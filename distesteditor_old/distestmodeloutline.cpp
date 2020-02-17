/*
*  This file is part of Spenat Plugin for Spenat Creator.
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

#include "distestmodeloutline.hpp"

#include "testsuiteeditor.hpp"
#include "decleditor.hpp"
#include "suteditor.hpp"
#include "testsystemeditor.hpp"
#include "testcaseeditor.hpp"
#include "testcasegraphiceditor.hpp"

#include <projectexplorer/projectexplorer.h>

#include <coreplugin/idocument.h>
#include <coreplugin/editormanager/editormanager.h>
#include <utils/qtcassert.h>

#include <mobata/model/ts/ts.hpp>

#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QMenu>
#include <QContextMenuEvent>

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;
using namespace distesteditor::Internal;

DisTestModelOutlineTreeView::DisTestModelOutlineTreeView(QWidget *parent)
  : Utils::NavigationTreeView(parent)
{}

void DisTestModelOutlineTreeView::contextMenuEvent(QContextMenuEvent *event)
{
  if (!event)
    return;

  QMenu contextMenu;

  contextMenu.addAction(tr("Expand All"), this, SLOT(expandAll()));
  contextMenu.addAction(tr("Collapse All"), this, SLOT(collapseAll()));

  contextMenu.exec(event->globalPos());

  event->accept();
}

DisTestModelOutlineWidget::DisTestModelOutlineWidget(const model::ts::TestSuite* testModel)
  : TextEditor::IOutlineWidget(),
    m_treeView(new DisTestModelOutlineTreeView(this)),
    m_enableCursorSync(true),
    m_blockCursorSync(false)
{
  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->addWidget(m_treeView);
  setLayout(layout);

  m_treeView->setModel(const_cast<model::ts::TestSuite*>(testModel));
  m_treeView->expandAll();

  //    connect(m_model, SIGNAL(modelReset()), this, SLOT(modelUpdated()));
  //    modelUpdated();

  //    connect(m_editor, SIGNAL(outlineModelIndexChanged(QModelIndex)),
  //            this, SLOT(updateSelectionInTree(QModelIndex)));
  //    connect(m_treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
  //            this, SLOT(updateSelectionInText(QItemSelection)));
  //    connect(m_treeView, SIGNAL(doubleClicked(QModelIndex)),
  //            this, SLOT(updateTextCursor(QModelIndex)));
}

QList<QAction*> DisTestModelOutlineWidget::filterMenuActions() const
{
  return QList<QAction*>();
}

void DisTestModelOutlineWidget::setCursorSynchronization(bool syncWithCursor)
{
  m_enableCursorSync = syncWithCursor;
  //  if (m_enableCursorSync)
  //    this->updateSelectionInTree(m_editor->outlineModelIndex());
}

void DisTestModelOutlineWidget::modelUpdated()
{
  m_treeView->expandAll();
}

void DisTestModelOutlineWidget::updateSelectionInTree(const QModelIndex &index)
{
  if (!syncCursor())
    return;

  //  QModelIndex proxyIndex = m_proxyModel->mapFromSource(index);

  m_blockCursorSync = true;

  m_treeView->selectionModel()->select(/*proxyIndex*/index,
                                       QItemSelectionModel::ClearAndSelect);
  m_treeView->scrollTo(/*proxyIndex*/index);
  m_blockCursorSync = false;

  return;
}

void DisTestModelOutlineWidget::updateSelectionInText(const QItemSelection &selection)
{
  if (!syncCursor())
    return;

  if (!selection.indexes().isEmpty()) {
    QModelIndex proxyIndex = selection.indexes().first();
    updateTextCursor(proxyIndex);
  }
}

void DisTestModelOutlineWidget::updateTextCursor(const QModelIndex &/*proxyIndex*/)
{
  //  QModelIndex index = m_proxyModel->mapToSource(proxyIndex);
  //  CPlusPlus::Symbol *symbol = m_model->symbolFromIndex(index);
  //  if (symbol) {
  //      m_blockCursorSync = true;

  //      if (debug)
  //          qDebug() << "CppOutline - moving cursor to" << symbol->line() << symbol->column() - 1;

  //      Core::EditorManager *editorManager = Core::EditorManager::instance();
  //      editorManager->cutForwardNavigationHistory();
  //      editorManager->addCurrentPositionToNavigationHistory();

  //      // line has to be 1 based, column 0 based!
  //      m_editor->gotoLine(symbol->line(), symbol->column() - 1);
  //      m_editor->setFocus();
  //      m_blockCursorSync = false;
  //  }
}

bool DisTestModelOutlineWidget::syncCursor()
{
  return m_enableCursorSync && !m_blockCursorSync;
}

bool DisTestModelOutlineWidgetFactory::supportsEditor(Core::IEditor *editor) const
{
  if(!editor)
    return false;

  if(!editor->document())
    return false;

  if(qobject_cast<TestSuiteEditor*>(editor))
    return true;
  else if(qobject_cast<SutEditor*>(editor))
    return true;
  else if(qobject_cast<TestSystemEditor*>(editor))
    return true;
  else if(qobject_cast<TestCaseEditor*>(editor))
    return true;
  else if(qobject_cast<TestCaseGraphicEditor*>(editor))
    return true;
  
  return false;
}

TextEditor::IOutlineWidget*
DisTestModelOutlineWidgetFactory::createWidget(Core::IEditor *editor)
{
  if(!editor)
    return 0;

  if(!editor->document())
    return 0;

  DisTestModelOutlineWidget* outlineWidget=0;
  if(TestSuiteEditor* testSuiteEditor=qobject_cast<TestSuiteEditor*>(editor))
  {
    if(testSuiteEditor->testSuite())
    {
      outlineWidget=new DisTestModelOutlineWidget(testSuiteEditor->testSuite());
      outlineWidget->updateSelectionInTree(testSuiteEditor->testSuite()->invisibleRootItem()->index());
    }
  }
//  else if(SutEditor* sutEditor=qobject_cast<SutEditor*>(editor))
//  {
//    if(sutEditor->sutItem())
//    {
//      outlineWidget=new DisTestModelOutlineWidget(sutEditor->sutItem()->testSuite());
//      outlineWidget->updateSelectionInTree(sutEditor->sutItem()->index());
//    }
//  }
  else if(TestSystemEditor* testSystemEditor=qobject_cast<TestSystemEditor*>(editor))
  {
    if(testSystemEditor->testSystemItem())
    {
      outlineWidget=new DisTestModelOutlineWidget(testSystemEditor->testSystemItem()->testSuite());
      outlineWidget->updateSelectionInTree(testSystemEditor->testSystemItem()->index());
    }
  }
  else if(TestCaseEditor* testCaseEditor=qobject_cast<TestCaseEditor*>(editor))
  {
    if(testCaseEditor->testCaseItem())
    {
      outlineWidget=new DisTestModelOutlineWidget(testCaseEditor->testCaseItem()->testSuite());
      outlineWidget->updateSelectionInTree(testCaseEditor->testCaseItem()->index());
    }
  }
  else if(TestCaseGraphicEditor* testCaseGraphicEditor=qobject_cast<TestCaseGraphicEditor*>(editor))
  {
    if(testCaseGraphicEditor->testCaseItem())
    {
      outlineWidget=new DisTestModelOutlineWidget(testCaseGraphicEditor->testCaseItem()->testSuite());
      outlineWidget->updateSelectionInTree(testCaseGraphicEditor->testCaseItem()->index());
    }
  }

  return outlineWidget;
}
