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

#include <QObject>

namespace distestproject {

namespace distestruntime {
class DisTestRuntime;
}

class TestReportTableModel;

class TestReportBuilder : public QObject
{
  Q_OBJECT
public:
  TestReportBuilder(QObject* parent = nullptr);
  ~TestReportBuilder();

private:
  void reset();

public:
  void buildReport(distestruntime::DisTestRuntime* disTestRuntime,
                   QString* errorString=0);

public:
  Q_INVOKABLE int getSucceededCount();
  Q_INVOKABLE int getFailedCount();
  Q_INVOKABLE int getExcludetCount();
  Q_INVOKABLE int getNotExecutedCount();

  TestReportTableModel* disTestRuntimeModel();
  TestReportTableModel* statisticModel();
  TestReportTableModel* testCasesModel();


private:
  int _succeededCount;
  int _failedCount;
  int _excludetCount;
  int _notExecuedCount;

  TestReportTableModel* _testSuiteModel;
  TestReportTableModel* _statisticModel;
  TestReportTableModel* _testCasesModel;
};

} // distestproject
