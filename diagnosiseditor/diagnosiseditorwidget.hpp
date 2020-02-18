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

#include <dsleditor/dsleditorwidget.hpp>

#include "diagnosiseditor_global.hpp"

#include "diagnosiseditor.hpp"

namespace diagnosiseditor{

class DIAGNOSISEDITOR_EXPORT DiagnosisEditorWidget
    : public dsleditor::DslEditorWidget
{
  Q_OBJECT

public:
  explicit DiagnosisEditorWidget(QWidget *parent = 0);
  virtual ~DiagnosisEditorWidget();

public:
  const DiagnosisDocument::Ptr&  diagnosisDocument() const;
  void                          unCommentSelection();
  QModelIndex                   outlineModelIndex();

public slots:
  virtual void setFontSettings(const TextEditor::FontSettings&);
  void showDiagnosisGraphic();

signals:
  void outlineModelIndexChanged(const QModelIndex &index);

protected:
  DiagnosisEditor*                 createEditor();
  QVector<TextEditor::TextStyle>  highlighterFormatCategories();
  TextEditor::IAssistInterface*   createAssistInterface(TextEditor::AssistKind assistKind,
                                                        TextEditor::AssistReason assistReason) const;

private:
  QModelIndex indexForPosition(unsigned cursorPosition) const;

private slots:
  void updateOutline();
  void updateOutlineNow();
  void updateOutlineIndexNow();

private:
  void setSelectedElements();
  QString wordUnderCursor() const;

private:
  Q_DISABLE_COPY(DiagnosisEditorWidget)
  class Private;
  Private*  _d;
};

} //end namespace diagnosiseditor
