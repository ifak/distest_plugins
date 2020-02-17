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

#include "diagnosisdocument.hpp"

#include "diagnosisoutlinemodel.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace model::ts;
using namespace diagnosiseditor;

class DiagnosisDocument::Private
{
  friend class DiagnosisDocument;

  DiagnosisOutlineModel*  _diagnosisOutlineModel;

  Private()
    : _diagnosisOutlineModel(0)
  {}
};

DiagnosisDocument::DiagnosisDocument(QObject *parent)
  : TextEditor::BaseTextDocument(parent),
    _d(new Private)
{
  this->_d->_diagnosisOutlineModel = new DiagnosisOutlineModel();
}

DiagnosisDocument::~DiagnosisDocument()
{
  delete this->_d->_diagnosisOutlineModel;
  delete this->_d;
}

DiagnosisOutlineModel* DiagnosisDocument::diagnosisOutlineModel()
{
  return this->_d->_diagnosisOutlineModel;
}
