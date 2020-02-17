#include "distestbuildstep.hpp"

#include "distestbuildconfiguration.hpp"
#include "distestproject.hpp"

#include <coreplugin/messagemanager.h>

#include <projectexplorer/buildsteplist.h>
#include <projectexplorer/target.h>

#include <QDir>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

DisTestBuildStep::DisTestBuildStep(ProjectExplorer::BuildStepList* parentStepList,
                                   const Core::Id& buildID)
  : ProjectExplorer::BuildStep(parentStepList, buildID)
{}

DisTestBuildStep::DisTestBuildStep(ProjectExplorer::BuildStepList* parentStepList,
                                   ProjectExplorer::BuildStep* step)
  : ProjectExplorer::BuildStep(parentStepList, step)
{}

DisTestBuildStep::~DisTestBuildStep()
{}

DisTestProject*DisTestBuildStep::disTestProject()
{
  DisTestProject* disTestProject = qobject_cast<DisTestProject*>(this->project());
  Q_ASSERT(disTestProject);

  return disTestProject;
}

DisTestBuildConfiguration* DisTestBuildStep::disTestBuildConfiguration()
{
  DisTestBuildConfiguration* disTestBC = qobject_cast<DisTestBuildConfiguration*>(this->buildConfiguration());
  Q_ASSERT(disTestBC);

  return disTestBC;
}

bool DisTestBuildStep::init()
{
  return true;
}


//bool DisTestBuildStep::buildDisTestRuntime(QString* errorMessage)
//{
//  Q_ASSERT(this->_d->_disTestProject);
//  Q_ASSERT(this->_d->_buildDir.exists());
//  Q_ASSERT(errorMessage);

//  SmartTestRuntime* smartTestRuntime = new SmartTestRuntime(this->_d->_smartTestProject->testModel());
//  ComBuildSmartTestRuntime command(this->_d->_smartTestProject,
//                                   smartTestRuntime,
//                                   this->_d->_buildDir);
//  bool result = command.execute(errorMessage);
//  if(!result)
//  {
//    delete smartTestRuntime;
//    return false;
//  }

//  this->smartTestBuildConfiguration()->setDisTestRuntime(smartTestRuntime);

//  return true;
//}

ProjectExplorer::BuildStepConfigWidget* DisTestBuildStep::createConfigWidget()
{
  return new ProjectExplorer::SimpleBuildStepConfigWidget(this);
}

bool DisTestBuildStep::runInGuiThread() const
{
  return true;
}

//
// DisTestBuildStepFactory
//

class DisTestBuildStepFactory::Private
{
  friend class DisTestBuildStepFactory;

  Private(const Core::Id& projectID,
          const Core::Id& buildID)
    : _projectID(projectID),
      _buildID(buildID)
  {}

  const Core::Id  _projectID;
  const Core::Id  _buildID;
};

DisTestBuildStepFactory::DisTestBuildStepFactory(const Core::Id& projectID,
                                                 const Core::Id& buildID,
                                                 QObject* parent)
  : ProjectExplorer::IBuildStepFactory(parent),
    _d(new Private(projectID, buildID))
{}

DisTestBuildStepFactory::~DisTestBuildStepFactory()
{
  delete this->_d;
}

bool DisTestBuildStepFactory::canCreate(ProjectExplorer::BuildStepList* parentStepList,
                                        const Core::Id id) const
{
  if (parentStepList->target()->project()->id() == this->_d->_projectID)
    return id == this->_d->_buildID;

  return false;
}

bool DisTestBuildStepFactory::canClone(ProjectExplorer::BuildStepList* parentStepList,
                                       ProjectExplorer::BuildStep *source) const
{
  Q_UNUSED(parentStepList);
  Q_UNUSED(source);

  return false;
}

ProjectExplorer::BuildStep* DisTestBuildStepFactory::clone(ProjectExplorer::BuildStepList* parentStepList,
                                                           ProjectExplorer::BuildStep* source)
{
  Q_UNUSED(parentStepList);
  Q_UNUSED(source);

  return 0;
}

bool DisTestBuildStepFactory::canRestore(ProjectExplorer::BuildStepList *parentStepList,
                                         const QVariantMap &map) const
{
  return canCreate(parentStepList,
                   ProjectExplorer::idFromMap(map));
}

QList<Core::Id>
DisTestBuildStepFactory::availableCreationIds(ProjectExplorer::BuildStepList* bsl) const
{
  if (bsl->target()->project()->id() == this->_d->_projectID)
    return QList<Core::Id>() << Core::Id(this->_d->_buildID);

  return QList<Core::Id>();
}

QString DisTestBuildStepFactory::displayNameForId(const Core::Id id) const
{
  if (id == this->_d->_buildID)
    return id.toString();

  return QString();
}

const Core::Id& DisTestBuildStepFactory::projectID() const
{
  return this->_d->_projectID;
}

const Core::Id& DisTestBuildStepFactory::buildID() const
{
  return this->_d->_buildID;
}

} // namespace distestproject

