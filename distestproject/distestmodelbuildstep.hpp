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

#include "distestbuildstep.hpp"

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT DisTestModelBuildStep
    : public DisTestBuildStep
{
  Q_OBJECT

protected:
  DisTestModelBuildStep(ProjectExplorer::BuildStepList* parentStepList,
                        const Core::Id& stepID);

public:
  virtual ~DisTestModelBuildStep();

public:
  virtual bool init();
  virtual void run(QFutureInterface<bool> &fi);
};

class DISTESTPROJECTSHARED_EXPORT DisTestModelBuildStepFactory
    : public DisTestBuildStepFactory
{
  Q_OBJECT

protected:
  explicit DisTestModelBuildStepFactory(const Core::Id& projectID,
                                        const Core::Id& buildID,
                                        QObject *parent = 0);

public:
  virtual ~DisTestModelBuildStepFactory();
};

} // namespace distestproject
