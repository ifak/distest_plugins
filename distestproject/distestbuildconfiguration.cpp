#include "distestbuildconfiguration.hpp"

#include "distestruntime/distestruntime.hpp"

#include "distestproject.hpp"

#include <projectexplorer/target.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/buildsteplist.h>

#include <utils/qtcassert.h>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

typedef distestruntime::DisTestRuntime  DisTestRuntime;

class DisTestBuildConfiguration::Private
{
  friend class DisTestBuildConfiguration;

  QString         _buildDirectory;
  DisTestRuntime* _disTestRuntime;
  DisTestProject* _disTestProject;
  bool            _enabled;
  QString         _disabledReason;

  Private()
    : _disTestRuntime(0),
      _enabled(true),
      _disabledReason(QStringLiteral("test runtime is running"))
  {}
};

DisTestBuildConfiguration::DisTestBuildConfiguration(ProjectExplorer::Target* parent,
                                                     const Core::Id& id,
                                                     const QString& displayName)
  : ProjectExplorer::BaseBuildConfiguration(parent, id, "DISTEST_Build"),
    _d(new Private)
{
  this->setDisplayName(displayName);
  this->_d->_disTestProject = qobject_cast<DisTestProject*>(parent->project());
  Q_ASSERT(this->_d->_disTestProject);
  this->_d->_buildDirectory = this->_d->_disTestProject->shadowBuildDirectory(parent->kit(),
                                                                              this->displayName());
  qDebug()<<"DisTestConfiguration::_buildDirectory: "<<this->_d->_buildDirectory;
}

DisTestBuildConfiguration::~DisTestBuildConfiguration()
{
  delete this->_d->_disTestRuntime;
  delete this->_d;
}

void DisTestBuildConfiguration::setDisTestRuntime(DisTestRuntime* disTestRuntime)
{
  delete this->_d->_disTestRuntime;
  this->_d->_disTestRuntime = disTestRuntime;

  return;
}

DisTestRuntime* DisTestBuildConfiguration::disTestRuntime()
{
  return this->_d->_disTestRuntime;
}

void DisTestBuildConfiguration::setEnabled(const bool enabled)
{
  if(this->_d->_enabled == enabled)
    return;

  this->_d->_enabled = enabled;
  emit this->_d->_disTestProject->buildConfigurationEnabledChanged();

  return;
}

QString DisTestBuildConfiguration::buildDirectory() const
{
  return this->_d->_buildDirectory;
}

ProjectExplorer::NamedWidget* DisTestBuildConfiguration::createConfigWidget()
{
  return 0;
}

DisTestBuildConfiguration::BuildType DisTestBuildConfiguration::buildType() const
{
  return Unknown;
}

bool DisTestBuildConfiguration::isEnabled() const
{
  return this->_d->_enabled;
}

QString DisTestBuildConfiguration::disabledReason() const
{
  return this->_d->_disabledReason;
}

/*!
  \class DisTestBuildConfigurationFactory
*/
class DisTestBuildConfigurationFactory::Private
{
  friend class DisTestBuildConfigurationFactory;

  const Core::Id _projectId;
  const Core::Id _buildId;

  Private(const Core::Id& projectId,
          const Core::Id& buildId)
    : _projectId(projectId),
      _buildId(buildId)
  {}
};

DisTestBuildConfigurationFactory::DisTestBuildConfigurationFactory(const Core::Id& projectId,
                                                                   const Core::Id& buildId,
                                                                   QObject *parent)
  : ProjectExplorer::IBuildConfigurationFactory(parent),
    _d(new Private(projectId, buildId))
{}

DisTestBuildConfigurationFactory::~DisTestBuildConfigurationFactory()
{
  delete this->_d;
}

bool DisTestBuildConfigurationFactory::canHandle(const ProjectExplorer::Target *t) const
{
  QTC_ASSERT(t, return false);

  if (!t->project()->supportsKit(t->kit()))
    return false;

  return t->project()->id() == this->_d->_projectId;
}

// used to show the list of possible additons to a target, returns a list of types
QList<Core::Id>
DisTestBuildConfigurationFactory::availableCreationIds(const ProjectExplorer::Target* target) const
{
  QList<Core::Id> creationIds;

  if(!target
     || !target->project())
    return creationIds;

  if (target->project()->id() == this->_d->_projectId)
    return creationIds << this->_d->_buildId;

  return creationIds;
}

// used to translate the types to names to display to the user
QString DisTestBuildConfigurationFactory::displayNameForId(const Core::Id id) const
{
  return id.toString();
}

bool DisTestBuildConfigurationFactory::canCreate(const ProjectExplorer::Target* target,
                                                 const Core::Id id) const
{
  if (!this->canHandle(target))
    return false;

  return id == this->_d->_buildId;
}

// used to recreate the runConfigurations when restoring settings
bool DisTestBuildConfigurationFactory::canRestore(const ProjectExplorer::Target* target,
                                                  const QVariantMap &map) const
{
  if (!this->canHandle(target))
    return false;

  return ProjectExplorer::idFromMap(map) == this->_d->_buildId;
}

bool DisTestBuildConfigurationFactory::canClone(const ProjectExplorer::Target* target,
                                                ProjectExplorer::BuildConfiguration* product) const
{
  Q_UNUSED(target);
  Q_UNUSED(product);

  return false;
}

DisTestBuildConfiguration* DisTestBuildConfigurationFactory::clone(ProjectExplorer::Target* target,
                                                                   ProjectExplorer::BuildConfiguration* product)
{
  Q_UNUSED(target);
  Q_UNUSED(product);

  return 0;
}

} // namespace cosysproject


