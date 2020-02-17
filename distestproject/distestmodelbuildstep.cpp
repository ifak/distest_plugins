#include "distestmodelbuildstep.hpp"

#include "distestprojectconstants.hpp"
#include "distestproject.hpp"

#include <projectexplorer/task.h>
#include <projectexplorer/projectexplorerconstants.h>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

DisTestModelBuildStep::DisTestModelBuildStep(ProjectExplorer::BuildStepList* parentStepList,
                                             const Core::Id& stepID)
  : DisTestBuildStep(parentStepList, stepID)
{}

DisTestModelBuildStep::~DisTestModelBuildStep()
{}

bool DisTestModelBuildStep::init()
{
  return DisTestBuildStep::init();
}

void DisTestModelBuildStep::run(QFutureInterface<bool> &fi)
{
  DisTestProject* disTestProject = this->disTestProject();
  Q_ASSERT(disTestProject);

  QString errorMessage;
  bool result=disTestProject->reload(&errorMessage);
  if(!result)
  {
    emit addOutput(errorMessage, BuildStep::ErrorMessageOutput);

    if(disTestProject->isError())
    {
      foreach(const ProjectExplorer::BaseError& error,
              disTestProject->errors())
      {
        emit addTask(ProjectExplorer::Task(ProjectExplorer::Task::Error,
                                           error.description(),
                                           Utils::FileName::fromString(error.url().path()),
                                           error.line(),
                                           Core::Id(ProjectExplorer::Constants::TASK_CATEGORY_COMPILE)));
      }
    }

    fi.reportResult(false);
    emit finished();
    return;
  }

  result=disTestProject->rebuildTestModel(&errorMessage);
  if(!result)
  {
    emit addOutput(errorMessage, BuildStep::ErrorMessageOutput);

    for(const ProjectExplorer::BaseError& error : disTestProject->errors())
    {
      emit addTask(ProjectExplorer::Task(ProjectExplorer::Task::Error,
                                         error.description(),
                                         Utils::FileName::fromString(error.url().path()),
                                         error.line(),
                                         Core::Id(ProjectExplorer::Constants::TASK_CATEGORY_COMPILE)));
    }

    fi.reportResult(false);
    emit finished();
    return;
  }

  fi.reportResult(true);
  emit finished();

  return;
}

//
// DisTestModelBuildStepFactory
//

DisTestModelBuildStepFactory::DisTestModelBuildStepFactory(const Core::Id& projectID,
                                                           const Core::Id& buildID,
                                                           QObject* parent)
  : DisTestBuildStepFactory(projectID, buildID, parent)
{}

DisTestModelBuildStepFactory::~DisTestModelBuildStepFactory()
{}

} // namespace distestproject

