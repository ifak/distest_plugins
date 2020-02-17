#include "distestprojectplugin.hpp"

#include "distestprojectconstants.hpp"
#include "distestprojectwizard.hpp"
#include "distestcasewizard.hpp"
#include "distestproject.hpp"
#include "helpers.hpp"

#include "globalrendersettings.hpp"
#include "testexecutionview.hpp"
#include "testreportgraphicfactory.hpp"

#include <app/app_version.h>

#include <utils/hostosinfo.h>

#include <extensionsystem/pluginmanager.h>

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/mimedatabase.h>
#include <coreplugin/fileiconprovider.h>
#include <coreplugin/modemanager.h>
#include <coreplugin/imode.h>
#include <coreplugin/dialogs/iwizard.h>

#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/toolchainmanager.h>
#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/kitmanager.h>
#include <projectexplorer/kit.h>
#include <projectexplorer/kitinformation.h>
#include <projectexplorer/projectnodes.h>
#include <projectexplorer/buildmanager.h>

#include <QAction>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QDir>
#include <QFileDialog>

#include <QtPlugin>
#include <QApplication>

#include <mobata/memory_leak_start.hpp>

inline void initMobataResource() { Q_INIT_RESOURCE(mobata); }
inline void initDisTestProjectResource() { Q_INIT_RESOURCE(distestproject); }

namespace distestproject{
namespace Internal{

class DisTestProjectPlugin::Private
{
  friend class DisTestProjectPlugin;

  Private()
    : _toolChainsRegistered(false),
      _testCasesMenu(nullptr),
      _testCaseMenu(nullptr),
      _addTestCaseAction(nullptr),
      _contextProject(nullptr),
      _contextNode(nullptr),
      _globalRenderSettings(distestproject::GlobalRenderSettings::createGlobalRenderSettings())
  {}

public:
  ~Private()
  {
      distestproject::GlobalRenderSettings::removeGlobalRenderSettings();
  }

private:
  bool                                  _toolChainsRegistered;
  QList<QAction*>                       _hideActions;
  QMenu*                                _testCasesMenu;
  QMenu*                                _testCaseMenu;
  QMenu*                                _prioMenu;
  QAction*                              _addPrioAction;
  QAction*                              _addTestCaseAction;
  QAction*                              _startTestCaseAction;
  ProjectExplorer::Project*             _contextProject;
  ProjectExplorer::Node*                _contextNode;
  distestproject::GlobalRenderSettings* _globalRenderSettings;
};

DisTestProjectPlugin::DisTestProjectPlugin()
  : _d(new Private())
{
  // Create your members
}

DisTestProjectPlugin::~DisTestProjectPlugin()
{
  // Unregister objects from the plugin manager's object pool
  // Delete members

  delete this->_d;
}

bool DisTestProjectPlugin::initialize(const QStringList &arguments, QString *errorString)
{
  // Register objects in the plugin manager's object pool
  // Load settings
  // Add actions to menus
  // Connect to other plugins' signals
  // In the initialize method, a plugin can be sure that the plugins it
  // depends on have initialized their members.

  Q_UNUSED(arguments);
  Q_UNUSED(errorString);

  initMobataResource();
  initDisTestProjectResource();

  Core::MimeDatabase* mdb=Core::ICore::instance()->mimeDatabase();
  if(!mdb->addMimeTypes(QLatin1String(":/distestproject/distestproject.mimetypes.xml"),
                        errorString))
  {
    if(errorString)
    {
      *errorString+=QLatin1String("mimetype for distestproject plugin "
                                  "could not be added!");
      qDebug()<<*errorString;
    }
    return false;
  }

  // add test cases menu + action/////////
  connect(ProjectExplorer::ProjectExplorerPlugin::instance(),
          &ProjectExplorer::ProjectExplorerPlugin::aboutToShowContextMenu,
          this, &DisTestProjectPlugin::showContextMenu);

  Core::Context projectTreeContext(ProjectExplorer::Constants::C_PROJECT_TREE);

  Core::ActionContainer*  folderContextMenu =
      Core::ActionManager::createMenu(ProjectExplorer::Constants::M_FOLDERCONTEXT);
  this->_d->_testCasesMenu=folderContextMenu->menu();
  Q_ASSERT(this->_d->_testCasesMenu);

  // new action
  this->_d->_addTestCaseAction = new QAction(tr("Add Test Case..."), this);
  Core::Command* cmd = Core::ActionManager::registerAction(this->_d->_addTestCaseAction,
                                                           Constants::ACTION_ADDTESTCASE,
                                                           projectTreeContext);
  cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+T")));
  folderContextMenu->addAction(cmd);

  connect(this->_d->_addTestCaseAction, &QAction::triggered,
          this, &DisTestProjectPlugin::addTestCase);




  Core::ActionContainer*  folderContextMenu2 =
      Core::ActionManager::createMenu("95484");

  this->_d->_prioMenu=folderContextMenu2->menu();
  Q_ASSERT(this->_d->_prioMenu);

  // new action
  this->_d->_addPrioAction = new QAction(tr("Add Prio File..."), this);
  Core::Command* cmd2 = Core::ActionManager::registerAction(this->_d->_addPrioAction,
                                                           Constants::ACTION_ADDPRIO,
                                                           projectTreeContext);
  folderContextMenu2->addAction(cmd2);

  connect(this->_d->_addPrioAction, &QAction::triggered,
          this, &DisTestProjectPlugin::addPrio);





  ///test case wizard////////////////
  Core::BaseFileWizardParameters testCaseParams(Core::IWizard::FileWizard);
  testCaseParams.setCategory(QLatin1String("P.distest"));
  testCaseParams.setDisplayCategory(tr("DisTest"));
  testCaseParams.setDescription(tr("Creates and adds a new test case..."));
  testCaseParams.setDisplayName(tr("Test Case"));
  testCaseParams.setId(QStringLiteral("DisTest.testcase"));
  this->addAutoReleasedObject(new DisTestCaseWizard(testCaseParams));

  Core::FileIconProvider *iconProvider = Core::FileIconProvider::instance();
  iconProvider->registerIconOverlayForSuffix(QIcon(QLatin1String(":/mobata/images/base/manytype.png")),
                                             QLatin1String("decl"));
  iconProvider->registerIconOverlayForSuffix(QIcon(QLatin1String(":/mobata/images/ts/sut.png")),
                                             QLatin1String("sut"));
  iconProvider->registerIconOverlayForSuffix(QIcon(QLatin1String(":/mobata/images/ts/testsystem.png")),
                                             QLatin1String("testsystem"));
  iconProvider->registerIconOverlayForSuffix(QIcon(QLatin1String(":/mobata/images/ts/manytestcase.png")),
                                             QLatin1String("testgroup"));
  iconProvider->registerIconOverlayForSuffix(QIcon(QLatin1String(":/mobata/images/ts/testcase.png")),
                                             QLatin1String("testcase"));

  this->addAutoReleasedObject(new TestExecutionViewFactory);
  this->addAutoReleasedObject(new TestReportGraphicFactory);

  return true;
}

void DisTestProjectPlugin::extensionsInitialized()
{
// Retrieve objects from the plugin manager's object pool
// In the extensionsInitialized method, a plugin can be sure that all
// plugins that depend on it are completely initialized.

  Core::ActionManager* actionManager=Core::ActionManager::instance();
  Q_ASSERT(actionManager);

  /// hide "debug" menu
  Core::ActionContainer* actContainer =actionManager->actionContainer(ProjectExplorer
                                                                      ::Constants
                                                                      ::M_DEBUG);
  if(actContainer)
    this->hideAction(actContainer->menu()->menuAction());

  ///hide session context menu actions....
  Core::Command* sessionCmd=actionManager->command(ProjectExplorer::Constants::BUILDSESSION);
  if(sessionCmd)
    this->hideAction(sessionCmd->action());

  sessionCmd=actionManager->command(ProjectExplorer::Constants::DEPLOYSESSION);
  if(sessionCmd)
    this->hideAction(sessionCmd->action());

  sessionCmd=actionManager->command(ProjectExplorer::Constants::REBUILDSESSION);
  if(sessionCmd)
    this->hideAction(sessionCmd->action());

  sessionCmd=actionManager->command(ProjectExplorer::Constants::CLEANSESSION);
  if(sessionCmd)
    this->hideAction(sessionCmd->action());

  return;
}

bool DisTestProjectPlugin::delayedInitialize()
{
  return true;
}

ExtensionSystem::IPlugin::ShutdownFlag DisTestProjectPlugin::aboutToShutdown()
{
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  return SynchronousShutdown;
}

void DisTestProjectPlugin::showContextMenu(ProjectExplorer::Project* project,
                                           ProjectExplorer::Node* node)
{
  this->_d->_contextProject=project;
  this->_d->_contextNode=node;

  if(this->_d->_contextNode->displayName() == QStringLiteral("test cases"))
    this->_d->_testCasesMenu->popup(QCursor::pos());

  if(this->_d->_contextNode->displayName() == QStringLiteral("prioritization"))
    this->_d->_prioMenu->popup(QCursor::pos());

//  if(this->_d->_contextNode->displayName().endsWith(QStringLiteral(".testcase")))
//    this->_d->_testCaseMenu->popup(QCursor::pos());

  return;
}

void DisTestProjectPlugin::addTestCase()
{
  typedef  QList<DisTestCaseWizard*> TestCaseWizardList;

  TestCaseWizardList testCaseWizards = ExtensionSystem::PluginManager::getObjects<DisTestCaseWizard>();
  Q_ASSERT(testCaseWizards.size()==1);

  DisTestCaseWizard* testCaseWizard=testCaseWizards.first();
  testCaseWizard->setContextNode(this->_d->_contextNode);
  testCaseWizard->setContextProject(this->_d->_contextProject);

  QString defaultPath=QDir::homePath();
  if(this->_d->_contextNode)
  {
    defaultPath=this->_d->_contextNode->path();
    defaultPath= QFileInfo(defaultPath).absolutePath();
  }

  qDebug()<< "DisTestProjectPlugin::addTestCase()" << defaultPath;
  Core::ICore::showNewItemDialog(QObject::tr("Add new test case..."),
                                 QList<Core::IWizard*>()<<testCaseWizard,
                                 defaultPath);

  this->_d->_contextNode=nullptr;
  this->_d->_contextProject=nullptr;

  return;
}

void DisTestProjectPlugin::addPrio()
{
  QString prioPath = QFileDialog::getOpenFileName(nullptr,
                                                  "Add Prio File",
                                                  this->_d->_contextProject->projectDirectory(),
                                                  "Prio File(*.prio)");
  if(prioPath == ""){
    return;
  }

  DisTestProject* project = dynamic_cast<DisTestProject*>(this->_d->_contextProject);
  Q_ASSERT(project);
  QString errorString;
  project->addPrioFile(prioPath, &errorString);

  return;
}

void DisTestProjectPlugin::startTestCase()
{
  Q_ASSERT(this->_d->_contextNode);



  //Core::EditorManager::openEditor(d->m_currentNode->path());
  qDebug()<< "startTestCase";
}

void DisTestProjectPlugin::hideAction(QAction *action)
{
  if(action)
  {
    action->setVisible(false);
    this->_d->_hideActions.append(action);
  }

  return;
}

}///end namespace Internal
}///end namespace distestproject

//using namespace distestproject;
//using namespace distestproject::Internal;

Q_EXPORT_PLUGIN(distestproject::Internal::DisTestProjectPlugin)

