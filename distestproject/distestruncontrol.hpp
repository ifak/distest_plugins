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
#ifndef DISTESTPROJECT_DISTESTRUNCONTROL_HPP
#define DISTESTPROJECT_DISTESTRUNCONTROL_HPP

#include "distestproject_global.hpp"

#include <projectexplorer/runconfiguration.h>

#include <QUuid>
#include <QIcon>

namespace distestproject {

class DisTestRunConfiguration;

namespace distestruntime {
class DisTestRuntime;
class DisTestCase;
class DisTestComponent;
}

class DISTESTPROJECTSHARED_EXPORT DisTestRunControl
    : public ProjectExplorer::RunControl
{
  Q_OBJECT
public:
  DisTestRunControl(DisTestRunConfiguration* disTestRunConfiguration,
                    ProjectExplorer::RunMode mode,
                    const QIcon& runControlIcon = QIcon(QLatin1String(ProjectExplorer::Constants::ICON_RUN_SMALL)));
  virtual ~DisTestRunControl();

public:
  virtual void        start();
  virtual StopResult  stop();

public:
  bool  isRunning() const;
  QIcon icon() const;

protected slots:
  void currTestCaseSlot(distestruntime::DisTestCase* currTestCase);
  void startTestCaseStepSlot(QUuid stepId, QString message);
  void finishTestCaseStepSlot(QUuid stepId, bool result, QString message);
  void runtimeMessageSlot(bool success, QString message);
  void componentRuntimeMessageSlot(distestruntime::DisTestComponent* disTestComponent,
                                   bool success,
                                   QString message);
  void finishedSlot(bool result, QString message);

private:
  Q_DISABLE_COPY(DisTestRunControl)
  class Private;
  Private* _d;
};

class DISTESTPROJECTSHARED_EXPORT DisTestRunControlFactory
    : public ProjectExplorer::IRunControlFactory
{
  Q_OBJECT
public:
  DisTestRunControlFactory(const Core::Id& runId,
                           QObject *parent = 0);
  virtual ~DisTestRunControlFactory();

public:
  bool                canRun(ProjectExplorer::RunConfiguration* runConfiguration,
                             ProjectExplorer::RunMode mode) const;
  DisTestRunControl*  create(ProjectExplorer::RunConfiguration*runConfiguration,
                             ProjectExplorer::RunMode mode,
                             QString *errorMessage);

protected:
  virtual DisTestRunControl* createRunControl(DisTestRunConfiguration* disTestRunConfiguration,
                                              ProjectExplorer::RunMode mode,
                                              QString* errorMessage) =0;
private:
  Q_DISABLE_COPY(DisTestRunControlFactory)
  class Private;
  Private* _d;
};

} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTRUNCONTROL_HPP
