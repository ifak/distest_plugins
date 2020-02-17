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

#include "diagnosisoutlinemodel.hpp"

#include <mobata/model/diagnosis/diagnosisitem.hpp>

#include <mobata/memory_leak_start.hpp>

using namespace model::diagnosis;
using namespace dslparser;

namespace diagnosiseditor {

class DiagnosisOutlineModel::Private
{
  friend class DiagnosisOutlineModel;

  DiagnosisItem*   _diagnosisModel;
};

DiagnosisOutlineModel::DiagnosisOutlineModel(QObject* parent)
  : dsleditor::DslOutlineModel(parent),
    _d(new Private)
{
  this->_d->_diagnosisModel = new model::diagnosis::DiagnosisItem;
  this->invisibleRootItem()->appendRow(this->_d->_diagnosisModel);
}

DiagnosisOutlineModel::~DiagnosisOutlineModel()
{
  delete this->_d->_diagnosisModel;

  delete this->_d;
}

QList<DiagnosisItem*> DiagnosisOutlineModel::importItems()
{
  return this->_d->_diagnosisModel->importItems();
}

DiagnosisItem* DiagnosisOutlineModel::diagnosisModel()
{
  return this->_d->_diagnosisModel;
}

void DiagnosisOutlineModel::reset()
{
//  for(auto import: _d->_importItems){
//      delete import;
//  }
//  _d->_importItems.clear();
  this->_d->_diagnosisModel->reset();

  return dsleditor::DslOutlineModel::reset();
}

} // namespace diagnosiseditor
