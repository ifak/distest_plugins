/*
 * This file is part of distest_plugins.
 *
 * distest_plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * distest_plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with distest_plugins.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "testcaseeditor_global.hpp"

#include <utils/navigationtreeview.h>
#include <texteditor/ioutlinewidget.h>

#include <QSortFilterProxyModel>
#include <QTreeView>

namespace testcaseeditor{

class TestCaseGraphicEditor;

class TESTCASEEDITOR_EXPORT TestCaseGraphicOutlineTreeView
    : public Utils::NavigationTreeView
{
  Q_OBJECT

public:
  TestCaseGraphicOutlineTreeView(QWidget *parent);
  void contextMenuEvent(QContextMenuEvent* event);
};

class TESTCASEEDITOR_EXPORT TestCaseGraphicOutlineWidget
    : public TextEditor::IOutlineWidget
{
  Q_OBJECT
public:
  TestCaseGraphicOutlineWidget(TestCaseGraphicEditor* testCaseGraphicEditor);

  // IOutlineWidget
  virtual QList<QAction*> filterMenuActions() const;
  virtual void setCursorSynchronization(bool syncWithCursor);

public slots:
  void modelUpdated();
  void updateSelectionInTree(const QModelIndex &index);
  void updateSelectionInText(const QItemSelection &selection);
  void updateTextCursor(const QModelIndex &modelIndex);

private:
  bool syncCursor();

private:
  Q_DISABLE_COPY(TestCaseGraphicOutlineWidget)
  class Private;
  Private* _d;
};

class TESTCASEEDITOR_EXPORT TestCaseGraphicOutlineWidgetFactory
    : public TextEditor::IOutlineWidgetFactory
{
  Q_OBJECT
public:
  bool supportsEditor(Core::IEditor *editor) const;
  TextEditor::IOutlineWidget *createWidget(Core::IEditor *editor);
};

} // namespace testcaseeditor
