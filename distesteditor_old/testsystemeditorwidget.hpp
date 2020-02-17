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
#ifndef DISTESTEDITOR_TESTSYSTEMEDITORWIDGET_HPP
#define DISTESTEDITOR_TESTSYSTEMEDITORWIDGET_HPP

#include "distesteditor_global.hpp"

#include <dsleditor/dsleditorwidget.hpp>

#include "testsystemeditor.hpp"

namespace distesteditor{

class DISTESTEDITOR_EXPORT TestSystemEditorWidget
    : public dsleditor::DslEditorWidget
{
  Q_OBJECT

public:
  explicit TestSystemEditorWidget(QWidget *parent = 0);
  virtual ~TestSystemEditorWidget();

public slots:
  virtual void setFontSettings(const TextEditor::FontSettings &);
          void showTestSystemGraphic();

private slots:
  void globalTestSystemRenderSettingsChangedSignalHandlder(QString projectID);
  void customTestSystemRenderSettingsChangedSignalHandlder(QString projectID);

protected:
  TestSystemEditor* createEditor();
  void renderTestSystem();

private:
  Q_DISABLE_COPY(TestSystemEditorWidget)
  class Private;
  Private*  _d;
};

} //end namespace distesteditor

#endif //DISTESTEDITOR_TESTSYSTEMEDITORWIDGET_HPP
