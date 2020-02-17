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
#pragma once

#include "testcaseeditor_global.hpp"

#include <graphlayout/mscquickwidget.hpp>
#include <QUuid>

class QToolBar;

namespace testcaseeditor {

class TestCaseGraphicEditor;

class TESTCASEEDITOR_EXPORT TestCaseGraphicWidget
    : public graphlayout::MscQuickWidget
{
  Q_OBJECT

public:
  explicit TestCaseGraphicWidget(QWidget *parent = 0);
  virtual ~TestCaseGraphicWidget();

public slots:
  bool updateTestCaseGraphic();
  void highlightGraphicItemByUuid(const QUuid& itemUuid,
                                  bool highlight,
                                  bool unhighlightOtherItems = false);
  void highlightGraphicItemsByUuids(const QList<QUuid>& itemUuids,
                                    bool highlight,
                                    bool unhighlightOtherItems = true);
  void highlightGraphicItemByName(const QString& itemName,
                                  bool highlight,
                                  bool unhighlightOtherItems = false);
  void highlightGraphicItemsByNames(const QList<QString>& itemNames,
                                    bool highlight,
                                    bool unhighlightOtherItems = true);

public:
  QToolBar*               toolBar();
  TestCaseGraphicEditor*  testCaseGraphicEditor() const;
  void                    setTestcaseGraphicEditor(TestCaseGraphicEditor* testCaseGraphicEditor) const;

private:
  void createToolBar();

private:
  Q_DISABLE_COPY(TestCaseGraphicWidget)
  class Private;
  Private*  _d;
};

} // namespace testcaseeditor
