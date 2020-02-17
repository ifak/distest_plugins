#include "distestproject.hpp"

#include "distestprojectconstants.hpp"
#include "distestprojectmodel.hpp"
#include "combuildtestmodel.hpp"
#include "testreportbuilder.hpp"
#include "helpers.hpp"
#include "distestconfiguration.hpp"
#include "distestrendermanager.hpp"

#include <utils/qtcassert.h>

#include <coreplugin/icontext.h>
#include <coreplugin/messagemanager.h>
#include <coreplugin/documentmanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/editormanager/editormanager.h>

#include <projectexplorer/kit.h>
#include <projectexplorer/kitmanager.h>
#include <projectexplorer/target.h>
#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/session.h>
#include <projectexplorer/taskhub.h>

#include <QFileSystemWatcher>
#include <QMessageBox>

#include <mobata/memory_leak_start.hpp>

#include <QDebug>

namespace distestproject {

const char DISTEST_SETTINGS_KEY[] = "distestproject.DisTestProject.DisTestSettings";

const char* const declArrayKey       = "DeclFiles";
const char* const sutArrayKey        = "SutFiles";
const char* const testSystemArrayKey = "TestSystemFiles";
const char* const testCaseArrayKey   = "TestCaseFiles";
const char* const prioritizationArrayKey   = "PrioritizationFiles";

///////////////////////////DisTestProject/////////////////////////////////////////
class DisTestProject::Private
{
  friend class DisTestProject;

  DisTestProjectModel*              _disTestProjectModel;
  DisTestConfiguration*             _disTestConfiguration;
  ProjectExplorer::FolderNode*      _declFolder;
  ProjectExplorer::FolderNode*      _sutFolder;
  ProjectExplorer::FolderNode*      _testSystemFolder;
  ProjectExplorer::FolderNode*      _testCaseFolder;
  ProjectExplorer::FolderNode*      _prioritizationFolder;
  QList<ProjectExplorer::BaseError> _errors;

  Private()
    : _disTestProjectModel(nullptr),
      _disTestConfiguration(nullptr),
      _declFolder(nullptr),
      _sutFolder(nullptr),
      _testSystemFolder(nullptr),
      _testCaseFolder(nullptr),
      _prioritizationFolder(nullptr)
  {}
};

DisTestProject::DisTestProject(ProjectExplorer::BaseProjectManager* projectManager,
                               const QString &fileName,
                               const QString& mimeType,
                               const QString& id)
  : ProjectExplorer::BaseProject(projectManager, fileName, mimeType, id),
    _d(new Private)
{
  this->_d->_disTestProjectModel = new DisTestProjectModel(this);
  this->_d->_disTestConfiguration = new DisTestConfiguration(this);

  ///project folders//////////////////////
  using namespace ProjectExplorer;
  this->_d->_declFolder=this->addFolderNode(QLatin1String("declarations"),
                                            QIcon(QLatin1String(":/mobata/images/base/manytype.png")),
                                            true);
  Q_ASSERT(this->_d->_declFolder);
  this->addArrayFilesKey(QLatin1String(declArrayKey), this->_d->_declFolder);

  this->_d->_sutFolder=this->addFolderNode(QLatin1String("systems under test (SUT)"),
                                           QIcon(QLatin1String(":/mobata/images/ts/sut.png")),
                                           true);
  Q_ASSERT(this->_d->_sutFolder);
  this->addArrayFilesKey(QLatin1String(sutArrayKey), this->_d->_sutFolder);

  this->_d->_testSystemFolder=this->addFolderNode(QLatin1String("test systems"),
                                                  QIcon(QLatin1String(":/mobata/images/ts/testsystem.png")),
                                                  true);
  Q_ASSERT(this->_d->_testSystemFolder);
  this->addArrayFilesKey(QLatin1String(testSystemArrayKey), this->_d->_testSystemFolder);

  this->_d->_testCaseFolder=this->addFolderNode(QLatin1String("test cases"),
                                           QIcon(QLatin1String(":/mobata/images/ts/testcase.png")),
                                           true);
  Q_ASSERT(this->_d->_testCaseFolder);
  this->addArrayFilesKey(QLatin1String(testCaseArrayKey), this->_d->_testCaseFolder);

  this->_d->_prioritizationFolder=this->addFolderNode(QLatin1String("prioritization"),
                                           QIcon(QLatin1String(":/mobata/images/base/manytype.png")),
                                           true);
  Q_ASSERT(this->_d->_prioritizationFolder);
  this->addArrayFilesKey(QLatin1String(prioritizationArrayKey), this->_d->_prioritizationFolder);
}

DisTestProject::~DisTestProject()
{
  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  QString projectID(this->document()->fileName());
  renderManager->removeProjectDocuments(projectID);
  renderManager->removeCustomRenderSettings(projectID);
  renderManager->deregisterRenderSettings(projectID);

  delete this->_d;
}

bool DisTestProject::needsConfiguration() const
{
  return false;
}

bool DisTestProject::supportsNoTargetPanel() const
{
  return false;
}

QStringList DisTestProject::files(FilesMode fileMode) const
{
  return BaseProject::files(fileMode);
}

bool DisTestProject::reload(QString* errorString)
{
  this->_d->_errors.clear();

  if(!ProjectExplorer::BaseProject::reload(errorString))
    return false;

  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  QString projectID(this->document()->fileName());
  renderManager->createCustomRenderSettings(projectID);
  for(const QString& sutFile : this->sutFiles())
    renderManager->assignSutDocument(projectID, sutFile);
  for(const QString& testSystemFile : this->testSystemFiles())
    renderManager->assignTestSystemDocument(projectID, testSystemFile);
  for(const QString &testCaseFile : this->testCaseFiles())
    renderManager->assignTestCaseDocument(projectID, testCaseFile);

  return true;
}

DisTestProjectModel const* DisTestProject::disTestProjectModel() const
{
  return this->_d->_disTestProjectModel;
}

bool DisTestProject::rebuildTestModel(QString* errorMessage)
{
  Q_ASSERT(errorMessage);

  if(!this->reload(errorMessage))
  {
    ProjectExplorer::BaseError error;
    error.setDescription(*errorMessage);
    error.setUrl(QUrl(this->rootProjectNode()->projectDocument()->fileName()));
    this->_d->_errors.append(error);

    return false;
  }

  ComBuildTestModel commandTestModel(this);
  if(!commandTestModel.execute(errorMessage))
    return false;

  return true;
}

const QStringList& DisTestProject::declFiles() const
{
  return this->rootProjectNode()->projectDocument()->projectArrayFiles(QLatin1String(declArrayKey));
}

const QStringList& DisTestProject::sutFiles() const
{
  return this->rootProjectNode()->projectDocument()->projectArrayFiles(QLatin1String(sutArrayKey));
}

const QStringList& DisTestProject::testSystemFiles() const
{
  return this->rootProjectNode()->projectDocument()->projectArrayFiles(QLatin1String(testSystemArrayKey));
}

const QStringList& DisTestProject::testCaseFiles() const
{
  return this->rootProjectNode()->projectDocument()->projectArrayFiles(QLatin1String(testCaseArrayKey));
}

const QString& DisTestProject::prioFile() const
{
  if(this->rootProjectNode()->projectDocument()->projectArrayFiles(QLatin1String(prioritizationArrayKey)).length()==1){
      return this->rootProjectNode()->projectDocument()->projectArrayFiles(QLatin1String(prioritizationArrayKey)).first();
  }else{
    return QString();
  }
}

int DisTestProject::testCaseCount() const
{
  return this->rootProjectNode()->projectDocument()->projectArrayFilesCount(QLatin1String(testCaseArrayKey));
}

bool DisTestProject::addTestCaseFile(const QString& testCaseFileName,
                                     QString* errorMessage)
{
  if(!QFileInfo::exists(testCaseFileName))
  {
    if(errorMessage)
      *errorMessage+=tr("test case file '%1' does not exists, "
                        "test case file will not be added!").arg(testCaseFileName);
    return false;
  }

  QString relTestCasePath=QDir::cleanPath(this->rootProjectNode()->projectDocument()->fileDir().relativeFilePath(testCaseFileName));
  qDebug()<<"relative test case path:"<<relTestCasePath;

  bool result = this->rootProjectNode()->projectDocument()->addProjectArrayFile(QLatin1String(testCaseArrayKey),
                                                                                relTestCasePath,
                                                                                errorMessage);
  if(!result)
    return false;

  if(!this->reload(errorMessage))
    return false;

  return true;
}

bool DisTestProject::addPrioFile(const QString& prioFileName,
                                     QString* errorMessage)
{
  if(!QFileInfo(prioFileName).exists())
  {
    if(errorMessage)
      *errorMessage+=tr("prio file '%1' does not exists, "
                        "prio file will not be added!").arg(prioFileName);
    return false;
  }

  if(!this->rootProjectNode()->projectDocument()->projectArrayFiles(QLatin1String(prioritizationArrayKey)).isEmpty()){
    int res = QMessageBox::question(nullptr,"Prio file","A prio file already exists in this project. Would you replace the current file with the new one?");
    if(res == 65536){
      return false;
    }
  }

  QString relTestCasePath=QDir::cleanPath(this->rootProjectNode()->projectDocument()->fileDir().relativeFilePath(prioFileName));
  qDebug()<<"relative test case path:"<<relTestCasePath;

  for(QString pfile : this->rootProjectNode()->projectDocument()->projectArrayFiles(QLatin1String(prioritizationArrayKey))){
    this->rootProjectNode()->projectDocument()->removeProjectFile(pfile);
  }
  bool result = this->rootProjectNode()->projectDocument()->addProjectArrayFile(QLatin1String(prioritizationArrayKey),
                                                                                relTestCasePath,
                                                                                errorMessage);
  if(!result)
    return false;

  if(!this->reload(errorMessage))
    return false;

  return true;
}

bool DisTestProject::isError() const
{
  return this->_d->_errors.size();
}

const QList<ProjectExplorer::BaseError>&
DisTestProject::errors() const
{
  return this->_d->_errors;
}

void DisTestProject::addError(const ProjectExplorer::BaseError& newError)
{
  this->_d->_errors.append(newError);

  return;
}

void DisTestProject::addDslError(const dslparser::DslError& newDslError,
                                 const QString& errorFileName)
{
  ProjectExplorer::BaseError error;

  if(newDslError.errorType()==dslparser::DslError::SyntaxError)
    error.setErrorType(ProjectExplorer::BaseError::SyntaxError);
  else if(newDslError.errorType()==dslparser::DslError::AmbiguityError)
    error.setErrorType(ProjectExplorer::BaseError::AmbiguityError);
  else if(newDslError.errorType()==dslparser::DslError::ContextError)
    error.setErrorType(ProjectExplorer::BaseError::ContextError);
  else if(newDslError.errorType()==dslparser::DslError::SensitivityError)
    error.setErrorType(ProjectExplorer::BaseError::SensitivityError);
  else if(newDslError.errorType()==dslparser::DslError::FileError)
    error.setErrorType(ProjectExplorer::BaseError::FileError);
  else if(newDslError.errorType()==dslparser::DslError::UnknownError)
    error.setErrorType(ProjectExplorer::BaseError::UnknownError);

  error.setDescription(newDslError.message());
  error.setUrl(QUrl(errorFileName));
  error.setLine(newDslError.line());
  error.setColumn(newDslError.charPositionInLine());

  this->_d->_errors.append(error);

  return;
}

bool DisTestProject::fromMap(const QVariantMap& map)
{
  if (map.contains(QLatin1String(DISTEST_SETTINGS_KEY))) {
    QVariantMap value(map.value(QLatin1String(DISTEST_SETTINGS_KEY)).toMap());
    this->_d->_disTestConfiguration->fromMap(value);
  }

  return Project::fromMap(map);
}

QVariantMap DisTestProject::toMap() const
{
  QVariantMap map = Project::toMap();
  map.insert(QLatin1String(DISTEST_SETTINGS_KEY), this->_d->_disTestConfiguration->toMap());

  return map;
}

DisTestConfiguration* DisTestProject::disTestConfiguration() const
{
  return this->_d->_disTestConfiguration;
}

} // namespace distestproject
