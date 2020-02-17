#include "combuilddistestruntime.hpp"

#include "distestproject.hpp"
#include "distestprojectmodel.hpp"
#include "distestsuite.hpp"

#include "distestruntime/distestruntime.hpp"
#include "distestruntime/distestsuiteruntime.hpp"

#include <QDir>

namespace distestproject {

using namespace distestruntime;

class ComBuildDisTestRuntime::Private
{
  friend class ComBuildDisTestRuntime;

  DisTestProject* _disTestProject;
  DisTestRuntime* _disTestRuntime;
  QDir            _buildDir;
  quint16         _currLocalPortNumber;

  Private(DisTestProject* disTestProject,
          DisTestRuntime* disTestRuntime,
          const QDir& buildDir,
          quint16 startLocalPortNumber)
    : _disTestProject(disTestProject),
      _disTestRuntime(disTestRuntime),
      _buildDir(buildDir),
      _currLocalPortNumber(startLocalPortNumber)
  {
    if(!this->_buildDir.exists())
    {
      this->_buildDir=QDir::tempPath();
      QString buildDirName = this->_disTestProject->displayName();
      bool result = this->_buildDir.cd(buildDirName);
      if(!result)
      {
        result = this->_buildDir.mkdir(buildDirName);
        Q_ASSERT(result);
        result = this->_buildDir.cd(buildDirName);
        Q_ASSERT(result);
      }
    }
  }
};

ComBuildDisTestRuntime::ComBuildDisTestRuntime(DisTestProject* disTestProject,
                                               DisTestRuntime* disTestRuntime,
                                               const QDir& buildDir,
                                               quint16 startLocalPortNumber,
                                               QObject* parent)
  : QObject(parent),
    _d(new Private(disTestProject, disTestRuntime, buildDir, startLocalPortNumber))
{
  Q_ASSERT(this->_d->_disTestProject);
  Q_ASSERT(this->_d->_disTestRuntime);
}

ComBuildDisTestRuntime::~ComBuildDisTestRuntime()
{
  delete this->_d;
}

bool ComBuildDisTestRuntime::execute(QString* errorString)
{
  DisTestProjectModel const* disTestProjectModel = this->_d->_disTestProject->disTestProjectModel();
  Q_ASSERT(disTestProjectModel);

  this->_d->_disTestRuntime->reset();

  quint8 counter=1;
  for(DisTestSuite const* disTestSuite : disTestProjectModel->disTestSuites())
  {
    //create runtime directory
    QString testSuiteRuntimeDirName(QLatin1String("testsuite_")
                                    +QString::number(counter));
    QDir testSuiteRuntimeDir = this->_d->_buildDir;
    bool result = testSuiteRuntimeDir.cd(testSuiteRuntimeDirName);
    if(!result)
    {
      result = testSuiteRuntimeDir.mkdir(testSuiteRuntimeDirName);
      Q_ASSERT(result);
      result = testSuiteRuntimeDir.cd(testSuiteRuntimeDirName);
      Q_ASSERT(result);
    }

    distestruntime::DisTestSuiteRuntime* newDisTestSuiteRuntime=new distestruntime::DisTestSuiteRuntime(disTestSuite,
                                                                                                        testSuiteRuntimeDir.canonicalPath());
    result = this->_d->_disTestRuntime->addDisTestSuiteRuntime(newDisTestSuiteRuntime, errorString);
    if(!result)
    {
      delete newDisTestSuiteRuntime;
      newDisTestSuiteRuntime=nullptr;
      this->_d->_disTestRuntime->reset();
      return false;
    }

    result = this->buildTestComponents(newDisTestSuiteRuntime, errorString);
    if(!result)
    {
      this->_d->_disTestRuntime->reset();
      return result;
    }

    result = this->buildTestCases(newDisTestSuiteRuntime, errorString);
    if(!result)
    {
      this->_d->_disTestRuntime->reset();
      return result;
    }

    ++counter;
  }

  return true;
}

quint16 ComBuildDisTestRuntime::freeLocalPortNumber()
{
  return this->_d->_currLocalPortNumber++;
}

} // namespace distestproject
