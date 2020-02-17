#include "distestruntime.hpp"

#include "distestsuiteruntime.hpp"
#include "distestcomponent.hpp"
#include "distestcase.hpp"

#include <mobata/utils/functors.hpp>

#include <QVector>
#include <QDateTime>
#include <QDebug>

namespace distestproject {
namespace distestruntime {

class DisTestRuntime::Private
{
  friend class DisTestRuntime;


  DisTestRuntimes _disTestSuiteRuntimes;
  QDateTime       _startTime;
  QDateTime       _endTime;

  Private()
  {}
};

DisTestRuntime::DisTestRuntime(QObject* parent)
  : QObject(parent), _d(new Private())
{}

DisTestRuntime::~DisTestRuntime()
{
  qDeleteAll(this->_d->_disTestSuiteRuntimes);
  this->_d->_disTestSuiteRuntimes.clear();

  delete this->_d;

  return;
}

void DisTestRuntime::reset()
{
  for(DisTestSuiteRuntime* disTestSuiteRuntime
      : this->_d->_disTestSuiteRuntimes)
    disTestSuiteRuntime->reset();

  qDeleteAll(this->_d->_disTestSuiteRuntimes);
  this->_d->_disTestSuiteRuntimes.clear();

  return;
}

bool DisTestRuntime::setup(QString* errorMessage)
{
  if(this->_d->_disTestSuiteRuntimes.isEmpty())
    return true;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    utils::AddPtrString(errorMessage)<<"currently only one distestgroup "
                                       "is supported for execution!";
    return false;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->setup();
}

bool DisTestRuntime::start(QString* errorMessage)
{
  if(this->_d->_disTestSuiteRuntimes.isEmpty())
    return true;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    utils::AddPtrString(errorMessage)<<"currently only one distestgroup "
                                       "is supported for execution!";
    return false;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->start();
}

bool DisTestRuntime::stop(QString* errorMessage)
{
  if(this->_d->_disTestSuiteRuntimes.isEmpty())
    return true;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    utils::AddPtrString(errorMessage)<<"currently only one distestgroup "
                                       "is supported for execution!";
    return false;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->stop();
}

bool DisTestRuntime::addDisTestSuiteRuntime(DisTestSuiteRuntime* disTestSuiteRuntime,
                                            QString* errorMessage)
{
  if(!disTestSuiteRuntime)
    return false;

  if(this->_d->_disTestSuiteRuntimes.count())
  {
    utils::AddPtrString(errorMessage)<<"currently only one distestgroup "
                                       "is supported for execution!";
    return false;
  }

  //create connections
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::componentRuntimeMessage,
          this, &DisTestRuntime::componentRuntimeMessage);
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::currTestCase,
          this, &DisTestRuntime::currTestCase);
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::finished,
          this, &DisTestRuntime::finished);
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::finishTestCaseStep,
          this, &DisTestRuntime::finishTestCaseStep);
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::runtimeMessage,
          this, &DisTestRuntime::runtimeMessage);
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::setuped,
          this, &DisTestRuntime::setuped);
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::started,
          this, &DisTestRuntime::started);
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::startTestCaseStep,
          this, &DisTestRuntime::startTestCaseStep);
  connect(disTestSuiteRuntime, &DisTestSuiteRuntime::stopped,
          this, &DisTestRuntime::stopped);

  this->_d->_disTestSuiteRuntimes.append(disTestSuiteRuntime);

  return true;
}

bool DisTestRuntime::testRuntimeResult()
{
  if(!this->_d->_disTestSuiteRuntimes.count())
    return true;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    qWarning()<<"currently only one distestgroup "
                "is supported for execution!";
    return false;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->testSuiteResult();
}

quint16 DisTestRuntime::testCaseCount()
{
  if(!this->_d->_disTestSuiteRuntimes.count())
    return 0;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    qWarning()<<"currently only one distestgroup "
                "is supported for execution!";
    return 0;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->testCaseCount();
}

QVector<DisTestCase*> DisTestRuntime::executedTestCases() const
{
  if(!this->_d->_disTestSuiteRuntimes.count())
    return QVector<DisTestCase*>();

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    qWarning()<<"currently only one distestgroup "
                "is supported for execution!";
    return QVector<DisTestCase*>();
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->executedTestCases();
}

quint16 DisTestRuntime::executedTestCaseCount()
{
  if(!this->_d->_disTestSuiteRuntimes.count())
    return 0;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    qWarning()<<"currently only one distestgroup "
                "is supported for execution!";
    return 0;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->executedTestCaseCount();
}

quint16 DisTestRuntime::verdictTypeCount(DisTestResult::Verdict verdict)
{
  if(!this->_d->_disTestSuiteRuntimes.count())
    return 0;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    qWarning()<<"currently only one distestgroup "
                "is supported for execution!";
    return 0;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->verdictTypeCount(verdict);
}

QVector<DisTestCase*> DisTestRuntime::failedTestCases()
{
  if(!this->_d->_disTestSuiteRuntimes.count())
    return QVector<DisTestCase*>();

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    qWarning()<<"currently only one distestgroup "
                "is supported for execution!";
    return QVector<DisTestCase*>();
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->failedTestCases();
}

const QDateTime& DisTestRuntime::startTime() const
{
  if(!this->_d->_disTestSuiteRuntimes.count())
    return this->_d->_startTime;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    qWarning()<<"currently only one distestgroup "
                "is supported for execution!";
    return this->_d->_startTime;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->startTime();
}

const QDateTime& DisTestRuntime::endTime() const
{
  if(!this->_d->_disTestSuiteRuntimes.count())
    return this->_d->_endTime;

  if(this->_d->_disTestSuiteRuntimes.count()!=1)
  {
    qWarning()<<"currently only one distestgroup "
                "is supported for execution!";
    return this->_d->_endTime;
  }

  return this->_d->_disTestSuiteRuntimes.at(0)->endTime();
}

const QVector<DisTestSuiteRuntime*>& DisTestRuntime::disTestSuiteRuntimes()
{
  return this->_d->_disTestSuiteRuntimes;
}

} // namespace distestruntime
} // namespace distestproject
