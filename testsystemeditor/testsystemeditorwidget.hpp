/*
 *  This file is part of Testsystem Editor Plugin for AppCreator based application.
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

#pragma once

#include <dsleditor/dsleditorwidget.hpp>

#include "testsystemeditor.hpp"

namespace testsystemeditor{

class TestSystemEditorWidget
    : public dsleditor::DslEditorWidget
{
  Q_OBJECT

public:
  explicit TestSystemEditorWidget(QWidget *parent = 0);
  virtual ~TestSystemEditorWidget();

public:
  const TestSystemDocument::Ptr& testsystemDocument() const;
  void                    unCommentSelection();
  QModelIndex             outlineModelIndex();

public slots:
  virtual void setFontSettings(const TextEditor::FontSettings &);
//  void showTestSystemGraphic();

signals:
  void outlineModelIndexChanged(const QModelIndex &index);

protected:
  TestSystemEditor*                      createEditor();
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
  Q_DISABLE_COPY(TestSystemEditorWidget)
  class Private;
  Private*  _d;
};

} //end namespace testsystemeditor
