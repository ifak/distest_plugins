/*
 * This file is part of distest_plugins.
 *
 * distest_plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * distest_plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with distest_plugins.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <dslparser/testcase/combuildtestcasemodel.hpp>

namespace testcaseeditor {

class TestCaseOutlineModel;

class ComBuildTestCaseOutlineModel
    : public dslparser::testcase::ComBuildTestCaseModel
{
public:
  ComBuildTestCaseOutlineModel(const QString& testCaseDocText,
                               TestCaseOutlineModel* testcaseOutlineModel,
                               const QString& praefix,
                               QObject* parent = 0);
  virtual ~ComBuildTestCaseOutlineModel();

public:
  bool execute(QString* errorString = 0);

private:
  Q_DISABLE_COPY(ComBuildTestCaseOutlineModel)
  class Private;
  Private* _d;
};

} // namespace testcaseeditor
