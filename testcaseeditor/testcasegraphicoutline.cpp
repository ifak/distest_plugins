#include "testcasegraphicoutline.hpp"

#include "testcasegraphiceditor.hpp"

#include <projectexplorer/projectexplorer.h>

#include <coreplugin/idocument.h>
#include <coreplugin/editormanager/editormanager.h>
#include <utils/qtcassert.h>

#include <mobata/model/ts/testcaseitem.hpp>

#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QMenu>
#include <QContextMenuEvent>

using namespace testcaseeditor;

TestCaseGraphicOutlineTreeView::TestCaseGraphicOutlineTreeView(QWidget* parent)
  : Utils::NavigationTreeView(parent)
{}

void TestCaseGraphicOutlineTreeView::contextMenuEvent(QContextMenuEvent* event)
{
  if (!event)
    return;

  QMenu contextMenu;

  contextMenu.addAction(tr("Expand All"), this, &TestCaseGraphicOutlineTreeView::expandAll);
  contextMenu.addAction(tr("Collapse All"), this, &TestCaseGraphicOutlineTreeView::collapseAll);

  contextMenu.exec(event->globalPos());

  event->accept();

  return;
}

class TestCaseGraphicOutlineWidget::Private
{
  friend class TestCaseGraphicOutlineWidget;

  TestCaseGraphicEditor*          _testCaseGraphicEditor;
  TestCaseGraphicOutlineTreeView* _treeView;
  bool                            _enableCursorSync;
  bool                            _blockCursorSync;

  Private(TestCaseGraphicEditor* testCaseGraphicEditor)
    : _testCaseGraphicEditor(testCaseGraphicEditor),
      _enableCursorSync(true),
      _blockCursorSync(false)
  {}
};

TestCaseGraphicOutlineWidget::TestCaseGraphicOutlineWidget(TestCaseGraphicEditor* testCaseGraphicEditor)
  : TextEditor::IOutlineWidget(),
    _d(new Private(testCaseGraphicEditor))
{
  Q_ASSERT(this->_d->_testCaseGraphicEditor);

  this->_d->_treeView = new TestCaseGraphicOutlineTreeView(this);
  this->_d->_treeView->setModel(this->_d->_testCaseGraphicEditor->outlineModel());

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->addWidget(this->_d->_treeView);
  this->setLayout(layout);

  if(this->_d->_testCaseGraphicEditor->outlineModel())
  {
    this->_d->_treeView->expandAll();
    this->updateSelectionInTree(this->_d->_testCaseGraphicEditor->outlineModel()->invisibleRootItem()->index());
  }
}

QList<QAction*> TestCaseGraphicOutlineWidget::filterMenuActions() const
{
  return QList<QAction*>();
}

void TestCaseGraphicOutlineWidget::setCursorSynchronization(bool syncWithCursor)
{
  this->_d->_enableCursorSync = syncWithCursor;
//  if (this->_d->_enableCursorSync)
//  {
//    TestCaseGraphicWidget* testCaseGraphicWidget = qobject_cast<TestCaseGraphicWidget*>(this->_d->_testCaseGraphicEditor->widget());
//    Q_ASSERT(testCaseGraphicWidget);
//    this->updateSelectionInTree(testCaseGraphicWidget->outlineModelIndex());
//  }

  return;
}

void TestCaseGraphicOutlineWidget::modelUpdated()
{
  this->_d->_treeView->expandAll();
}

void TestCaseGraphicOutlineWidget::updateSelectionInTree(const QModelIndex& index)
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

void TestCaseGraphicOutlineWidget::updateSelectionInText(const QItemSelection& selection)
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

void TestCaseGraphicOutlineWidget::updateTextCursor(const QModelIndex& /*modelIndex*/)
{

//  using namespace dslparser;

//  TestCaseOutlineModel const* testCaseOutlineModel = this->_d->_TestCaseGraphic->testCaseOutlineModel();
//  Q_ASSERT(testCaseOutlineModel);

//  //  QModelIndex index = m_proxyModel->mapToSource(proxyIndex);
//  TokenTextLocation const* tokTextLoc = testCaseOutlineModel->modelTextLocation(modelIndex);
//  if (tokTextLoc)
//  {
//    this->_d->_blockCursorSync = true;

//    Core::EditorManager* editorManager = Core::EditorManager::instance();
//    editorManager->cutForwardNavigationHistory();
//    editorManager->addCurrentPositionToNavigationHistory();

//    TestCaseGraphicWidget* TestCaseGraphicWidget = qobject_cast<TestCaseGraphicWidget*>(this->_d->_TestCaseGraphic->widget());
//    Q_ASSERT(TestCaseGraphicWidget);

//    QTextCursor editCursor = TestCaseGraphicWidget->textCursor();
//    editCursor.setPosition(tokTextLoc->start());
//    TestCaseGraphicWidget->setTextCursor(editCursor);

//    // line has to be 1 based, column 0 based!
////    m_editor->gotoLine(symbol->line(), symbol->column() - 1);
//    TestCaseGraphicWidget->setFocus();
//    this->_d->_blockCursorSync = false;
//  }

  return;
}

bool TestCaseGraphicOutlineWidget::syncCursor()
{
  return this->_d->_enableCursorSync && !this->_d->_blockCursorSync;
}

bool TestCaseGraphicOutlineWidgetFactory::supportsEditor(Core::IEditor* editor) const
{
  if(!editor)
    return false;

  if(qobject_cast<TestCaseGraphicEditor*>(editor))
    return true;

  return false;
}

TextEditor::IOutlineWidget*
TestCaseGraphicOutlineWidgetFactory::createWidget(Core::IEditor* editor)
{
  if(!editor)
    return 0;

  TestCaseGraphicOutlineWidget* outlineWidget=0;
  if(TestCaseGraphicEditor* testCaseGraphicEditor=qobject_cast<TestCaseGraphicEditor*>(editor))
      outlineWidget=new TestCaseGraphicOutlineWidget(testCaseGraphicEditor);

  return outlineWidget;
}
