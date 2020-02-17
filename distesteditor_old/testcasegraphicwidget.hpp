/*
 * This file is part of mobata.
 *
 * mobata is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * mobata is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with mobata.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DISTESTEDITOR_TESTCASEGRAPHICWIDGET_HPP
#define DISTESTEDITOR_TESTCASEGRAPHICWIDGET_HPP

#include "distesteditor_global.hpp"

#include <mobatawidgets/ts/testcaseview.hpp>

class QToolBar;

namespace distesteditor {

class DISTESTEDITOR_EXPORT TestCaseGraphicWidget
    : public view::ts::TestCaseView
{
  Q_OBJECT

public:
  explicit TestCaseGraphicWidget(QWidget *parent = 0);
  virtual ~TestCaseGraphicWidget();

public:
  QToolBar*                 toolBar();
  view::ts::TestCaseScene*  testCaseScene();

private:
  void createToolBar();

private:
  Q_DISABLE_COPY(TestCaseGraphicWidget)
  class Private;
  Private*  _d;
};

} // namespace distesteditor

#endif // DISTESTEDITOR_TESTCASEGRAPHICWIDGET_HPP
