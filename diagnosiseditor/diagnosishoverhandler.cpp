/*
 *  This file is part of Diagnosis Editor Plugin for AppCreator based application.
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

#include "diagnosishoverhandler.hpp"

#include "diagnosiseditor.hpp"
#include "diagnosiseditorwidget.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace Core;

namespace diagnosiseditor {

DiagnosisHoverHandler::DiagnosisHoverHandler(QObject* parent)
  : BaseHoverHandler(parent)
{}

DiagnosisHoverHandler::~DiagnosisHoverHandler()
{}

bool DiagnosisHoverHandler::acceptEditor(IEditor* editor)
{
  if (qobject_cast<DiagnosisEditor*>(editor))
    return true;
  return false;
}

void DiagnosisHoverHandler::identifyMatch(TextEditor::ITextEditor* editor, int pos)
{
  if (DiagnosisEditorWidget* diagnosisEditorWidget = qobject_cast<DiagnosisEditorWidget *>(editor->widget()))
  {
    if (! diagnosisEditorWidget->extraSelectionTooltip(pos).isEmpty())
      this->setToolTip(diagnosisEditorWidget->extraSelectionTooltip(pos));
  }
}

void DiagnosisHoverHandler::decorateToolTip()
{
  if (Qt::mightBeRichText(toolTip()))
    this->setToolTip(Qt::escape(toolTip()));
}

} // namespace diagnosiseditor
