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

#include <texteditor/basehoverhandler.h>

namespace Core {
class IEditor;
}

namespace TextEditor {
class ITextEditor;
}

namespace testcaseeditor {

class TESTCASEEDITOR_EXPORT TestCaseHoverHandler
    : public TextEditor::BaseHoverHandler
{
  Q_OBJECT
public:
  TestCaseHoverHandler(QObject *parent = 0);
  virtual ~TestCaseHoverHandler();

private:
  bool acceptEditor(Core::IEditor *editor);
  void identifyMatch(TextEditor::ITextEditor *editor, int pos);
  void decorateToolTip();
};

} // namespace testcaseeditor
