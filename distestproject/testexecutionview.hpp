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

#include "distestproject_global.hpp"

#include <coreplugin/inavigationwidgetfactory.h>

#include <QStyledItemDelegate>
#include <QTreeView>

namespace Core {
class IEditor;
}

namespace ProjectExplorer{
class Project;
}

namespace distestproject{

class DISTESTPROJECTSHARED_EXPORT TestExecutionView
    : public QTreeView
{
  Q_OBJECT

public:
  TestExecutionView();
  virtual ~TestExecutionView();

  bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void handlePressed(const QModelIndex &);
  void updateCurrentItem(Core::IEditor*);
  void contextMenuRequested(QPoint pos);
  void currentProjectChanged(ProjectExplorer::Project* currentProject);

private:
  void activateEditor(const QModelIndex &index);
};

class TestExecutionViewFactory : public Core::INavigationWidgetFactory
{
  Q_OBJECT
public:
  TestExecutionViewFactory();
  ~TestExecutionViewFactory();

public:
  QString displayName() const;
  int priority() const;
  Core::Id id() const;
  QKeySequence activationSequence() const;
  Core::NavigationView createWidget();
};

} // namespace distestproject
