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

#include "../distestproject_global.hpp"

#include <QObject>

#include "distestresult.hpp"

namespace distestproject {

namespace distestruntime {

class DisTestSuiteRuntime;
class DisTestComponent;
class DisTestCase;

class DISTESTPROJECTSHARED_EXPORT DisTestRuntime
    : public QObject
{
  Q_OBJECT

public:
  typedef QVector<DisTestSuiteRuntime*> DisTestRuntimes;

public:
  DisTestRuntime(QObject* parent = nullptr);
  virtual ~DisTestRuntime();

public:
  virtual void reset();

public:
  virtual bool setup(QString* errorMessage);
  virtual bool start(QString* errorMessage);
  virtual bool stop(QString* errorMessage);

public:
  bool                    addDisTestSuiteRuntime(DisTestSuiteRuntime* disTestSuiteRuntime,
                                                 QString* errorMessage);
  const DisTestRuntimes&  disTestSuiteRuntimes();

public:
  bool                  testRuntimeResult();
  quint16               testCaseCount();
  QVector<DisTestCase*> executedTestCases() const;
  quint16               executedTestCaseCount();
  quint16               verdictTypeCount(DisTestResult::Verdict verdict);
  QVector<DisTestCase*> succeededTestCases();
  QVector<DisTestCase*> failedTestCases();
  const QDateTime&      startTime() const;
  const QDateTime&      endTime() const;

signals:
  void currTestCase(DisTestCase* currTestCase);
  void startTestCaseStep(const QUuid& stepId, const QString& message);
  void finishTestCaseStep(const QUuid& stepId,
                          bool result,
                          const QString& message);
  void componentRuntimeMessage(DisTestComponent* disTestComponent,
                               bool success,
                               const QString& message);
  void runtimeMessage(bool success,
                      const QString& message);
  void setuped(bool result,
               const QString& message);
  void started(bool result,
               const QString& message);
  void stopped(bool result,
               const QString& message);
  void finished(bool result,
                const QString& message);

private:
  void updateConnections(DisTestSuiteRuntime* oldTestSuiteRuntime,
                         DisTestSuiteRuntime* nextTestSuiteRuntime);

private:
  Q_DISABLE_COPY(DisTestRuntime)
  class Private;
  Private* _d;
};

} // namespace distestruntime
} // namespace distestproject
