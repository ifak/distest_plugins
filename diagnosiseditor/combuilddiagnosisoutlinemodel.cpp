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
#include "combuilddiagnosisoutlinemodel.hpp"

#include "diagnosisoutlinemodel.hpp"

#include <mobata/memory_leak_start.hpp>

namespace diagnosiseditor {

class ComBuildDiagnosisOutlineModel::Private
{
  friend class ComBuildDiagnosisOutlineModel;

  DiagnosisOutlineModel*  _diagnosisOutlineModel;
  dslparser::diagnosis::ComBuildDiagnosisModel::FileType _type;

  Private(DiagnosisOutlineModel* diagnosisOutlineModel,dslparser::diagnosis::ComBuildDiagnosisModel::FileType type)
    : _diagnosisOutlineModel(diagnosisOutlineModel),_type(type)
  {}
};

ComBuildDiagnosisOutlineModel::ComBuildDiagnosisOutlineModel(const QString& diagnosisDocText,
                                                           DiagnosisOutlineModel* diagnosisOutlineModel,
                                                           QString praefix, FileType type,
                                                           QObject* parent)
  : dslparser::diagnosis::ComBuildDiagnosisModel(diagnosisDocText,
                                               diagnosisOutlineModel?diagnosisOutlineModel->diagnosisModel():0,
                                               praefix,
                                               false,
                                               parent),
    _d(new Private(diagnosisOutlineModel,type))
{
  Q_ASSERT(this->_d->_diagnosisOutlineModel);
  Q_ASSERT(this->_d->_diagnosisOutlineModel->diagnosisModel());
}

ComBuildDiagnosisOutlineModel::~ComBuildDiagnosisOutlineModel()
{
  delete this->_d;
}

bool ComBuildDiagnosisOutlineModel::execute(QString* errorString)
{
  bool result = ComBuildDiagnosisModel::execute(errorString,_d->_type);
  if(!result)
    return false;

  this->_d->_diagnosisOutlineModel->setModelTextLocations(this->modelTextLocations());
  this->_d->_diagnosisOutlineModel->setKeywordTextLocations(this->keywordTextLocations());

  return true;
}

} // namespace diagnosiseditor
