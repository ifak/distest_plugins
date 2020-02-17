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
#ifndef DISTESTPROJECT_DISTESTCLEANBUILDSTEP_HPP
#define DISTESTPROJECT_DISTESTCLEANBUILDSTEP_HPP

#include "distestbuildstep.hpp"

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT DisTestCleanBuildStep
    : public DisTestBuildStep
{
  Q_OBJECT

public:
  DisTestCleanBuildStep(ProjectExplorer::BuildStepList* parentStepList);
  virtual ~DisTestCleanBuildStep();

public:
  virtual bool init();
  virtual void run(QFutureInterface<bool> &fi);

protected:
  DisTestCleanBuildStep(ProjectExplorer::BuildStepList* parentStepList,
                        const Core::Id& stepID);

private:
  class Private;
  Private* _d;
};

class DISTESTPROJECTSHARED_EXPORT DisTestCleanBuildStepFactory
    : public DisTestBuildStepFactory
{
  Q_OBJECT

protected:
  explicit DisTestCleanBuildStepFactory(const Core::Id& projectID,
                                        const Core::Id& buildID,
                                        QObject *parent = 0);

public:
  virtual ~DisTestCleanBuildStepFactory();

public:
  virtual ProjectExplorer::BuildStep* create(ProjectExplorer::BuildStepList* parentStepList,
                                             const Core::Id id);
  virtual ProjectExplorer::BuildStep* restore(ProjectExplorer::BuildStepList *parentStepList,
                                              const QVariantMap &map);
};

} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTCLEANBUILDSTEP_HPP
