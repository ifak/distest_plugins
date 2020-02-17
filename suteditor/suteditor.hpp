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

#include "suteditor_global.hpp"

#include <texteditor/basetexteditor.h>

#include "sutdocument.hpp"

namespace suteditor{

class SutEditorWidget;
class SutOutlineModel;

class SUTEDITOR_EXPORT SutEditor
    : public TextEditor::BaseTextEditor
{
  Q_OBJECT

public:
  explicit SutEditor(SutEditorWidget* sutEditorWidget);
  virtual ~SutEditor();

public:
  static
  Core::Id          sutEditorId();
  bool              duplicateSupported() const;
  Core::IEditor*    duplicate(QWidget *parent);
  bool              isTemporary() const;
  Core::Id          id() const;
  SutDocument*      document();
  SutOutlineModel*  sutOutlineModel();

private:
  Q_DISABLE_COPY(SutEditor)
  class Private;
  Private* _d;
};

} //end namespace suteditor
