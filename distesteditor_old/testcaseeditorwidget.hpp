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
#ifndef DISTESTEDITOR_TESTCASEEDITORWIDGET_HPP
#define DISTESTEDITOR_TESTCASEEDITORWIDGET_HPP

#include "distesteditor_global.hpp"

#include <dsleditor/dsleditorwidget.hpp>

#include "testcaseeditor.hpp"

namespace distesteditor{

class DISTESTEDITOR_EXPORT TestCaseEditorWidget
    : public dsleditor::DslEditorWidget
{
  Q_OBJECT

public:
  explicit TestCaseEditorWidget(QWidget *parent = 0);
  virtual ~TestCaseEditorWidget();

public slots:
  virtual void setFontSettings(const TextEditor::FontSettings &);
          void showTestCaseGraphic();

private slots:
  void globalTestCaseRenderSettingsChangedSignalHandlder(QString projectID);
  void customTestCaseRenderSettingsChangedSignalHandlder(QString projectID);

protected:
  TestCaseEditor* createEditor();
  void renderTestCase();

private:
  Q_DISABLE_COPY(TestCaseEditorWidget)
  class Private;
  Private* _d;
};

} //end namespace distesteditor

#endif //DISTESTEDITOR_TESTCASEEDITORWIDGET_HPP
