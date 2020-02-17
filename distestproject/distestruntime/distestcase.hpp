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
#ifndef DISTESTPROJECT_DISTESTRUNTIME_DISTESTCASE_HPP
#define DISTESTPROJECT_DISTESTRUNTIME_DISTESTCASE_HPP

#include "../distestproject_global.hpp"

#include <projectexplorer/baseerror.hpp>

#include <QObject>
#include <QUuid>

namespace model{ namespace ts{
class TestCaseItem;
}}

namespace distestproject{
namespace distestruntime {

class DisTestComponent;
class DisTestResult;

class DISTESTPROJECTSHARED_EXPORT DisTestCase
    : public QObject
{
  Q_OBJECT

  friend class DisTestSuiteRuntime;

public:
  typedef QVector<DisTestComponent*>  DisTestComponents;

public:
  enum DisTestCaseState
  {
    Idle,
    SetupRequest,
    Setuped,
    StartRequest,
    Started,
    StopRequest,
    Stopped,
    CleanupRequest,
    Cleanuped
  };

public:
  explicit DisTestCase(model::ts::TestCaseItem const* testCaseModel,
                       const QString& testCaseFilePath,
                       const DisTestComponents& testComponents,
                       QObject *parent = 0);
  virtual ~DisTestCase();

public:
  virtual DisTestCase* clone() const;

public:
  model::ts::TestCaseItem const*  testCaseModel() const;
  QString                         testCaseName() const;
  QString                         testCaseFilePath() const;
  DisTestCaseState                disTestCaseState() const;
  const DisTestResult&            testResult() const;

public:
  virtual bool setup(QString* errorString);
  virtual bool start(QString* errorString);
  virtual bool stop(QString* errorString);
  virtual bool cleanup(QString* errorString);

signals:
  void setuped(bool value, QString message);
  void started(bool value, QString message);
  void stopped(bool value, QString message);
  void cleanuped(bool value, QString message);
  void finished(bool value, QString message);

  void ptcSetuped(DisTestComponent* disTestComponent,
                  bool value,
                  QString message);
  void ptcStarted(DisTestComponent* disTestComponent,
                  bool value,
                  QString message);
  void ptcStopped(DisTestComponent* disTestComponent,
                  bool value,
                  QString message);
  void ptcCleanuped(DisTestComponent* disTestComponent,
                    bool value,
                    QString message);
  void ptcFinished(DisTestComponent* disTestComponent,
                   bool value,
                   QString message);
  void ptcErrors(DisTestComponent* disTestComponent,
                 QString message);

  void stepStarted(QUuid stepId, QString message);
  void stepFinished(QUuid stepId,
                    bool result,
                    QString message);

  void runtimeMessage(bool isError, QString message);

public:
  const QList<ProjectExplorer::BaseError>&  errors() const;
  QString                                   errorString() const;

protected:
  void                      addError(const ProjectExplorer::BaseError& newError);
  const DisTestComponents&  testComponents() const;
  DisTestComponent*         testComponent(const QString& compName);

protected slots:
  virtual void ptcSetupedSlot(DisTestComponent* disTestComponent,
                              bool value,
                              QString message);
  virtual void ptcStartedSlot(DisTestComponent* disTestComponent,
                              bool value,
                              QString message);
  virtual void ptcStoppedSlot(DisTestComponent* disTestComponent,
                              bool value,
                              QString message);
  virtual void ptcFinishedSlot(DisTestComponent* disTestComponent,
                               bool value,
                               QString message);
  virtual void ptcCleanupedSlot(DisTestComponent* disTestComponent,
                                bool value,
                                QString message);
  virtual void ptcErrorsSlot(DisTestComponent* disTestComponent,
                             QStringList errors);

protected:
  void              setDisTestCaseState(DisTestCaseState newState);

private:
  Q_DISABLE_COPY(DisTestCase)
  class Private;
  Private* _d;
};

} // namespace distestruntime
} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTRUNTIME_DISTESTCASE_HPP
