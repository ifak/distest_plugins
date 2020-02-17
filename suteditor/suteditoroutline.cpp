/*
*  This file is part of SUT Plugin.
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

#include "suteditoroutline.hpp"

#include "suteditor.hpp"
#include "suteditorwidget.hpp"
#include "sutoutlinemodel.hpp"

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

using namespace suteditor;
using namespace suteditor::Internal;

SutEditorOutlineTreeView::SutEditorOutlineTreeView(QWidget *parent)
  : Utils::NavigationTreeView(parent)
{}

void SutEditorOutlineTreeView::contextMenuEvent(QContextMenuEvent *event)
{
  if (!event)
    return;

  QMenu contextMenu;

  contextMenu.addAction(tr("Expand All"), this, &SutEditorOutlineTreeView::expandAll);
  contextMenu.addAction(tr("Collapse All"), this, &SutEditorOutlineTreeView::collapseAll);

  contextMenu.exec(event->globalPos());

  event->accept();

  return;
}

class SutEditorOutlineWidget::Private
{
  friend class SutEditorOutlineWidget;

  SutEditor*                _sutEditor;
  SutEditorOutlineTreeView* _treeView;
  bool                      _enableCursorSync;
  bool                      _blockCursorSync;

  Private(SutEditor* sutEditor)
    : _sutEditor(sutEditor),
      _enableCursorSync(true),
      _blockCursorSync(false)
  {}
};

SutEditorOutlineWidget::SutEditorOutlineWidget(SutEditor* sutEditor)
  : TextEditor::IOutlineWidget(), _d(new Private(sutEditor))
{
  Q_ASSERT(this->_d->_sutEditor);

  this->_d->_treeView = new SutEditorOutlineTreeView(this);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->addWidget(this->_d->_treeView);
  this->setLayout(layout);

  SutOutlineModel const* sutOutlineModel = this->_d->_sutEditor->sutOutlineModel();
  Q_ASSERT(sutOutlineModel);
  this->_d->_treeView->setModel(const_cast<SutOutlineModel*>(sutOutlineModel));
  this->_d->_treeView->expandAll();

  this->updateSelectionInTree(sutOutlineModel->invisibleRootItem()->index());

  SutEditorWidget* sutEditorWidget = qobject_cast<SutEditorWidget*>(this->_d->_sutEditor->widget());
  Q_ASSERT(sutEditorWidget);

  //    connect(m_model, SIGNAL(modelReset()), this, SLOT(modelUpdated()));
  //    modelUpdated();

  connect(sutEditorWidget, &SutEditorWidget::outlineModelIndexChanged,
          this, &SutEditorOutlineWidget::updateSelectionInTree);
  connect(this->_d->_treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, &SutEditorOutlineWidget::updateSelectionInText);
  connect(this->_d->_treeView, &SutEditorOutlineTreeView::doubleClicked,
          this, &SutEditorOutlineWidget::updateTextCursor);
}

QList<QAction*> SutEditorOutlineWidget::filterMenuActions() const
{
  return QList<QAction*>();
}

void SutEditorOutlineWidget::setCursorSynchronization(bool syncWithCursor)
{
  this->_d->_enableCursorSync = syncWithCursor;
  if (this->_d->_enableCursorSync)
  {
    SutEditorWidget* sutEditorWidget = qobject_cast<SutEditorWidget*>(this->_d->_sutEditor->widget());
    Q_ASSERT(sutEditorWidget);
    this->updateSelectionInTree(sutEditorWidget->outlineModelIndex());
  }

  return;
}

void SutEditorOutlineWidget::modelUpdated()
{
  this->_d->_treeView->expandAll();
}

void SutEditorOutlineWidget::updateSelectionInTree(const QModelIndex &index)
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

void SutEditorOutlineWidget::updateSelectionInText(const QItemSelection &selection)
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

void SutEditorOutlineWidget::updateTextCursor(const QModelIndex &modelIndex/*proxyIndex*/)
{
  using namespace dslparser;

  SutOutlineModel const* sutOutlineModel = this->_d->_sutEditor->sutOutlineModel();
  Q_ASSERT(sutOutlineModel);

  //  QModelIndex index = m_proxyModel->mapToSource(proxyIndex);
  TokenTextLocation const* tokTextLoc = sutOutlineModel->modelTextLocation(modelIndex);
  if (tokTextLoc)
  {
    this->_d->_blockCursorSync = true;

    Core::EditorManager *editorManager = Core::EditorManager::instance();
    editorManager->cutForwardNavigationHistory();
    editorManager->addCurrentPositionToNavigationHistory();

    SutEditorWidget* sutEditorWidget = qobject_cast<SutEditorWidget*>(this->_d->_sutEditor->widget());
    Q_ASSERT(sutEditorWidget);

    QTextCursor editCursor = sutEditorWidget->textCursor();
    editCursor.setPosition(tokTextLoc->start());
    sutEditorWidget->setTextCursor(editCursor);

    // line has to be 1 based, column 0 based!
//    m_editor->gotoLine(symbol->line(), symbol->column() - 1);
    sutEditorWidget->setFocus();
    this->_d->_blockCursorSync = false;
  }

  return;
}

bool SutEditorOutlineWidget::syncCursor()
{
  return this->_d->_enableCursorSync && !this->_d->_blockCursorSync;
}

bool SutEditorOutlineWidgetFactory::supportsEditor(Core::IEditor *editor) const
{
  if(!editor)
    return false;

  if(!editor->document())
    return false;

  if(qobject_cast<SutEditor*>(editor))
    return true;

  return false;
}

TextEditor::IOutlineWidget*
SutEditorOutlineWidgetFactory::createWidget(Core::IEditor *editor)
{
  if(!editor)
    return 0;

  if(!editor->document())
    return 0;

  SutEditorOutlineWidget* outlineWidget=0;
  if(SutEditor* sutEditor=qobject_cast<SutEditor*>(editor))
  {
    if(sutEditor->sutOutlineModel())
      outlineWidget=new SutEditorOutlineWidget(sutEditor);
  }

  return outlineWidget;
}
