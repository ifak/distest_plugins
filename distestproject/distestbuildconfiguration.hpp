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
#ifndef DISTESTPROJECT_DISTESTBUILDCONFIGURATION_HPP
#define DISTESTPROJECT_DISTESTBUILDCONFIGURATION_HPP

#include "distestproject_global.hpp"

#include <projectexplorer/basebuildconfiguration.hpp>
#include <projectexplorer/namedwidget.h>

namespace distestproject {

namespace distestruntime {
class DisTestRuntime;
}

class DISTESTPROJECTSHARED_EXPORT DisTestBuildConfiguration
    : public ProjectExplorer::BaseBuildConfiguration
{
  Q_OBJECT

public:
  explicit DisTestBuildConfiguration(ProjectExplorer::Target* parent,
                                     const Core::Id& id,
                                     const QString& displayName);
  virtual ~DisTestBuildConfiguration();

public:
  virtual QString buildDirectory() const;
  virtual ProjectExplorer::NamedWidget* createConfigWidget();
  virtual BuildType buildType() const;
  virtual bool isEnabled() const;
  virtual QString disabledReason() const;

public:
  void                            setDisTestRuntime(distestruntime::DisTestRuntime* disTestRuntime);
  distestruntime::DisTestRuntime* disTestRuntime();
  void                            setEnabled(const bool enabled);

private:
  Q_DISABLE_COPY(DisTestBuildConfiguration)
  class Private;
  Private* _d;
};

class DISTESTPROJECTSHARED_EXPORT DisTestBuildConfigurationFactory
    : public ProjectExplorer::IBuildConfigurationFactory
{
  Q_OBJECT

public:
  explicit DisTestBuildConfigurationFactory(const Core::Id& projectId,
                                            const Core::Id& buildId,
                                            QObject *parent = 0);
  virtual ~DisTestBuildConfigurationFactory();

public:
  virtual bool canCreate(const ProjectExplorer::Target* parent,
                         const Core::Id id) const;
  virtual DisTestBuildConfiguration* create(ProjectExplorer::Target* parent,
                                            const Core::Id id,
                                            const QString &name = QString()) = 0;

  // used to recreate the runConfigurations when restoring settings
  virtual bool canRestore(const ProjectExplorer::Target* parent,
                          const QVariantMap &map) const;
  virtual DisTestBuildConfiguration* restore(ProjectExplorer::Target* parent,
                                             const QVariantMap &map) = 0;

public:
  // used to show the list of possible additons to a target, returns a list of types
  virtual QList<Core::Id> availableCreationIds(const ProjectExplorer::Target *parent) const;

  // used to translate the types to names to display to the user
  virtual QString displayNameForId(const Core::Id id) const;

  virtual bool canClone(const ProjectExplorer::Target* parent,
                        ProjectExplorer::BuildConfiguration* product) const;
  virtual DisTestBuildConfiguration* clone(ProjectExplorer::Target* parent,
                                           ProjectExplorer::BuildConfiguration* product);

private:
  bool canHandle(const ProjectExplorer::Target* t) const;

private:
  Q_DISABLE_COPY(DisTestBuildConfigurationFactory)
  class Private;
  Private* _d;
};

} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTBUILDCONFIGURATION_HPP
