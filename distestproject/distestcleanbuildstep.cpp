#include "distestcleanbuildstep.hpp"

#include "distestprojectconstants.hpp"
#include "distestbuildconfiguration.hpp"
#include "distestrunconfiguration.hpp"
#include "distestproject.hpp"

#include <mobata/utils/fileutils.hpp>

#include <projectexplorer/target.h>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

class DisTestCleanBuildStep::Private
{
  friend class DisTestCleanBuildStep;

  Private()
  {}

  QDir  _buildDir;
};

DisTestCleanBuildStep::DisTestCleanBuildStep(ProjectExplorer::BuildStepList* parentStepList)
  : DisTestBuildStep(parentStepList, Core::Id(Constants::ACTION_BUILD_CLEAN)),
    _d(new Private())
{}

DisTestCleanBuildStep::DisTestCleanBuildStep(ProjectExplorer::BuildStepList* parentStepList,
                                             const Core::Id& stepID)
  : DisTestBuildStep(parentStepList, stepID),
    _d(new Private())
{}

DisTestCleanBuildStep::~DisTestCleanBuildStep()
{
  delete this->_d;
}

bool DisTestCleanBuildStep::init()
{
  DisTestProject* disTestProject=this->disTestProject();
  Q_ASSERT(disTestProject);

  DisTestRunConfiguration* rc = qobject_cast<DisTestRunConfiguration*>(disTestProject
                                                                       ->activeTarget()
                                                                       ->activeRunConfiguration());
  Q_ASSERT(rc);

  DisTestBuildConfiguration* bc = this->disTestBuildConfiguration();
  QString outputPath(bc->buildDirectory());
  this->_d->_buildDir.setPath(outputPath);
  if(!this->_d->_buildDir.exists())
    this->_d->_buildDir.mkpath(outputPath);

  if(!this->_d->_buildDir.exists())
  {
    QString errorMessage=tr("The output folder '%1' cannot be created. "
                            "The build process cannot be initialized!").arg(outputPath);
    emit addOutput(errorMessage, BuildStep::ErrorMessageOutput);
    return false;
  }

  return true;
}

void DisTestCleanBuildStep::run(QFutureInterface<bool> &fi)
{
  Q_ASSERT(this->_d->_buildDir.exists());

  bool result=utils::FileUtils::removeDirContent(this->_d->_buildDir);
  if(!result)
  {
    QString errorMessage = tr("The build directory '%1' cannot be cleaned!")
                           .arg(this->_d->_buildDir.absolutePath());
    emit addOutput(errorMessage, BuildStep::ErrorMessageOutput);
    fi.reportResult(false);
    emit finished();
    return;
  }

  fi.reportResult(true);
  emit finished();

  return;
}

//
// DisTestCleanBuildStepFactory
//

DisTestCleanBuildStepFactory::DisTestCleanBuildStepFactory(const Core::Id& projectID,
                                                           const Core::Id& buildID,
                                                           QObject* parent)
  : DisTestBuildStepFactory(projectID, buildID, parent)
{}

DisTestCleanBuildStepFactory::~DisTestCleanBuildStepFactory()
{}

ProjectExplorer::BuildStep* DisTestCleanBuildStepFactory::create(ProjectExplorer::BuildStepList* parentStepList,
                                                                 const Core::Id id)
{
  if (!this->canCreate(parentStepList, id))
    return 0;

  DisTestCleanBuildStep* step = new DisTestCleanBuildStep(parentStepList);

  return step;
}

ProjectExplorer::BuildStep* DisTestCleanBuildStepFactory::restore(ProjectExplorer::BuildStepList* parentStepList,
                                                                  const QVariantMap &map)
{
  if (!this->canRestore(parentStepList, map))
    return 0;

  DisTestCleanBuildStep* cbc(new DisTestCleanBuildStep(parentStepList));
  if (cbc->fromMap(map))
    return cbc;

  delete cbc;

  return 0;
}

} // namespace distestproject

