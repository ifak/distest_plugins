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

#include "testsystemeditor_global.hpp"

#include <texteditor/basetexteditor.h>

#include "testsystemdocument.hpp"

namespace testsystemeditor{

class TestSystemEditorWidget;
class TestSystemOutlineModel;

class TESTSYSTEMEDITOR_EXPORT TestSystemEditor
    : public TextEditor::BaseTextEditor
{
  Q_OBJECT

public:
  explicit TestSystemEditor(TestSystemEditorWidget* testSystemEditorWidget);
  virtual ~TestSystemEditor();

public:
  static
  Core::Id          testSystemEditorId();
  bool              duplicateSupported() const;
  Core::IEditor*    duplicate(QWidget *parent);
  bool              isTemporary() const;
  Core::Id          id() const;
  TestSystemDocument*      document();
  TestSystemOutlineModel*  testSystemOutlineModel();

private:
  Q_DISABLE_COPY(TestSystemEditor)
  class Private;
  Private* _d;
};

} //end namespace testsystemeditor
