#include "distestcasewizard.hpp"

#include "distestproject.hpp"
#include "distestrendermanager.hpp"

#include <mobata/utils/functors.hpp>

#include <utils/qtcassert.h>
#include <projectexplorer/customwizard/customwizard.h>

#include <QFileInfo>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

namespace Internal {

DisTestCaseWizardDialog::DisTestCaseWizardDialog(QWidget *parent)
  : Utils::FileWizardDialog(parent)
{}




DisTestCaseWizard::DisTestCaseWizard(const Core::BaseFileWizardParameters &parameters,
                                     QObject *parent)
  : Core::BaseFileWizard(parameters, parent), _contextProject(0), _contextNode(0)
{}

void DisTestCaseWizard::setContextNode(ProjectExplorer::Node* node)
{
  this->_contextNode=node;

  return;
}

void DisTestCaseWizard::setContextProject(ProjectExplorer::Project *project)
{
  this->_contextProject=project;

  return;
}

QWizard *DisTestCaseWizard::createWizardDialog(QWidget *parent,
                                               const Core::WizardDialogParameters& wizardDialogParameters) const
{
  DisTestCaseWizardDialog *dialog = new DisTestCaseWizardDialog(parent);
  dialog->setPath(wizardDialogParameters.defaultPath());
  foreach (QWizardPage *p, wizardDialogParameters.extensionPages())
    dialog->addPage(p);

  return dialog;
}

Core::GeneratedFiles
DisTestCaseWizard::generateFiles(QWizard const* wizard,
                                 QString* errorString) const
{
  Core::GeneratedFiles files;
  const DisTestCaseWizardDialog* dialog = qobject_cast<const DisTestCaseWizardDialog*>(wizard);
  QTC_ASSERT(dialog, return files);
  QTC_ASSERT(errorString, return files);

  //get distest-project
  DisTestProject* disTestProject=qobject_cast<DisTestProject*>(this->_contextProject);
  // error handling............
  if(!disTestProject)
  {
    QString errorMessage=tr("No DisTest Project for new test case!");
    utils::AddPtrString(errorString)<<errorMessage;

    return files;
  }

  ////distest test case example file///////////
  const QString testCaseFileName = Core::BaseFileWizard::buildFileName(dialog->path(),
                                                                       dialog->fileName(),
                                                                       QLatin1String("testcase"));

  QFileInfo testCaseFileInfo(testCaseFileName);
  if(testCaseFileInfo.exists())
  {
    *errorString+=tr("there is already a test case file '%1' available, "
                     "please choose another test case file name!").arg(testCaseFileName);
    return files;
  }

  Core::GeneratedFile newTestCaseFile(testCaseFileName);
  newTestCaseFile.setAttributes(Core::GeneratedFile::OpenEditorAttribute);

  // test case content/////////
  QFile templateTestCaseFile(QStringLiteral(":/distestproject/project_default_newtestcase.testcase"));
  if(templateTestCaseFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QString content(QLatin1String(templateTestCaseFile.readAll()));
    content.replace(QStringLiteral("$${ProjectName}"), disTestProject->displayName());
    content.replace(QStringLiteral("$${NewTestCaseName}"),
                    QString(QLatin1String("testcase_%1")).arg(disTestProject->testCaseCount()+1));
    newTestCaseFile.setContents(content);
  }
  else
    *errorString+=QLatin1String("example new test case file could not be written!");
  files.push_back(newTestCaseFile);

  return files;
}

bool DisTestCaseWizard::postGenerateFiles(const QWizard* wizard,
                                          const Core::GeneratedFiles& files,
                                          QString* errorMessage)
{
  qDebug()<<"DisTestTestCaseWizard::postGenerateFiles() executed()";
  Q_UNUSED(wizard);

  //get distest-project
  DisTestProject* disTestProject=qobject_cast<DisTestProject*>(this->_contextProject);
  // error handling............
  if(!disTestProject)
  {
    QString errorString=tr("No DisTest Project for new test case!");
    if(errorMessage)
      *errorMessage+=errorString;
    else
      qCritical()<<"error: "<<errorString;

    return false;
  }

  QString projectID(disTestProject->document()->fileName());
  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  for(const Core::GeneratedFile& testCaseFile : files)
  {
    if(!disTestProject->addTestCaseFile(testCaseFile.path(), errorMessage))
      return false;
    else
      renderManager->assignTestCaseDocument(projectID, testCaseFile.path());
  }

  return ProjectExplorer::CustomProjectWizard::postGenerateOpen(files,
                                                                errorMessage);
}


} // namespace Internal
} // namespace distestproject

