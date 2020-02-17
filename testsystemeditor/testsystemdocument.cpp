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

#include "testsystemdocument.hpp"

#include "testsystemoutlinemodel.hpp"

#include <mobata/model/ts/testsystemitem.hpp>

#include <mobata/memory_leak_start.hpp>

using namespace model::ts;
using namespace testsystemeditor;

class TestSystemDocument::Private
{
  friend class TestSystemDocument;

  TestSystemOutlineModel* _testSystemOutlineModel;

  Private()
    : _testSystemOutlineModel(new TestSystemOutlineModel)
  {}
};

TestSystemDocument::TestSystemDocument(QObject *parent)
  : TextEditor::BaseTextDocument(parent),
    _d(new Private)
{}

TestSystemDocument::~TestSystemDocument()
{
  delete this->_d->_testSystemOutlineModel;
  delete this->_d;
}

TestSystemOutlineModel* TestSystemDocument::testSystemOutlineModel()
{
  return this->_d->_testSystemOutlineModel;
}

SutItem* TestSystemDocument::sutModel()
{
  Q_ASSERT(this->_d->_testSystemOutlineModel);

  return this->_d->_testSystemOutlineModel->sutModel();
}

TestSystemItem* TestSystemDocument::testSystemModel()
{
  Q_ASSERT(this->_d->_testSystemOutlineModel);

  return this->_d->_testSystemOutlineModel->testSystemModel();
}
