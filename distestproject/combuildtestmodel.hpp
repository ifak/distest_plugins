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

#include <QObject>

namespace distestproject {

class DisTestProject;

class DISTESTPROJECTSHARED_EXPORT ComBuildTestModel
    : public QObject
{
public:
  explicit ComBuildTestModel(DisTestProject* disTestProject,
                             QObject* parent = nullptr);
  virtual ~ComBuildTestModel();

public:
  bool execute(QString* errorMessage);

//private:
//  bool buildDeclModel(distestdsl::DisTestDslErrorList* errors,
//                      QString* errorMessage);
//  bool buildSutModel(distestdsl::DisTestDslErrorList* errors,
//                     QString* errorMessage);
//  bool buildTestSuiteModel(distestdsl::DisTestDslErrorList* errors,
//                           QString* errorMessage);
//  bool buildTestSystemModel(distestdsl::DisTestDslErrorList* errors,
//                            QString* errorMessage,
//                            model::ts::TestGroupItem* testGroupItem=0);
//  bool buildTestCaseModel(distestdsl::DisTestDslErrorList* errors,
//                          QString* errorMessage,
//                          const QString& testCaseFileName,
//                          model::ts::TestGroupItem* testGroupItem=0);

private:
  Q_DISABLE_COPY(ComBuildTestModel)
  class Private;
  Private* _d;
};

} // namespace distestproject
