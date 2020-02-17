/*
 *  This file is part of SUT Editor Plugin for AppCreator based application.
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

#include "suteditor.hpp"

namespace suteditor{

class SutEditorWidget
    : public dsleditor::DslEditorWidget
{
  Q_OBJECT

public:
  explicit SutEditorWidget(QWidget *parent = 0);
  virtual ~SutEditorWidget();

public:
  const SutDocument::Ptr& sutDocument() const;
  void                    unCommentSelection();
  QModelIndex             outlineModelIndex();

public slots:
  virtual void setFontSettings(const TextEditor::FontSettings &);
//  void showSutGraphic();

signals:
  void outlineModelIndexChanged(const QModelIndex &index);

protected:
  SutEditor*                      createEditor();
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
  Q_DISABLE_COPY(SutEditorWidget)
  class Private;
  Private*  _d;
};

} //end namespace suteditor
