#include "distestprojectwizard.hpp"

#include <utils/filewizarddialog.h>
#include <utils/qtcassert.h>

#include <projectexplorer/customwizard/customwizard.h>

#include <QXmlStreamWriter>

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

DisTestProjectWizardPage::DisTestProjectWizardPage(const QString& title,
                                                   QWidget *parent) :
  QWizardPage(parent),
  _complete(true)
{
  this->setTitle(title);
}

void DisTestProjectWizardPage::slotChanged()
{
  ///example code
  const bool completeNow=true;
  if (completeNow != this->_complete)
  {
    _complete = completeNow;
    emit completeChanged();
  }

  return;
}


DisTestProjectWizardDialog::DisTestProjectWizardDialog(const QString& title,
                                                       QWidget *parent) :
  Utils::FileWizardDialog(parent),
  _contentPage(new DisTestProjectWizardPage(title))
{}


DisTestProjectWizard::DisTestProjectWizard(const QString& title,
                                           const QString& projectFileExtension,
                                           const Core::BaseFileWizardParameters &parameters,
                                           QObject *parent)
  : Core::BaseFileWizard(parameters, parent),
    _title(title),
    _projectFileExtension(projectFileExtension)
{}

QWizard* DisTestProjectWizard::createWizardDialog(QWidget *parent,
                                                  const Core::WizardDialogParameters& wizardDialogParameters) const
{
  DisTestProjectWizardDialog *dialog = new DisTestProjectWizardDialog(this->_title, parent);
  dialog->setPath(QDir::homePath());
  foreach (QWizardPage *p, wizardDialogParameters.extensionPages())
    dialog->addPage(p);

  return dialog;
}

Core::GeneratedFiles
DisTestProjectWizard::generateFiles(QWizard const* wizard,
                                    QString* errorString) const
{
  Core::GeneratedFiles files;
  const DisTestProjectWizardDialog *dialog = qobject_cast<const DisTestProjectWizardDialog*>(wizard);
  QTC_ASSERT(dialog, return files);
  QTC_ASSERT(errorString, return files);

  QString projectPath=dialog->path()+
                      QLatin1String("/")+
                      dialog->fileName();

  ////distest project example file///////////
  const QString projectFileName = Core::BaseFileWizard::buildFileName(projectPath,
                                                                      dialog->fileName(),
                                                                      this->_projectFileExtension);
  Core::GeneratedFile projectFile(projectFileName);
  projectFile.setAttributes(Core::GeneratedFile::OpenProjectAttribute);
  QString exampleProjectFileContent=this->generateExampleProjectFileContent(projectFileName,
                                                                            errorString);
  projectFile.setContents(exampleProjectFileContent);
  files.push_back(projectFile);

  ////decl example file///////////
  const QString declFileName = Core::BaseFileWizard::buildFileName(projectPath,
                                                                   dialog->fileName(),
                                                                   QLatin1String("decl"));
  Core::GeneratedFile declFile(declFileName);
  QFile exampleDeclFile(QLatin1String(":/distestproject/project_default.decl"));
  if(exampleDeclFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QString content(QLatin1String(exampleDeclFile.readAll()));
    content.replace(QStringLiteral("$${ProjectName}"), dialog->fileName());
    declFile.setContents(content);
  }
  else
    *errorString+=QLatin1String("example decl file could not be written!");
  files.push_back(declFile);

  ////sut example file///////////
  const QString sutFileName = Core::BaseFileWizard::buildFileName(projectPath,
                                                                  dialog->fileName(),
                                                                  QLatin1String("sut"));
  Core::GeneratedFile sutFile(sutFileName);
  QFile exampleSutFile(QStringLiteral(":/distestproject/project_default.sut"));
  if(exampleSutFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QString content(QLatin1String(exampleSutFile.readAll()));
    content.replace(QStringLiteral("$${ProjectName}"), dialog->fileName());
    sutFile.setContents(content);
  }
  else
    *errorString+=QLatin1String("example sut file could not be written!");
  files.push_back(sutFile);

  ///test system...///
  const QString testSystemFileName = Core::BaseFileWizard::buildFileName(projectPath,
                                                                         dialog->fileName(),
                                                                         QLatin1String("testsystem"));
  Core::GeneratedFile testSystemFile(testSystemFileName);
  QFile exampleTestSystemFile(QLatin1String(":/distestproject/project_default.testsystem"));
  if(exampleTestSystemFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QString content(QLatin1String(exampleTestSystemFile.readAll()));
    content.replace(QStringLiteral("$${ProjectName}"), dialog->fileName());
    testSystemFile.setContents(content);
  }
  else
    *errorString+=QStringLiteral("example test system file for test suite could not be written!");
  files.push_back(testSystemFile);

  ///test cases
  const QString testCase_1FileName = Core::BaseFileWizard::buildFileName(projectPath,
                                                                         QStringLiteral("testcase_1"),
                                                                         QStringLiteral("testcase"));
  Core::GeneratedFile testCase_1File(testCase_1FileName);
  QFile exampleTestCase_1File(QStringLiteral(":/distestproject/project_default_testcase_1.testcase"));
  if(exampleTestCase_1File.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QString content(QLatin1String(exampleTestCase_1File.readAll()));
    content.replace(QStringLiteral("$${ProjectName}"), dialog->fileName());
    testCase_1File.setContents(content);
  }
  else
    *errorString+=QStringLiteral("example test case 1 file could not be written!");
  files.push_back(testCase_1File);

  const QString testCase_2FileName = Core::BaseFileWizard::buildFileName(projectPath,
                                                                         QStringLiteral("testcase_2"),
                                                                         QStringLiteral("testcase"));
  Core::GeneratedFile testCase_2File(testCase_2FileName);
  QFile exampleTestCase_2File(QStringLiteral(":/distestproject/project_default_testcase_2.testcase"));
  if(exampleTestCase_2File.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QString content(QLatin1String(exampleTestCase_2File.readAll()));
    content.replace(QStringLiteral("$${ProjectName}"), dialog->fileName());
    testCase_2File.setContents(content);
  }
  else
    *errorString+=QStringLiteral("example test case 2 file could not be written!");
  files.push_back(testCase_2File);

  return files;
}

QString DisTestProjectWizard::generateExampleProjectFileContent(const QString& projectFileName,
                                                                QString* errorMessage) const
{
  QTC_ASSERT(errorMessage, return QStringLiteral(""));

  if(projectFileName.isEmpty())
  {
    *errorMessage=QLatin1String("empty project file name!");
    return  QStringLiteral("");
  }

  QFileInfo exampleProjectFileInfo(projectFileName);

  QString exampleProjectFileContent=QStringLiteral("[DeclFiles]\n");
  exampleProjectFileContent+=QStringLiteral("size=1\n");
  exampleProjectFileContent+=QStringLiteral("1/file=")
                             +exampleProjectFileInfo.baseName()
                             +QStringLiteral(".decl\n");
  exampleProjectFileContent+=QStringLiteral("\n");

  exampleProjectFileContent+=QStringLiteral("[SutFiles]\n");
  exampleProjectFileContent+=QStringLiteral("size=1\n");
  exampleProjectFileContent+=QStringLiteral("1/file=")
                             +exampleProjectFileInfo.baseName()
                             +QStringLiteral(".sut\n");
  exampleProjectFileContent+=QStringLiteral("\n");

  exampleProjectFileContent+=QStringLiteral("[TestSystemFiles]\n");
  exampleProjectFileContent+=QStringLiteral("size=1\n");
  exampleProjectFileContent+=QStringLiteral("1/file=")
                             +exampleProjectFileInfo.baseName()
                             +QStringLiteral(".testsystem\n");
  exampleProjectFileContent+=QStringLiteral("\n");

  exampleProjectFileContent+=QStringLiteral("[TestCaseFiles]\n");
  exampleProjectFileContent+=QStringLiteral("size=2\n");
  exampleProjectFileContent+=QStringLiteral("1/file=")
                             +QStringLiteral("testcase_1.testcase\n");
  exampleProjectFileContent+=QStringLiteral("2/file=")
                             +QStringLiteral("testcase_2.testcase\n");

  return exampleProjectFileContent;
}

bool DisTestProjectWizard::postGenerateFiles(const QWizard* wizard,
                                             const Core::GeneratedFiles& files,
                                             QString* errorMessage)
{
  Q_UNUSED(wizard);

  return ProjectExplorer::CustomProjectWizard::postGenerateOpen(files,
                                                                errorMessage);
}

} // namespace distestproject
