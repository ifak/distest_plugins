#include "testcaseeditoroutline.hpp"

#include "testcaseeditor.hpp"
#include "testcaseeditorwidget.hpp"
#include "testcaseoutlinemodel.hpp"

#include <projectexplorer/projectexplorer.h>

#include <coreplugin/idocument.h>
#include <coreplugin/editormanager/editormanager.h>
#include <utils/qtcassert.h>

#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QMenu>
#include <QContextMenuEvent>

#include <mobata/memory_leak_start.hpp>

using namespace testcaseeditor;
using namespace testcaseeditor::Internal;

TestCaseEditorOutlineTreeView::TestCaseEditorOutlineTreeView(QWidget* parent)
  : Utils::NavigationTreeView(parent)
{}

void TestCaseEditorOutlineTreeView::contextMenuEvent(QContextMenuEvent* event)
{
  if (!event)
    return;

  QMenu contextMenu;

  contextMenu.addAction(tr("Expand All"), this, &TestCaseEditorOutlineTreeView::expandAll);
  contextMenu.addAction(tr("Collapse All"), this, &TestCaseEditorOutlineTreeView::collapseAll);

  contextMenu.exec(event->globalPos());

  event->accept();

  return;
}

class TestCaseEditorOutlineWidget::Private
{
  friend class TestCaseEditorOutlineWidget;

  TestCaseEditor*                 _testCaseEditor;
  TestCaseEditorOutlineTreeView*  _treeView;
  bool                            _enableCursorSync;
  bool                            _blockCursorSync;

  Private(TestCaseEditor* testCaseEditor)
    : _testCaseEditor(testCaseEditor),
      _enableCursorSync(true),
      _blockCursorSync(false)
  {}
};

TestCaseEditorOutlineWidget::TestCaseEditorOutlineWidget(TestCaseEditor* testCaseEditor)
  : TextEditor::IOutlineWidget(), _d(new Private(testCaseEditor))
{
  Q_ASSERT(this->_d->_testCaseEditor);

  this->_d->_treeView = new TestCaseEditorOutlineTreeView(this);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->addWidget(this->_d->_treeView);
  this->setLayout(layout);

  TestCaseOutlineModel const* testCaseOutlineModel = this->_d->_testCaseEditor->testCaseOutlineModel();
  Q_ASSERT(testCaseOutlineModel);
  this->_d->_treeView->setModel(const_cast<TestCaseOutlineModel*>(testCaseOutlineModel));
  this->_d->_treeView->expandAll();

  this->updateSelectionInTree(testCaseOutlineModel->invisibleRootItem()->index());

  TestCaseEditorWidget* testCaseEditorWidget = qobject_cast<TestCaseEditorWidget*>(this->_d->_testCaseEditor->widget());
  Q_ASSERT(testCaseEditorWidget);

  connect(testCaseEditorWidget, &TestCaseEditorWidget::outlineModelIndexChanged,
          this, &TestCaseEditorOutlineWidget::updateSelectionInTree);
  connect(this->_d->_treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &TestCaseEditorOutlineWidget::updateSelectionInText);
  connect(this->_d->_treeView, &TestCaseEditorOutlineTreeView::doubleClicked,
          this, &TestCaseEditorOutlineWidget::updateTextCursor);
}

QList<QAction*> TestCaseEditorOutlineWidget::filterMenuActions() const
{
  return QList<QAction*>();
}

void TestCaseEditorOutlineWidget::setCursorSynchronization(bool syncWithCursor)
{
  this->_d->_enableCursorSync = syncWithCursor;
  if (this->_d->_enableCursorSync)
  {
    TestCaseEditorWidget* testCaseEditorWidget = qobject_cast<TestCaseEditorWidget*>(this->_d->_testCaseEditor->widget());
    Q_ASSERT(testCaseEditorWidget);
    this->updateSelectionInTree(testCaseEditorWidget->outlineModelIndex());
  }

  return;
}

void TestCaseEditorOutlineWidget::modelUpdated()
{
  this->_d->_treeView->expandAll();
}

void TestCaseEditorOutlineWidget::updateSelectionInTree(const QModelIndex& index)
{
  if (!syncCursor())
    return;
  if(!index.isValid())
    return;

  //  QModelIndex proxyIndex = m_proxyModel->mapFromSource(index);

  this->_d->_blockCursorSync = true;

  this->_d->_treeView->selectionModel()->select(/*proxyIndex*/index,
                                                QItemSelectionModel::ClearAndSelect);
  this->_d->_treeView->scrollTo(/*proxyIndex*/index);
  this->_d->_blockCursorSync = false;

  return;
}

void TestCaseEditorOutlineWidget::updateSelectionInText(const QItemSelection& selection)
{
  if (!syncCursor())
    return;

  if (!selection.indexes().isEmpty())
  {
    QModelIndex proxyIndex = selection.indexes().first();
    this->updateTextCursor(proxyIndex);
  }

  return;
}

void TestCaseEditorOutlineWidget::updateTextCursor(const QModelIndex &modelIndex/*proxyIndex*/)
{
  using namespace dslparser;

  TestCaseOutlineModel const* testCaseOutlineModel = this->_d->_testCaseEditor->testCaseOutlineModel();
  Q_ASSERT(testCaseOutlineModel);

  //  QModelIndex index = m_proxyModel->mapToSource(proxyIndex);
  TokenTextLocation const* tokTextLoc = testCaseOutlineModel->modelTextLocation(modelIndex);
  if (tokTextLoc)
  {
    this->_d->_blockCursorSync = true;

    Core::EditorManager* editorManager = Core::EditorManager::instance();
    editorManager->cutForwardNavigationHistory();
    editorManager->addCurrentPositionToNavigationHistory();

    TestCaseEditorWidget* testCaseEditorWidget = qobject_cast<TestCaseEditorWidget*>(this->_d->_testCaseEditor->widget());
    Q_ASSERT(testCaseEditorWidget);

    QTextCursor editCursor = testCaseEditorWidget->textCursor();
    editCursor.setPosition(tokTextLoc->start());
    testCaseEditorWidget->setTextCursor(editCursor);

    // line has to be 1 based, column 0 based!
//    m_editor->gotoLine(symbol->line(), symbol->column() - 1);
    testCaseEditorWidget->setFocus();
    this->_d->_blockCursorSync = false;
  }

  return;
}

bool TestCaseEditorOutlineWidget::syncCursor()
{
  return this->_d->_enableCursorSync && !this->_d->_blockCursorSync;
}

bool TestCaseEditorOutlineWidgetFactory::supportsEditor(Core::IEditor* editor) const
{
  if(!editor)
    return false;

  if(!editor->document())
    return false;

  if(qobject_cast<TestCaseEditor*>(editor))
    return true;

  return false;
}

TextEditor::IOutlineWidget*
TestCaseEditorOutlineWidgetFactory::createWidget(Core::IEditor* editor)
{
  if(!editor)
    return 0;

  if(!editor->document())
    return 0;

  TestCaseEditorOutlineWidget* outlineWidget=0;
  if(TestCaseEditor* testcaseEditor=qobject_cast<TestCaseEditor*>(editor))
  {
    if(testcaseEditor->testCaseOutlineModel())
      outlineWidget=new TestCaseEditorOutlineWidget(testcaseEditor);
  }

  return outlineWidget;
}
