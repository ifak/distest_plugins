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

#include "combuildtestsystemoutlinemodel.hpp"

#include "testsystemoutlinemodel.hpp"

#include <mobata/memory_leak_start.hpp>

namespace testsystemeditor {

class ComBuildTestSystemOutlineModel::Private
{
  friend class ComBuildTestSystemOutlineModel;

  TestSystemOutlineModel*  _testsystemOutlineModel;

  Private(TestSystemOutlineModel* testsystemOutlineModel)
    : _testsystemOutlineModel(testsystemOutlineModel)
  {}
};

ComBuildTestSystemOutlineModel::ComBuildTestSystemOutlineModel(const QString& testsystemDocText,
                                                               TestSystemOutlineModel* testSystemOutlineModel,
                                                               QString praefix,
                                                               QObject* parent)
  : dslparser::testsystem::ComBuildTestSystemModel(testsystemDocText,
                                                   testSystemOutlineModel?testSystemOutlineModel->testSystemModel():0,
                                                   praefix,
                                                   false,
                                                   parent),
    _d(new Private(testSystemOutlineModel))
{
  Q_ASSERT(this->_d->_testsystemOutlineModel);
  Q_ASSERT(this->_d->_testsystemOutlineModel->testSystemModel());
}

ComBuildTestSystemOutlineModel::~ComBuildTestSystemOutlineModel()
{
  delete this->_d;
}

bool ComBuildTestSystemOutlineModel::execute(QString* errorString)
{
  bool result = ComBuildTestSystemModel::execute(errorString);
  if(!result)
    return false;

  this->_d->_testsystemOutlineModel->setModelTextLocations(this->modelTextLocations());
  this->_d->_testsystemOutlineModel->setKeywordTextLocations(this->keywordTextLocations());

  return true;
}

} // namespace testsystemeditor
