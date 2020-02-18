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

#include "distestproject_global.hpp"

#include <mobata/model/ts/testsuite.hpp>

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT DisTestSuite
    : public model::ts::TestSuite
{
public:
  enum DataRole
  {
    DisTestTypeRole = Qt::UserRole + 2,
    FileNameRole
  };

  enum DisTestType
  {
    TestSuiteType,
    SutType,
    TestSystemType,
    TestCaseType
  };

public:
  DisTestSuite(QObject* parent = 0);
  virtual ~DisTestSuite();

public:
  void setSutFilePath(const QString& sutFilePath);
  void setTestSystemFilePath(const QString& testSystemFilePath);

  const QString&  sutFilePath() const;
  const QString&  testSystemFilePath() const;

  bool                      addTestCase(const QString& testCaseFilePath,
                                        model::ts::TestCaseItem* testCase,
                                        QString* errorString = 0);
  void                      removeTestCase(const QString& testCaseFilePath);
  QList<QString>            testCaseFiles() const;
  model::ts::TestCaseItem*  testCaseModel(const QString& testCaseFile);
  QString                   testCaseFile(model::ts::TestCaseItem const* testCaseModel) const;

private:
  Q_DISABLE_COPY(DisTestSuite)
  class Private;
  Private*  _d;
};

} // namespace distestproject
