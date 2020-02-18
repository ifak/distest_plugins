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

#include "../distestproject_global.hpp"

#include "distestresult.hpp"

#include <projectexplorer/baseerror.hpp>

#include <QObject>
#include <QUuid>

class QDir;

namespace distestproject{
class DisTestSuite;

namespace distestruntime {

class DisTestComponent;
class DisTestCase;

bool DISTESTPROJECTSHARED_EXPORT
cleanDirectory(const QString& toCleanedDirString,
               QString* errorMessage);

class DISTESTPROJECTSHARED_EXPORT DisTestSuiteRuntime
    : public QObject
{
  Q_OBJECT

public:
  DisTestSuiteRuntime(DisTestSuite const* testSuiteModel,
                      const QString& runtimeDir = QStringLiteral(""),
                      const int repeating =0,
                      const int defaultTimeout = 20000,
                      QObject* parent = 0);
  virtual ~DisTestSuiteRuntime();

public:
  virtual void reset();

public:
  virtual bool setup();
  virtual bool start();
  virtual bool stop();

public:
  const QList<ProjectExplorer::BaseError>&  errors() const;

public:
  int                               defaultTimeout() const;
  void                              setDefaultTimeout(const int defaultTimeout);
  int                               repeating() const;
  void                              setRepeating(const int repeating);
  const QString&                    runtimeDir() const;
  DisTestSuite const*               testSuiteModel() const;
  QString                           testSuiteName() const;
  const QVector<DisTestComponent*>& testComponents() const;
  const QVector<DisTestCase*>&      testCases() const;
  quint16                           testCaseCount();
  const QVector<DisTestCase*>&      executedTestCases() const;
  quint16                           executedTestCaseCount();
  quint16                           verdictTypeCount(DisTestResult::Verdict verdict);
  bool                              testSuiteResult();
  const QVector<DisTestCase*>&      failedTestCases();
  const QDateTime&                  startTime() const;
  const QDateTime&                  endTime() const;

public:
  void addTestComponent(DisTestComponent* disTestComponent);
  void addTestCase(DisTestCase* disTestCase);

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

protected:
  void startNextTestCase();
  void setTestSuiteResult(bool result);
  void setStartDate(const QDateTime& startTime);
  void setEndDate(const QDateTime& endTime);

private slots:
  void currTestCaseSetuped(bool value, const QString& message);
  void currTestCaseStarted(bool value, const QString& message);
  void currTestCaseStopped(bool value, const QString& message);
  void currTestCaseFinished(bool value, const QString& message);
  void currTestCaseErrored(const QString& message);

private:
  bool restart();
  void updateConnections(DisTestCase* oldTestCase,
                         DisTestCase* nextTestCase);

private:
  Q_DISABLE_COPY(DisTestSuiteRuntime)
  class Private;
  Private* _d;
};

} // namespace distestruntime
} // namespace distestproject
