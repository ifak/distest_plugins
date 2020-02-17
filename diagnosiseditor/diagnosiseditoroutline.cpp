/*
 *  This file is part of Diagnosis Editor Plugin for AppCreator based application.
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

#include "diagnosiseditoroutline.hpp"

#include "diagnosiseditor.hpp"
#include "diagnosiseditorwidget.hpp"
#include "diagnosisoutlinemodel.hpp"

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

using namespace diagnosiseditor;
using namespace diagnosiseditor::Internal;

DiagnosisEditorOutlineTreeView::DiagnosisEditorOutlineTreeView(QWidget* parent)
  : Utils::NavigationTreeView(parent)
{}

void DiagnosisEditorOutlineTreeView::contextMenuEvent(QContextMenuEvent* event)
{
  if (!event)
    return;

  QMenu contextMenu;

  contextMenu.addAction(tr("Expand All"), this, &DiagnosisEditorOutlineTreeView::expandAll);
  contextMenu.addAction(tr("Collapse All"), this, &DiagnosisEditorOutlineTreeView::collapseAll);

  contextMenu.exec(event->globalPos());

  event->accept();

  return;
}

class DiagnosisEditorOutlineWidget::Private
{
  friend class DiagnosisEditorOutlineWidget;

  DiagnosisEditor*                 _diagnosisEditor;
  DiagnosisEditorOutlineTreeView*  _treeView;
  bool                            _enableCursorSync;
  bool                            _blockCursorSync;

  Private(DiagnosisEditor* diagnosisEditor)
    : _diagnosisEditor(diagnosisEditor),
      _enableCursorSync(true),
      _blockCursorSync(false)
  {}
};

DiagnosisEditorOutlineWidget::DiagnosisEditorOutlineWidget(DiagnosisEditor* diagnosisEditor)
  : TextEditor::IOutlineWidget(), _d(new Private(diagnosisEditor))
{
  Q_ASSERT(this->_d->_diagnosisEditor);

  this->_d->_treeView = new DiagnosisEditorOutlineTreeView(this);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->addWidget(this->_d->_treeView);
  this->setLayout(layout);

  DiagnosisOutlineModel const* diagnosisOutlineModel = this->_d->_diagnosisEditor->diagnosisOutlineModel();
  Q_ASSERT(diagnosisOutlineModel);
  this->_d->_treeView->setModel(const_cast<DiagnosisOutlineModel*>(diagnosisOutlineModel));
  this->_d->_treeView->expandAll();

  this->updateSelectionInTree(diagnosisOutlineModel->invisibleRootItem()->index());

  DiagnosisEditorWidget* diagnosisEditorWidget = qobject_cast<DiagnosisEditorWidget*>(this->_d->_diagnosisEditor->widget());
  Q_ASSERT(diagnosisEditorWidget);

  connect(diagnosisEditorWidget, &DiagnosisEditorWidget::outlineModelIndexChanged,
          this, &DiagnosisEditorOutlineWidget::updateSelectionInTree);
  connect(this->_d->_treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &DiagnosisEditorOutlineWidget::updateSelectionInText);
  connect(this->_d->_treeView, &DiagnosisEditorOutlineTreeView::doubleClicked,
          this, &DiagnosisEditorOutlineWidget::updateTextCursor);
}

QList<QAction*> DiagnosisEditorOutlineWidget::filterMenuActions() const
{
  return QList<QAction*>();
}

void DiagnosisEditorOutlineWidget::setCursorSynchronization(bool syncWithCursor)
{
  this->_d->_enableCursorSync = syncWithCursor;
  if (this->_d->_enableCursorSync)
  {
    DiagnosisEditorWidget* diagnosisEditorWidget = qobject_cast<DiagnosisEditorWidget*>(this->_d->_diagnosisEditor->widget());
    Q_ASSERT(diagnosisEditorWidget);
    this->updateSelectionInTree(diagnosisEditorWidget->outlineModelIndex());
  }

  return;
}

void DiagnosisEditorOutlineWidget::modelUpdated()
{
  this->_d->_treeView->expandAll();
}

void DiagnosisEditorOutlineWidget::updateSelectionInTree(const QModelIndex& index)
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

void DiagnosisEditorOutlineWidget::updateSelectionInText(const QItemSelection& selection)
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

void DiagnosisEditorOutlineWidget::updateTextCursor(const QModelIndex &modelIndex/*proxyIndex*/)
{
  using namespace dslparser;

  DiagnosisOutlineModel const* diagnosisOutlineModel = this->_d->_diagnosisEditor->diagnosisOutlineModel();
  Q_ASSERT(diagnosisOutlineModel);

  //  QModelIndex index = m_proxyModel->mapToSource(proxyIndex);
  TokenTextLocation const* tokTextLoc = diagnosisOutlineModel->modelTextLocation(modelIndex);
  if (tokTextLoc)
  {
    this->_d->_blockCursorSync = true;

    Core::EditorManager* editorManager = Core::EditorManager::instance();
    editorManager->cutForwardNavigationHistory();
    editorManager->addCurrentPositionToNavigationHistory();

    DiagnosisEditorWidget* diagnosisEditorWidget = qobject_cast<DiagnosisEditorWidget*>(this->_d->_diagnosisEditor->widget());
    Q_ASSERT(diagnosisEditorWidget);

    QTextCursor editCursor = diagnosisEditorWidget->textCursor();
    editCursor.setPosition(tokTextLoc->start());
    diagnosisEditorWidget->setTextCursor(editCursor);

    // line has to be 1 based, column 0 based!
//    m_editor->gotoLine(symbol->line(), symbol->column() - 1);
    diagnosisEditorWidget->setFocus();
    this->_d->_blockCursorSync = false;
  }

  return;
}

bool DiagnosisEditorOutlineWidget::syncCursor()
{
  return this->_d->_enableCursorSync && !this->_d->_blockCursorSync;
}

bool DiagnosisEditorOutlineWidgetFactory::supportsEditor(Core::IEditor* editor) const
{
  if(!editor)
    return false;

  if(!editor->document())
    return false;

  if(qobject_cast<DiagnosisEditor*>(editor))
    return true;

  return false;
}

TextEditor::IOutlineWidget*
DiagnosisEditorOutlineWidgetFactory::createWidget(Core::IEditor* editor)
{
  if(!editor)
    return 0;

  if(!editor->document())
    return 0;

  DiagnosisEditorOutlineWidget* outlineWidget=0;
  if(DiagnosisEditor* diagnosisEditor=qobject_cast<DiagnosisEditor*>(editor))
  {
    if(diagnosisEditor->diagnosisOutlineModel())
      outlineWidget=new DiagnosisEditorOutlineWidget(diagnosisEditor);
  }

  return outlineWidget;
}
