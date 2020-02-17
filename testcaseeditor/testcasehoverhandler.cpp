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

#include "testcasehoverhandler.hpp"

#include "testcaseeditor.hpp"
#include "testcaseeditorwidget.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace Core;

namespace testcaseeditor {

TestCaseHoverHandler::TestCaseHoverHandler(QObject* parent)
  : BaseHoverHandler(parent)
{}

TestCaseHoverHandler::~TestCaseHoverHandler()
{}

bool TestCaseHoverHandler::acceptEditor(IEditor* editor)
{
  if (qobject_cast<TestCaseEditor*>(editor))
    return true;
  return false;
}

void TestCaseHoverHandler::identifyMatch(TextEditor::ITextEditor* editor, int pos)
{
  if (TestCaseEditorWidget* testCaseEditorWidget = qobject_cast<TestCaseEditorWidget *>(editor->widget()))
  {
    if (! testCaseEditorWidget->extraSelectionTooltip(pos).isEmpty())
      this->setToolTip(testCaseEditorWidget->extraSelectionTooltip(pos));
  }
}

void TestCaseHoverHandler::decorateToolTip()
{
  if (Qt::mightBeRichText(toolTip()))
    this->setToolTip(Qt::escape(toolTip()));
}

} // namespace testcaseeditor
