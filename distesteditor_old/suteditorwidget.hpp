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
#ifndef DISTESTEDITOR_SUTEDITORWIDGET_HPP
#define DISTESTEDITOR_SUTEDITORWIDGET_HPP

#include <dsleditor/dsleditorwidget.hpp>

#include "suteditor.hpp"

namespace distesteditor{

class SutEditorWidget
    : public dsleditor::DslEditorWidget
{
  Q_OBJECT

public:
  explicit SutEditorWidget(QWidget *parent = 0);
  virtual ~SutEditorWidget();

public slots:
  virtual void setFontSettings(const TextEditor::FontSettings &);
          void showSutGraphic();

private slots:
  void globalSutRenderSettingsChangedSignalHandlder(QString projectID);
  void customSutRenderSettingsChangedSignalHandlder(QString projectID);

protected:
  SutEditor* createEditor();
  void renderSut();

private:
  Q_DISABLE_COPY(SutEditorWidget)
  class Private;
  Private* _d;
};

} //end namespace distesteditor

#endif //DISTESTEDITOR_SUTEDITORWIDGET_HPP
