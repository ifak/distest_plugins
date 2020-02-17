/*
 *  This file is part of Test System Editor Plugin for AppCreator based application.
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

#include "testsystemhoverhandler.hpp"

#include "testsystemeditor.hpp"
#include "testsystemeditorwidget.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace Core;

namespace testsystemeditor {

TestSystemHoverHandler::TestSystemHoverHandler(QObject* parent)
  : TextEditor::BaseHoverHandler(parent)
{}

TestSystemHoverHandler::~TestSystemHoverHandler()
{}

bool TestSystemHoverHandler::acceptEditor(IEditor* editor)
{
  if (qobject_cast<TestSystemEditor*>(editor))
    return true;
  return false;
}

void TestSystemHoverHandler::identifyMatch(TextEditor::ITextEditor* editor, int pos)
{
  if (TestSystemEditorWidget* testSystemEditorWidget = qobject_cast<TestSystemEditorWidget *>(editor->widget()))
  {
    if (! testSystemEditorWidget->extraSelectionTooltip(pos).isEmpty())
      this->setToolTip(testSystemEditorWidget->extraSelectionTooltip(pos));
  }

  return;
}

void TestSystemHoverHandler::decorateToolTip()
{
  if (Qt::mightBeRichText(toolTip()))
    this->setToolTip(Qt::escape(toolTip()));

  return;
}

} // namespace testsystemeditor
