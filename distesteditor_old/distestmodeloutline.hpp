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
#ifndef DISTESTEDITOR_TESTMODELOUTLINE_HPP
#define DISTESTEDITOR_TESTMODELOUTLINE_HPP

#include <utils/navigationtreeview.h>
#include <texteditor/ioutlinewidget.h>

#include <QSortFilterProxyModel>
#include <QTreeView>

namespace model{
namespace ts{
class TestSuite;
}}

namespace distesteditor{

namespace Internal{

class DisTestModelOutlineTreeView : public Utils::NavigationTreeView
{
  Q_OBJECT

public:
  DisTestModelOutlineTreeView(QWidget *parent);

  void contextMenuEvent(QContextMenuEvent *event);
};

class DisTestModelOutlineWidget : public TextEditor::IOutlineWidget
{
  Q_OBJECT
public:
  DisTestModelOutlineWidget(model::ts::TestSuite const* testModel);

  // IOutlineWidget
  virtual QList<QAction*> filterMenuActions() const;
  virtual void setCursorSynchronization(bool syncWithCursor);

public slots:
  void modelUpdated();
  void updateSelectionInTree(const QModelIndex &index);
  void updateSelectionInText(const QItemSelection &selection);
  void updateTextCursor(const QModelIndex &index);

private:
  bool syncCursor();

private:
  DisTestModelOutlineTreeView *m_treeView;
  bool m_enableCursorSync;
  bool m_blockCursorSync;
};

class DisTestModelOutlineWidgetFactory : public TextEditor::IOutlineWidgetFactory
{
  Q_OBJECT
public:
  bool supportsEditor(Core::IEditor *editor) const;
  TextEditor::IOutlineWidget *createWidget(Core::IEditor *editor);
};

} // namespace Internal
} // namespace distesteditor

#endif // DISTESTEDITOR_TESTMODELOUTLINE_HPP
