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

#include "testsystemoutlinemodel.hpp"

#include <mobata/model/ts/sutitem.hpp>
#include <mobata/model/ts/testsystemitem.hpp>

#include <mobata/memory_leak_start.hpp>

using namespace model::ts;
using namespace dslparser;

namespace testsystemeditor {

class TestSystemOutlineModel::Private
{
  friend class TestSystemOutlineModel;

  SutItem*        _sutModel;
  TestSystemItem* _testSystemModel;

  ModelTextLocations  _modelTextLocations;
  TokenTextLocations  _keywordTextLocations;
};

TestSystemOutlineModel::TestSystemOutlineModel(QObject* parent)
  : dsleditor::DslOutlineModel(parent),
    _d(new Private)
{
  this->_d->_sutModel = new SutItem;
  this->_d->_testSystemModel = new model::ts::TestSystemItem(this->_d->_sutModel);

  this->invisibleRootItem()->appendRow(this->_d->_testSystemModel);
}

TestSystemOutlineModel::~TestSystemOutlineModel()
{
  delete this->_d->_sutModel;
  delete this->_d;
}

SutItem* TestSystemOutlineModel::sutModel()
{
  return this->_d->_sutModel;
}

TestSystemItem* TestSystemOutlineModel::testSystemModel()
{
  return this->_d->_testSystemModel;
}

void TestSystemOutlineModel::reset()
{
  this->_d->_sutModel->reset();
  this->_d->_testSystemModel->reset();

  return dsleditor::DslOutlineModel::reset();
}

} // namespace testsystemeditor
