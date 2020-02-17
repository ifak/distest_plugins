/*
 *  This file is part of Test Case Editor Plugin for AppCreator based application.
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

#include "testcasedocument.hpp"

#include "testcaseoutlinemodel.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace model::ts;
using namespace testcaseeditor;

class TestCaseDocument::Private
{
  friend class TestCaseDocument;

  TestCaseOutlineModel*  _testCaseOutlineModel;

  Private()
    : _testCaseOutlineModel(0)
  {}
};

TestCaseDocument::TestCaseDocument(QObject *parent)
  : TextEditor::BaseTextDocument(parent),
    _d(new Private)
{
  this->_d->_testCaseOutlineModel = new TestCaseOutlineModel();
}

TestCaseDocument::~TestCaseDocument()
{
  delete this->_d->_testCaseOutlineModel;
  delete this->_d;
}

TestCaseOutlineModel* TestCaseDocument::testCaseOutlineModel()
{
  return this->_d->_testCaseOutlineModel;
}
