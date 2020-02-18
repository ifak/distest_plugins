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
#ifndef DISTESTEDITOR_SUTGRAPHICWIDGET_HPP
#define DISTESTEDITOR_SUTGRAPHICWIDGET_HPP

#include "distesteditor_global.hpp"

#include <mobatawidgets/ts/sutview.hpp>

class QToolBar;

namespace distesteditor {

class DISTESTEDITOR_EXPORT SutGraphicWidget
    : public view::ts::SutView
{
  Q_OBJECT

public:
  SutGraphicWidget(QWidget *parent = 0);
  virtual ~SutGraphicWidget();

public:
  QToolBar*           toolBar();
  view::ts::SutScene* sutScene();

private:
  void createToolBar();

private:
  Q_DISABLE_COPY(SutGraphicWidget)
  class Private;
  Private*  _d;
};

} // namespace distesteditor

#endif // DISTESTEDITOR_SUTGRAPHICWIDGET_HPP
