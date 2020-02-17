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

#pragma once

#include "diagnosiseditor_global.hpp"

#include <texteditor/basetexteditor.h>

#include "diagnosisdocument.hpp"

namespace diagnosiseditor{

class DiagnosisEditorWidget;
class DiagnosisOutlineModel;

class DIAGNOSISEDITOR_EXPORT DiagnosisEditor
    : public TextEditor::BaseTextEditor
{
  Q_OBJECT

public:
  explicit DiagnosisEditor(DiagnosisEditorWidget* diagnosisEditorWidget);
  virtual ~DiagnosisEditor();

public:
  static
  Core::Id              diagnosisEditorId();
  bool                  duplicateSupported() const;
  Core::IEditor*        duplicate(QWidget *parent);
  bool                  isTemporary() const;
  Core::Id              id() const;
  DiagnosisDocument*     document();
  DiagnosisOutlineModel* diagnosisOutlineModel();

private:
  Q_DISABLE_COPY(DiagnosisEditor)
  class Private;
  Private* _d;
};

} //end namespace diagnosiseditor
