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

#include "distestproject_global.hpp"

#include <projectexplorer/buildstep.h>

namespace distestproject {

class DisTestProject;
class DisTestBuildConfiguration;

class DISTESTPROJECTSHARED_EXPORT DisTestBuildStep
    : public ProjectExplorer::BuildStep
{
  Q_OBJECT

  friend class DisTestBuildStepFactory;

public:
  DisTestBuildStep(ProjectExplorer::BuildStepList* parentStepList,
                   const Core::Id& buildID);
  virtual ~DisTestBuildStep();

public:
  virtual bool init();
  virtual void run(QFutureInterface<bool> &fi) =0;

public:
  virtual ProjectExplorer::BuildStepConfigWidget* createConfigWidget();
  virtual bool runInGuiThread() const;

protected:
  DisTestBuildStep(ProjectExplorer::BuildStepList* parentStepList,
                   ProjectExplorer::BuildStep* step);

protected:
  DisTestProject*             disTestProject();
  DisTestBuildConfiguration*  disTestBuildConfiguration();
};

class DISTESTPROJECTSHARED_EXPORT DisTestBuildStepFactory
    : public ProjectExplorer::IBuildStepFactory
{
  Q_OBJECT

public:
  explicit DisTestBuildStepFactory(const Core::Id& projectID,
                                   const Core::Id& buildID,
                                   QObject *parent = 0);
  virtual ~DisTestBuildStepFactory();

public:
  bool                        canCreate(ProjectExplorer::BuildStepList *parentStepList,
                                        const Core::Id id) const;
  bool                        canClone(ProjectExplorer::BuildStepList *parentStepList,
                                       ProjectExplorer::BuildStep *source) const;
  ProjectExplorer::BuildStep* clone(ProjectExplorer::BuildStepList* parentStepList,
                                    ProjectExplorer::BuildStep* source);

  bool                        canRestore(ProjectExplorer::BuildStepList* parentStepList,
                                         const QVariantMap& map) const;

  QList<Core::Id>             availableCreationIds(ProjectExplorer::BuildStepList* bsl) const;
  QString                     displayNameForId(const Core::Id id) const;

public:
  virtual ProjectExplorer::BuildStep* create(ProjectExplorer::BuildStepList* parentStepList,
                                             const Core::Id id) =0;
  virtual ProjectExplorer::BuildStep* restore(ProjectExplorer::BuildStepList *parentStepList,
                                              const QVariantMap &map) =0;

protected:
  const Core::Id& projectID() const;
  const Core::Id& buildID() const;

private:
  class Private;
  Private* _d;
};

} // namespace distestproject
