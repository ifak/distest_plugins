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

#include <coreplugin/editormanager/ieditorfactory.h>

namespace TextEditor {
class  TextEditorActionHandler;
}

namespace testcaseeditor{

class TestCaseEditorPlugin;

class TestCaseEditorFactory
    : public Core::IEditorFactory
{
  Q_OBJECT

public:
  explicit TestCaseEditorFactory(TestCaseEditorPlugin* owner);
  virtual ~TestCaseEditorFactory();

public:
  QStringList     mimeTypes() const;
  Core::Id        id() const;
  QString         displayName() const;
  Core::IEditor*  createEditor(QWidget *parent);

private:
  Q_DISABLE_COPY(TestCaseEditorFactory)
  class Private;
  Private* _d;
};

} //end namespace testcaseeditor
