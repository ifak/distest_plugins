#include "distestcase.hpp"

#include "distestcomponent.hpp"
#include "distestresult.hpp"

#include <mobata/model/ts/ts.hpp>

#include <QFileInfo>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distestproject{
namespace distestruntime {

typedef model::ts::TestCaseItem TestCaseModel;

class DisTestCase::Private
{
  friend class DisTestCase;

  TestCaseModel const*              _testCaseModel;
  QFileInfo                         _testCaseFileInfo;
  QVector<DisTestComponent*>        _testComponents;
  DisTestCase::DisTestCaseState     _state;
  DisTestResult                     _testResult;
  QList<ProjectExplorer::BaseError> _errors;

  QVector<DisTestComponent*>        _startedTestComponents;
  QVector<DisTestComponent*>        _runningTestComponents;

  Private(TestCaseModel const* testCaseModel,
          const QString& testCaseFileName,
          const QVector<DisTestComponent*>& testComponents,
          DisTestCase::DisTestCaseState state)
    : _testCaseModel(testCaseModel),
      _testCaseFileInfo(testCaseFileName),
      _testComponents(testComponents),
      _state(state)
  {}
};

DisTestCase::DisTestCase(TestCaseModel const* testCaseModel,
                         const QString& testCaseFileName,
                         const QVector<DisTestComponent*>& testComponents,
                         QObject *parent)
  : QObject(parent),
    _d(new Private(testCaseModel, testCaseFileName, testComponents, Idle))
{
  Q_ASSERT(this->_d->_testCaseModel);
  Q_ASSERT(this->_d->_testCaseFileInfo.exists());
}

DisTestCase::~DisTestCase()
{
  delete this->_d;
}

DisTestCase*DisTestCase::clone() const
{
  return new DisTestCase(this->_d->_testCaseModel,
                         this->_d->_testCaseFileInfo.absoluteFilePath(),
                         this->_d->_testComponents,
                         this->parent());
}

QString DisTestCase::testCaseName() const
{
  if(!this->_d->_testCaseModel)
    return QStringLiteral("");

  return this->_d->_testCaseModel->name();
}

DisTestComponent* DisTestCase::testComponent(const QString& compName)
{
  foreach(DisTestComponent* testComponent, this->_d->_testComponents)
    if(testComponent->name().compare(compName, Qt::CaseInsensitive) == 0)
      return testComponent;

  return 0;
}

TestCaseModel const* DisTestCase::testCaseModel() const
{
  return this->_d->_testCaseModel;
}

QString DisTestCase::testCaseFilePath() const
{
  return this->_d->_testCaseFileInfo.absoluteFilePath();
}

DisTestCase::DisTestCaseState DisTestCase::disTestCaseState() const
{
  return this->_d->_state;
}

const DisTestResult& DisTestCase::testResult() const
{
  return this->_d->_testResult;
}

const DisTestCase::DisTestComponents& DisTestCase::testComponents() const
{
  return  this->_d->_testComponents;
}

bool DisTestCase::setup(QString* errorString)
{
  Q_ASSERT(errorString);

  qDebug()<<"DisTestCase::setup() executed! name: " << this->testCaseName();

  ////prepare test components/////
  for (DisTestComponent* testComponent :
           this->_d->_testComponents)
  {
    if(!testComponent->isEnabled())
      continue;

    bool result = testComponent->setup(errorString);
    if(!result)
    {
      qDebug()<<" ERROR: DisTestCase::setup() failled! name: " << this->testCaseName();
      this->_d->_testResult.setVerdict(DisTestResult::FAIL);
      emit setuped(false, *errorString);
      return false;
    }
  }

  emit runtimeMessage(true,
                      tr("all test components of test case '%1' setuped!")
                      .arg(this->testCaseModel()->name()));

  emit setuped(true,
               tr("test case '%1' setuped!")
               .arg(this->testCaseModel()->name()));

  return true;
}

void DisTestCase::ptcSetupedSlot(DisTestComponent* disTestComponent,
                                 bool value,
                                 QString message)
{
  qDebug()<<"DisTestCase::setup() executed! name: " << this->testCaseName();

  emit ptcSetuped(disTestComponent, value, message);

  //TODO: DisTestCase::ptcSetupedSlot() not implemented yet!

  return;
}

bool DisTestCase::start(QString *errorString)
{
  Q_ASSERT(errorString);

  qDebug()<<"DisTestCase::start() executed! name: " << this->testCaseName();

  ///start test components//////////
  foreach (DisTestComponent* testComponent, this->_d->_testComponents)
  {
    if(!testComponent->isEnabled())
      continue;

    this->_d->_startedTestComponents.append(testComponent);
    this->_d->_runningTestComponents.append(testComponent);

    bool result = testComponent->start(errorString);
    if(!result)
    {
      this->_d->_testResult.setVerdict(DisTestResult::FAIL);
      emit started(false, *errorString);
      return false;
    }
  }

  return true;
}

void DisTestCase::ptcStartedSlot(DisTestComponent* disTestComponent,
                                 bool value,
                                 QString message)
{
  qDebug()<<"DisTestCase::ptcStartedSlot() executed! name: " << this->testCaseName();

  Q_ASSERT(disTestComponent);

  emit ptcStarted(disTestComponent, value, message);

  if(!value)
  {
    QString errorMessage = message;

    QString errorString;
    this->stop(&errorString);
    this->cleanup(&errorString);

    emit finished(false, errorMessage + errorString);

    return;
  }

  ///remove from started...
  this->_d->_startedTestComponents.removeAll(disTestComponent);
  if(this->_d->_startedTestComponents.isEmpty())
    emit started(true,
                 tr("test case '%1' started")
                 .arg(this->testCaseModel()->name()));

  return;
}

bool DisTestCase::stop(QString* errorString)
{
  qDebug()<<"DisTestCase::stop() executed! name: " << this->testCaseName();

  bool result = true;
  foreach(DisTestComponent* testComponent,
          this->_d->_testComponents)
  {
    if(!testComponent->isEnabled())
      continue;

    bool stopSuccess = testComponent->stop(errorString);
    if(result)
      result = stopSuccess;
  }

  bool cleanupSuccess = this->cleanup(errorString);
  if(result)
    result = cleanupSuccess;

  return result;
}

void DisTestCase::ptcStoppedSlot(DisTestComponent* disTestComponent,
                                 bool value,
                                 QString message)
{
  qDebug()<<"DisTestCase::ptcStoppedSlot() executed! name: " << this->testCaseName();

  emit ptcStopped(disTestComponent, value, message);

  //TODO: DisTestCase::ptcStoppedSlot() not implemented yet!

  return;
}

void DisTestCase::ptcFinishedSlot(DisTestComponent* disTestComponent,
                                  bool value,
                                  QString message)
{
  qDebug()<<"DisTestCase::ptcFinishedSlot() executed! name: " << this->testCaseName();

  Q_ASSERT(disTestComponent);
  qDebug()<<"test component '"<<disTestComponent->name()<<"' finished!";

  emit ptcFinished(disTestComponent, value, message);

  if(!value)
  {
    QString errorMessage = message;

    QString errorString;
    this->stop(&errorString);
    this->cleanup(&errorString);

    this->_d->_testResult.setVerdict(DisTestResult::FAIL);
    qDebug()<<"DisTestCase::ptcFinishedSlot() Testcase: " << this->testCaseName() <<" testResult = "<< this->_d->_testResult.toString();
    emit finished(false, errorMessage + errorString);

    return;
  }

  ///remove from running...
  this->_d->_runningTestComponents.removeAll(disTestComponent);
  if(this->_d->_runningTestComponents.isEmpty())
  {

    this->_d->_testResult.setVerdict(DisTestResult::SUCCESS);
    qDebug()<<"DisTestCase::ptcFinishedSlot() Testcase: " << this->testCaseName() <<" testResult = "<< this->_d->_testResult.toString();
    emit finished(true,
                  tr("test case '%1' finished")
                  .arg(this->testCaseModel()->name()));
  }
  return;
}

bool DisTestCase::cleanup(QString* errorString)
{
  Q_ASSERT(errorString);

  qDebug()<<"DisTestCase::cleanup() executed! name: " << this->testCaseName();

  this->_d->_startedTestComponents.clear();
  this->_d->_runningTestComponents.clear();

  foreach(DisTestComponent* testComponent,
          this->_d->_testComponents)
  {
    if(!testComponent->isEnabled())
      continue;

    if(!testComponent->cleanup(errorString))
    {
      emit cleanuped(false, *errorString);
      return false;
    }
  }

  emit cleanuped(true,
                 tr("test case '%1' cleanuped")
                 .arg(this->testCaseModel()->name()));

  return true;
}

const QList<ProjectExplorer::BaseError>& DisTestCase::errors() const
{
  return this->_d->_errors;
}

void DisTestCase::addError(const ProjectExplorer::BaseError& newError)
{
  this->_d->_errors.append(newError);

  return;
}

void DisTestCase::ptcCleanupedSlot(DisTestComponent* disTestComponent,
                                   bool value,
                                   QString message)
{
  qDebug()<<"DisTestCase::ptcCleanupedSlot() executed! name: " << this->testCaseName();

  emit ptcCleanuped(disTestComponent, value, message);

  //TODO: DisTestCase::ptcCleanupedSlot() not implemented yet!

  return;
}

void DisTestCase::ptcErrorsSlot(DisTestComponent* disTestComponent,
                                QStringList errors)
{
  qDebug()<<"DisTestCase::ptcErrorsSlot() executed! name: " << this->testCaseName();
  Q_ASSERT(disTestComponent);

  if(errors.count())
    this->_d->_testResult.setVerdict(DisTestResult::FAIL);

  QString errorMessage = tr("error for test component %1: ")
                         .arg(disTestComponent->name());
  foreach(const QString& errorString,
          errors)
  {
    if(!errorMessage.isEmpty())
      errorMessage += QStringLiteral("\n");
    errorMessage += errorString;
  }

  QString errorString;
  this->stop(&errorString);
  this->cleanup(&errorString);

  this->_d->_testResult.setErrorMessage(errorMessage);
  this->_d->_testResult.setVerdict(DisTestResult::FAIL);
  emit finished(false, errorMessage + errorString);

  return;
}

} // namespace distestruntime
} // namespace distestproject
