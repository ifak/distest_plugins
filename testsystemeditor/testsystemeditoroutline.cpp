/*
 *  This file is part of Test System Editor Plugin for AppCreator based application.
 *
 *  Copyright (C) 2013 Jan Krause <jan.krause.no19@gmail.com>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
*/

#include "testsystemeditoroutline.hpp"

#include "testsystemeditor.hpp"
#include "testsystemeditorwidget.hpp"
#include "testsystemoutlinemodel.hpp"

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

using namespace testsystemeditor;
using namespace testsystemeditor::Internal;

TestSystemEditorOutlineTreeView::TestSystemEditorOutlineTreeView(QWidget *parent)
  : Utils::NavigationTreeView(parent)
{}

void TestSystemEditorOutlineTreeView::contextMenuEvent(QContextMenuEvent *event)
{
  if (!event)
    return;

  QMenu contextMenu;

  contextMenu.addAction(tr("Expand All"), this, &TestSystemEditorOutlineTreeView::expandAll);
  contextMenu.addAction(tr("Collapse All"), this, &TestSystemEditorOutlineTreeView::collapseAll);

  contextMenu.exec(event->globalPos());

  event->accept();

  return;
}

class TestSystemEditorOutlineWidget::Private
{
  friend class TestSystemEditorOutlineWidget;

  TestSystemEditor*                 _testSystemEditor;
  TestSystemEditorOutlineTreeView*  _treeView;
  bool                              _enableCursorSync;
  bool                              _blockCursorSync;

  Private(TestSystemEditor* testsystemEditor)
    : _testSystemEditor(testsystemEditor),
      _enableCursorSync(true),
      _blockCursorSync(false)
  {}
};

TestSystemEditorOutlineWidget::TestSystemEditorOutlineWidget(TestSystemEditor* testsystemEditor)
  : TextEditor::IOutlineWidget(), _d(new Private(testsystemEditor))
{
  Q_ASSERT(this->_d->_testSystemEditor);

  this->_d->_treeView = new TestSystemEditorOutlineTreeView(this);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->addWidget(this->_d->_treeView);
  this->setLayout(layout);

  TestSystemOutlineModel const* testsystemOutlineModel = this->_d->_testSystemEditor->testSystemOutlineModel();
  Q_ASSERT(testsystemOutlineModel);
  this->_d->_treeView->setModel(const_cast<TestSystemOutlineModel*>(testsystemOutlineModel));
  this->_d->_treeView->expandAll();

  this->updateSelectionInTree(testsystemOutlineModel->invisibleRootItem()->index());

  TestSystemEditorWidget* testsystemEditorWidget = qobject_cast<TestSystemEditorWidget*>(this->_d->_testSystemEditor->widget());
  Q_ASSERT(testsystemEditorWidget);

  //    connect(m_model, SIGNAL(modelReset()), this, SLOT(modelUpdated()));
  //    modelUpdated();

  connect(testsystemEditorWidget, &TestSystemEditorWidget::outlineModelIndexChanged,
          this, &TestSystemEditorOutlineWidget::updateSelectionInTree);
  connect(this->_d->_treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &TestSystemEditorOutlineWidget::updateSelectionInText);
  connect(this->_d->_treeView, &TestSystemEditorOutlineTreeView::doubleClicked,
          this, &TestSystemEditorOutlineWidget::updateTextCursor);
}

QList<QAction*> TestSystemEditorOutlineWidget::filterMenuActions() const
{
  return QList<QAction*>();
}

void TestSystemEditorOutlineWidget::setCursorSynchronization(bool syncWithCursor)
{
  this->_d->_enableCursorSync = syncWithCursor;
  if (this->_d->_enableCursorSync)
  {
    TestSystemEditorWidget* testsystemEditorWidget = qobject_cast<TestSystemEditorWidget*>(this->_d->_testSystemEditor->widget());
    Q_ASSERT(testsystemEditorWidget);
    this->updateSelectionInTree(testsystemEditorWidget->outlineModelIndex());
  }

  return;
}

void TestSystemEditorOutlineWidget::modelUpdated()
{
  this->_d->_treeView->expandAll();
}

void TestSystemEditorOutlineWidget::updateSelectionInTree(const QModelIndex &index)
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

void TestSystemEditorOutlineWidget::updateSelectionInText(const QItemSelection &selection)
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

void TestSystemEditorOutlineWidget::updateTextCursor(const QModelIndex &modelIndex/*proxyIndex*/)
{
  using namespace dslparser;

  TestSystemOutlineModel const* testsystemOutlineModel = this->_d->_testSystemEditor->testSystemOutlineModel();
  Q_ASSERT(testsystemOutlineModel);

  //  QModelIndex index = m_proxyModel->mapToSource(proxyIndex);
  TokenTextLocation const* tokTextLoc = testsystemOutlineModel->modelTextLocation(modelIndex);
  if (tokTextLoc)
  {
    this->_d->_blockCursorSync = true;

    Core::EditorManager *editorManager = Core::EditorManager::instance();
    editorManager->cutForwardNavigationHistory();
    editorManager->addCurrentPositionToNavigationHistory();

    TestSystemEditorWidget* testsystemEditorWidget = qobject_cast<TestSystemEditorWidget*>(this->_d->_testSystemEditor->widget());
    Q_ASSERT(testsystemEditorWidget);

    QTextCursor editCursor = testsystemEditorWidget->textCursor();
    editCursor.setPosition(tokTextLoc->start());
    testsystemEditorWidget->setTextCursor(editCursor);

    // line has to be 1 based, column 0 based!
//    m_editor->gotoLine(symbol->line(), symbol->column() - 1);
    testsystemEditorWidget->setFocus();
    this->_d->_blockCursorSync = false;
  }

  return;
}

bool TestSystemEditorOutlineWidget::syncCursor()
{
  return this->_d->_enableCursorSync && !this->_d->_blockCursorSync;
}

bool TestSystemEditorOutlineWidgetFactory::supportsEditor(Core::IEditor *editor) const
{
  if(!editor)
    return false;

  if(!editor->document())
    return false;

  if(qobject_cast<TestSystemEditor*>(editor))
    return true;

  return false;
}

TextEditor::IOutlineWidget*
TestSystemEditorOutlineWidgetFactory::createWidget(Core::IEditor *editor)
{
  if(!editor)
    return 0;

  if(!editor->document())
    return 0;

  TestSystemEditorOutlineWidget* outlineWidget=0;
  if(TestSystemEditor* testsystemEditor=qobject_cast<TestSystemEditor*>(editor))
  {
    if(testsystemEditor->testSystemOutlineModel())
      outlineWidget=new TestSystemEditorOutlineWidget(testsystemEditor);
  }

  return outlineWidget;
}
