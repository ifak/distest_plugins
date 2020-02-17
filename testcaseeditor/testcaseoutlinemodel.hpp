/*
 * This file is part of mobata.
 *
 * mobata is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * mobata is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with mobata.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <dsleditor/dsloutlinemodel.hpp>

#include <mobata/model/ts/sutitem.hpp>
#include <mobata/model/ts/testsystemitem.hpp>
#include <mobata/model/ts/testcaseitem.hpp>

namespace testcaseeditor {

using model::ts::SutItemPtr;
using model::ts::TestSystemItemPtr;
using model::ts::TestCaseItemPtr;

class TestCaseOutlineModel
    : public dsleditor::DslOutlineModel
{
  friend class ComBuildTestCaseOutlineModel;

public:
  TestCaseOutlineModel(QObject* parent = 0);
  virtual ~TestCaseOutlineModel();

public:
  const SutItemPtr&         sutModel() const;
  const TestSystemItemPtr&  testSystemModel() const;
  const TestCaseItemPtr&    testCaseModel() const;

public:
  virtual void reset();

private:
  Q_DISABLE_COPY(TestCaseOutlineModel)
  class Private;
  Private* _d;
};

} // namespace testcaseeditor
