#include "distestsuiteruntime.hpp"

#include "distestsuite.hpp"
#include "distestcomponent.hpp"
#include "distestcase.hpp"

#include <QDateTime>
#include <QDir>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distestproject{
namespace distestruntime{

typedef DisTestSuite            TestSuiteModel;
typedef model::ts::TestCaseItem TestCaseModel;

class DisTestSuiteRuntime::Private
{
  friend class DisTestSuiteRuntime;

  TestSuiteModel const*       _testSuiteModel;
  QString                     _runtimeDir;
  int                         _repeating;
  int                         _defaultTimeout;
  QVector<DisTestComponent*>  _testComponents;
  QVector<DisTestCase*>       _origTestCases;

  ///runtime attributes
  QVector<DisTestCase*>       _execTestCases;
  QVector<DisTestCase*>       _successfulTestCases;
  QVector<DisTestCase*>       _failedTestCases;
  QVector<DisTestCase*>       _excludedTestCases;
  DisTestCase*                _currTestCase;
  int                         _currTestCaseIndex;
  bool                        _testSuiteResult;
  int                         _currExecution;
  QDateTime                   _startTime;
  QDateTime                   _endTime;

  Private(TestSuiteModel const* testSuiteModel,
          const QString& runtimeDir,
          const int repeating,
          const int defaultTimeout)
    : _testSuiteModel(testSuiteModel),
      _runtimeDir(runtimeDir),
      _repeating(repeating),
      _defaultTimeout(defaultTimeout),
      _currTestCase(0),
      _currTestCaseIndex(-1),
      _testSuiteResult(true),
      _currExecution(0)
  {}
};

bool cleanDirectory(const QString& toCleanedDirString,
                    QString* errorMessage)
{
  if(toCleanedDirString.isEmpty())
    return true;

  QDir toCleanedDir(toCleanedDirString);
  if(!toCleanedDir.exists())
  {
    if(errorMessage)
      *errorMessage=QObject::tr("directory '%1' does not exist! it cannot be cleaned!")
                    .arg(toCleanedDir.absolutePath());

    return  false;
  }

  foreach (const QFileInfo& dirFileInfo,
           toCleanedDir.entryInfoList(QDir::Files
                                      | QDir::Dirs
                                      | QDir::NoDotAndDotDot))
  {
    bool result=false;
    if(dirFileInfo.isDir())
    {
      QDir subDir(toCleanedDir);
      result=subDir.cd(dirFileInfo.fileName());
      result=subDir.removeRecursively();
    }
    else
    {
      result=toCleanedDir.remove(dirFileInfo.fileName());
    }

    if(!result)
    {
      *errorMessage=QObject::tr("The directory '%1' cannot be cleaned!")
                    .arg(toCleanedDir.absolutePath());
      return false;
    }
  }

  return  true;
}

DisTestSuiteRuntime::DisTestSuiteRuntime(DisTestSuite const* testSuiteModel,
                                         const QString& runtimeDir,
                                         const int repeating,
                                         const int defaultTimeout,
                                         QObject* parent)
  : QObject(parent),
    _d(new Private(testSuiteModel, runtimeDir, repeating, defaultTimeout))
{
  Q_ASSERT(this->_d->_testSuiteModel);
}

DisTestSuiteRuntime::~DisTestSuiteRuntime()
{
  this->reset();

  delete this->_d;
}

int DisTestSuiteRuntime::defaultTimeout() const
{
  return this->_d->_defaultTimeout;
}

int DisTestSuiteRuntime::repeating() const
{
  return this->_d->_repeating;
}

void DisTestSuiteRuntime::setRepeating(const int repeating)
{
  this->_d->_repeating=repeating;

  return;
}

void DisTestSuiteRuntime::reset()
{
  qDebug()<<"DisTestSuiteRuntime::reset() executed!";

//  QString errorMessage;
//  if(!this->_d->_runtimeDir.isEmpty())
//  {
//    if(QFileInfo(this->_d->_runtimeDir).exists())
//    {
//      bool result = cleanDirectory(this->_d->_runtimeDir, &errorMessage);
//      if(!result)
//        qWarning()<<errorMessage;
//    }
//    else
//    {
//      qWarning()<<"Runtime directory '"<<this->_d->_runtimeDir<<"' does not exists!";
//    }
//  }

  this->_d->_currTestCase=0;
  this->_d->_currTestCaseIndex=-1;
  this->_d->_testSuiteResult = true;
  this->_d->_successfulTestCases.clear();
  this->_d->_failedTestCases.clear();
  this->_d->_startTime.setDate(QDate());
  this->_d->_endTime.setDate(QDate());

  qDeleteAll(this->_d->_testComponents);
  this->_d->_testComponents.clear();

  qDeleteAll(this->_d->_origTestCases);
  this->_d->_origTestCases.clear();

  qDeleteAll(this->_d->_execTestCases);
  this->_d->_execTestCases.clear();

  return;
}

bool DisTestSuiteRuntime::setup()
{
  qDebug()<<"DisTestSuiteRuntime::setup() executed!";

  QString wholeErrorString;
  for(DisTestComponent* testComponent :
          this->_d->_testComponents)
  {
    if(!testComponent->isEnabled())
      continue;

    QString errorString;
    if(!testComponent->cleanup(&errorString))
    {
      QString errorMessage = tr("cleanup during setup of test component '%1' "
                                "of test suite '%2' failed: ")
                             .arg(testComponent->name())
                             .arg(this->testSuiteName());
      errorMessage += errorString;

      if(!wholeErrorString.isEmpty())
        wholeErrorString += QStringLiteral("\n");
      wholeErrorString += errorMessage;

      this->_d->_testSuiteResult = false;
    }
  }

  if(!this->_d->_testSuiteResult)
  {
    this->_d->_startTime = QDateTime::currentDateTime();
    this->_d->_endTime = this->_d->_startTime;

    emit finished(false, wholeErrorString);
    return false;
  }

  for(DisTestCase const* origTestCase : this->_d->_origTestCases)
    this->_d->_execTestCases.append(origTestCase->clone());

  emit runtimeMessage(true, tr("test suite setuped..."));

  return true;
}

bool DisTestSuiteRuntime::start()
{
  qDebug()<<"DisTestSuiteRuntime::start() executed!";

  this->_d->_startTime = QDateTime::currentDateTime();

  if(!this->_d->_execTestCases.count())
  {
    this->_d->_endTime = this->_d->_startTime;
    emit finished(true,
                  tr("no test cases for test suite '%1' defined")
                  .arg(this->testSuiteName()));
    return true;
  }

  qDebug()<<"DisTestSuiteRuntime::restart() executed!";

  this->_d->_currTestCaseIndex=0;
  this->_d->_currTestCase=this->_d->_execTestCases.at(this->_d->_currTestCaseIndex);
  Q_ASSERT(this->_d->_currTestCase);
  this->updateConnections(0, this->_d->_currTestCase);

  emit currTestCase(this->_d->_currTestCase);
  emit started (true,
                tr("test runtime of test suite '%1' started...")
                .arg(this->testSuiteName()));

  QString errorString;
  this->_d->_currTestCase->setup(&errorString);

  return true;
}

bool DisTestSuiteRuntime::stop()
{
  qDebug()<<"DisTestSuiteRuntime::stop() executed!";

  bool result = true;
  if(this->_d->_currTestCase)
  {
    QString errorString;
    result = this->_d->_currTestCase->stop(&errorString);
    emit stopped(result, errorString);
  }

  return result;
}

const QString& DisTestSuiteRuntime::runtimeDir() const
{
  return this->_d->_runtimeDir;
}

TestSuiteModel const* DisTestSuiteRuntime::testSuiteModel() const
{
  return this->_d->_testSuiteModel;
}

QString DisTestSuiteRuntime::testSuiteName() const
{
  if(!this->_d->_testSuiteModel)
    return QStringLiteral("");

  return this->_d->_testSuiteModel->name();
}

void DisTestSuiteRuntime::currTestCaseSetuped(bool value,
                                              const QString& message)
{
  qDebug()<<"DisTestSuiteRuntime::currTestCaseSetuped() executed!";

  if(!value)
  {
    QString errorMessage = tr("setup of test case '%1' failed: ")
                           .arg(this->_d->_currTestCase->testCaseName());
    errorMessage += message;

    this->_d->_failedTestCases.append(this->_d->_currTestCase);
    this->_d->_testSuiteResult = false;

    emit runtimeMessage(false, errorMessage);

    this->startNextTestCase();
    return;
  }

  Q_ASSERT(this->_d->_currTestCase==this->sender());
  QString messageValue = tr("test case '%1' setuped")
                         .arg(this->_d->_currTestCase->testCaseName());
  emit runtimeMessage(true, messageValue);

  QString errorString;
  this->_d->_currTestCase->start(&errorString);

  return;
}

void DisTestSuiteRuntime::currTestCaseStarted(bool value, const QString& message)
{
  qDebug()<<"DisTestSuiteRuntime::currTestCaseStarted() executed!";

  if(!value)
  {
    QString errorMessage = tr("start of test case '%1' failed: ")
                           .arg(this->_d->_currTestCase->testCaseName());
    errorMessage += message;

    this->_d->_failedTestCases.append(this->_d->_currTestCase);
    this->_d->_testSuiteResult = false;

    emit runtimeMessage(false, errorMessage);

    this->startNextTestCase();
    return;
  }

  Q_ASSERT(this->_d->_currTestCase==this->sender());
  QString messageValue = tr("test case '%1' started")
                         .arg(this->_d->_currTestCase->testCaseName());

  emit runtimeMessage(true, messageValue);

  return;
}

void DisTestSuiteRuntime::currTestCaseStopped(bool value, const QString& message)
{
  qDebug()<<"DisTestSuiteRuntime::currTestCaseStopped() executed!";

  QString stopMessage;
  if(!value)
  {
    QString errorMessage = tr("test case '%1' not successful stopped: ")
                           .arg(this->_d->_currTestCase->testCaseName());
    stopMessage += errorMessage;
  }

  stopMessage+=message;

  this->_d->_endTime = QDateTime::currentDateTime();
  this->updateConnections(this->_d->_currTestCase, 0);
  emit finished(value, tr("test runtime stopped!...%1").arg(stopMessage));

  return;
}

void DisTestSuiteRuntime::currTestCaseFinished(bool value, const QString& message)
{
  qDebug()<<"DisTestSuiteRuntime::currTestCaseFinished() executed!";

  if(!value)
  {
    QString errorMessage = tr("test case '%1' not successful finished: ")
                           .arg(this->_d->_currTestCase->testCaseName());
    errorMessage += message;

    Q_ASSERT(this->_d->_currTestCase==this->sender());
    this->_d->_failedTestCases.append(this->_d->_currTestCase);
    this->_d->_testSuiteResult = false;

    emit runtimeMessage(false, errorMessage);

    this->startNextTestCase();
    return;
  }

  Q_ASSERT(this->_d->_currTestCase==this->sender());
  this->_d->_successfulTestCases.append(this->_d->_currTestCase);
  emit runtimeMessage(true,
                      tr("test case '%1' finished")
                      .arg(this->_d->_currTestCase->testCaseName()));

  this->startNextTestCase();

  return;
}

void DisTestSuiteRuntime::startNextTestCase()
{
  DisTestCase* oldTestCase=this->_d->_currTestCase;

  ++this->_d->_currTestCaseIndex;
  if(this->_d->_currTestCaseIndex >= this->_d->_execTestCases.count())
  {
    ++this->_d->_currExecution;
    if(this->_d->_repeating >= 0
       && this->_d->_currExecution>this->_d->_repeating)
    {
      this->_d->_endTime = QDateTime::currentDateTime();
      this->updateConnections(oldTestCase, 0);
      emit finished(this->_d->_testSuiteResult, tr("test runtime finished..."));
      return;
    }
    else
    {
      foreach(DisTestCase const* origTestCase,
              this->_d->_origTestCases)
        this->_d->_execTestCases.append(origTestCase->clone());
    }
  }

  this->_d->_currTestCase=this->_d->_execTestCases.at(this->_d->_currTestCaseIndex);
  Q_ASSERT(this->_d->_currTestCase);

  qDebug()<<"start test case: "<<this->_d->_currTestCase->testCaseName();
  this->updateConnections(oldTestCase, this->_d->_currTestCase);
  emit currTestCase(this->_d->_currTestCase);

  QString errorString;
  this->_d->_currTestCase->setup(&errorString);

  return;
}

void DisTestSuiteRuntime::setTestSuiteResult(bool result)
{
  this->_d->_testSuiteResult=result;
}

void DisTestSuiteRuntime::setStartDate(const QDateTime &startTime)
{
  this->_d->_startTime = startTime;
}

void DisTestSuiteRuntime::setEndDate(const QDateTime &endTime)
{
  this->_d->_endTime = endTime;
}

void DisTestSuiteRuntime::currTestCaseErrored(const QString& message)
{
  qDebug()<<"DisTestSuiteRuntime::currTestCaseErrored() executed!";

  emit runtimeMessage(false, message);

  return;
}

const QVector<DisTestComponent*>& DisTestSuiteRuntime::testComponents() const
{
  return this->_d->_testComponents;
}

const QVector<DisTestCase*>& DisTestSuiteRuntime::testCases() const
{
  return this->_d->_origTestCases;
}

quint16 DisTestSuiteRuntime::testCaseCount()
{
  return this->_d->_origTestCases.count();
}

const QVector<DisTestCase*>& DisTestSuiteRuntime::executedTestCases() const
{
  return this->_d->_execTestCases;
}

quint16 DisTestSuiteRuntime::executedTestCaseCount()
{
  return this->_d->_execTestCases.count();
}

quint16 DisTestSuiteRuntime::verdictTypeCount(DisTestResult::Verdict verdict)
{
  if(verdict == DisTestResult::FAIL)
    return this->_d->_failedTestCases.count();
  else if(verdict == DisTestResult::SUCCESS)
    return this->_d->_successfulTestCases.count();
  else if(verdict == DisTestResult::EXCLUDE)
    return this->_d->_excludedTestCases.count();
  else if(verdict == DisTestResult::NOT_EXECUTED)
    return (this->_d->_execTestCases.count()
            - this->_d->_failedTestCases.count()
            - this->_d->_successfulTestCases.count());

  return 0;
}

bool DisTestSuiteRuntime::testSuiteResult()
{
  return this->_d->_testSuiteResult;
}

const QVector<DisTestCase*>& DisTestSuiteRuntime::failedTestCases()
{
  return this->_d->_failedTestCases;
}

const QDateTime&DisTestSuiteRuntime::startTime() const
{
  return this->_d->_startTime;
}

const QDateTime&DisTestSuiteRuntime::endTime() const
{
  return this->_d->_endTime;
}

void DisTestSuiteRuntime::addTestComponent(DisTestComponent* disTestComponent)
{
  Q_ASSERT(disTestComponent);

  this->_d->_testComponents.append(disTestComponent);

  return;
}

void DisTestSuiteRuntime::addTestCase(DisTestCase* disTestCase)
{
  Q_ASSERT(disTestCase);

  this->_d->_origTestCases.append(disTestCase);

  return;
}

void DisTestSuiteRuntime::updateConnections(DisTestCase* oldTestCase,
                                            DisTestCase* nextTestCase)
{
  qDebug()<<"DisTestSuiteRuntime::updateConnections() executed!";

  if(oldTestCase)
  {///disconnections///
    qDebug()<<  "DisTestSuiteRuntime::updateConnections() oldTestcase: " << oldTestCase->testCaseName();
    disconnect(oldTestCase, &DisTestCase::setuped,
               this, &DisTestSuiteRuntime::currTestCaseSetuped);
    disconnect(oldTestCase, &DisTestCase::started,
               this, &DisTestSuiteRuntime::currTestCaseStarted);
    disconnect(oldTestCase, &DisTestCase::finished,
               this, &DisTestSuiteRuntime::currTestCaseFinished);
    disconnect(oldTestCase, &DisTestCase::stepStarted,
               this, &DisTestSuiteRuntime::startTestCaseStep);
    disconnect(oldTestCase, &DisTestCase::stepFinished,
               this, &DisTestSuiteRuntime::finishTestCaseStep);
    disconnect(oldTestCase, &DisTestCase::ptcSetuped,
               this, &DisTestSuiteRuntime::componentRuntimeMessage);
    disconnect(oldTestCase, &DisTestCase::ptcStarted,
               this, &DisTestSuiteRuntime::componentRuntimeMessage);
    disconnect(oldTestCase, &DisTestCase::ptcStopped,
               this, &DisTestSuiteRuntime::componentRuntimeMessage);
    disconnect(oldTestCase, &DisTestCase::ptcCleanuped,
               this, &DisTestSuiteRuntime::componentRuntimeMessage);
    disconnect(oldTestCase, &DisTestCase::ptcFinished,
               this, &DisTestSuiteRuntime::componentRuntimeMessage);
    disconnect(oldTestCase, &DisTestCase::runtimeMessage,
               this, &DisTestSuiteRuntime::runtimeMessage);

    foreach(DisTestComponent* testComponent,
            oldTestCase->testComponents())
    {
      disconnect(testComponent, &DisTestComponent::setuped,
                 oldTestCase, &DisTestCase::ptcSetupedSlot);
      disconnect(testComponent, &DisTestComponent::started,
                 oldTestCase, &DisTestCase::ptcStartedSlot);
      disconnect(testComponent, &DisTestComponent::stopped,
                 oldTestCase, &DisTestCase::ptcStoppedSlot);
      disconnect(testComponent, &DisTestComponent::finished,
                 oldTestCase, &DisTestCase::ptcFinishedSlot);
      disconnect(testComponent, &DisTestComponent::cleanuped,
                 oldTestCase, &DisTestCase::ptcCleanupedSlot);
      disconnect(testComponent, &DisTestComponent::errors,
                 oldTestCase, &DisTestCase::ptcErrorsSlot);
      disconnect(testComponent, &DisTestComponent::stepStarted,
                 oldTestCase, &DisTestCase::stepStarted);
      disconnect(testComponent, &DisTestComponent::stepFinished,
                 oldTestCase, &DisTestCase::stepFinished);
    }
  }

  if(nextTestCase)
  {///connections////
    qDebug()<< "DisTestSuiteRuntime::updateConnections() nextTestcase: " << nextTestCase->testCaseName();
    connect(nextTestCase, &DisTestCase::setuped,
            this, &DisTestSuiteRuntime::currTestCaseSetuped,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::started,
            this, &DisTestSuiteRuntime::currTestCaseStarted,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::finished,
            this, &DisTestSuiteRuntime::currTestCaseFinished,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::stepStarted,
            this, &DisTestSuiteRuntime::startTestCaseStep,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::stepFinished,
            this, &DisTestSuiteRuntime::finishTestCaseStep,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::ptcSetuped,
            this, &DisTestSuiteRuntime::componentRuntimeMessage,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::ptcStarted,
            this, &DisTestSuiteRuntime::componentRuntimeMessage,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::ptcStopped,
            this, &DisTestSuiteRuntime::componentRuntimeMessage,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::ptcCleanuped,
            this, &DisTestSuiteRuntime::componentRuntimeMessage,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::ptcFinished,
            this, &DisTestSuiteRuntime::componentRuntimeMessage,
            Qt::UniqueConnection);
    connect(nextTestCase, &DisTestCase::runtimeMessage,
            this, &DisTestSuiteRuntime::runtimeMessage,
            Qt::UniqueConnection);

    foreach(DisTestComponent* testComponent,
            nextTestCase->testComponents())
    {
      connect(testComponent, &DisTestComponent::setuped,
              nextTestCase, &DisTestCase::ptcSetupedSlot,
              Qt::QueuedConnection);
      connect(testComponent, &DisTestComponent::started,
              nextTestCase, &DisTestCase::ptcStartedSlot,
              Qt::QueuedConnection);
      connect(testComponent, &DisTestComponent::stopped,
              nextTestCase, &DisTestCase::ptcStoppedSlot,
              Qt::QueuedConnection);
      connect(testComponent, &DisTestComponent::finished,
              nextTestCase, &DisTestCase::ptcFinishedSlot,
              Qt::QueuedConnection);
      connect(testComponent, &DisTestComponent::cleanuped,
              nextTestCase, &DisTestCase::ptcCleanupedSlot,
              Qt::QueuedConnection);
      connect(testComponent, &DisTestComponent::errors,
              nextTestCase, &DisTestCase::ptcErrorsSlot,
              Qt::QueuedConnection);
      connect(testComponent, &DisTestComponent::stepStarted,
              nextTestCase, &DisTestCase::stepStarted,
              Qt::QueuedConnection);
      connect(testComponent, &DisTestComponent::stepFinished,
              nextTestCase, &DisTestCase::stepFinished,
              Qt::QueuedConnection);
    }
  }

  return;
}

}//end namespace distestruntime
} // namespace distestproject
