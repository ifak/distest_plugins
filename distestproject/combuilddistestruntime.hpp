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

#include "distestproject_global.hpp"

#include <QObject>

class QDir;

namespace distestproject {

namespace distestruntime{
class DisTestSuiteRuntime;
class DisTestRuntime;
}

class DisTestProject;

class DISTESTPROJECTSHARED_EXPORT ComBuildDisTestRuntime
    : public QObject
{
  Q_OBJECT
public:
  explicit ComBuildDisTestRuntime(DisTestProject* disTestProject,
                                  distestruntime::DisTestRuntime* disTestRuntime,
                                  const QDir& buildDir,
                                  quint16 startLocalPortNumber = 6200,
                                  QObject* parent = nullptr);
  virtual ~ComBuildDisTestRuntime();

public:
  virtual bool execute(QString* errorString);

protected:
  virtual bool buildTestComponents(distestruntime::DisTestSuiteRuntime* disTestSuiteRuntime,
                                   QString* errorMessage) =0;
  virtual bool buildTestCases(distestruntime::DisTestSuiteRuntime* disTestSuiteRuntime,
                              QString* errorMessage) =0;

protected:
  quint16 freeLocalPortNumber();

private:
  Q_DISABLE_COPY(ComBuildDisTestRuntime)
  class Private;
  Private* _d;
};

} // namespace distestproject
