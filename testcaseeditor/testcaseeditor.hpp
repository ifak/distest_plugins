/*
 *  This file is part of Test Case Editor Plugin for AppCreator based application.
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

#include "testcaseeditor_global.hpp"

#include <texteditor/basetexteditor.h>

#include "testcasedocument.hpp"

namespace testcaseeditor{

class TestCaseEditorWidget;
class TestCaseOutlineModel;

class TESTCASEEDITOR_EXPORT TestCaseEditor
    : public TextEditor::BaseTextEditor
{
  Q_OBJECT

public:
  explicit TestCaseEditor(TestCaseEditorWidget* testcaseEditorWidget);
  virtual ~TestCaseEditor();

public:
  static
  Core::Id              testCaseEditorId();
  bool                  duplicateSupported() const;
  Core::IEditor*        duplicate(QWidget *parent);
  bool                  isTemporary() const;
  Core::Id              id() const;
  TestCaseDocument*     document();
  TestCaseOutlineModel* testCaseOutlineModel();

private:
  Q_DISABLE_COPY(TestCaseEditor)
  class Private;
  Private* _d;
};

} //end namespace testcaseeditor
