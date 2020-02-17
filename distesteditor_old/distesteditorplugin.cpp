#include "distesteditorplugin.hpp"

#include "distesteditorconstants.hpp"
#include "distestrendermanager.hpp"

#include "decleditorfactory.hpp"
#include "suteditorfactory.hpp"
#include "sutgraphicfactory.hpp"
#include "testsystemeditorfactory.hpp"
#include "testsystemgraphicfactory.hpp"
#include "testcaseeditorfactory.hpp"
#include "testcasegraphicfactory.hpp"
#include "testsuiteeditorfactory.hpp"
#include "distestmodeloutline.hpp"
#include "testreportgraphicfactory.hpp"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/mimedatabase.h>

#include <QAction>
#include <QMenu>
#include <QString>
#include <QDebug>

#include <QtPlugin>

#include <utils/qtcassert.h>

inline void initModelingResource() { Q_INIT_RESOURCE(mobata); }

namespace distesteditor{
namespace Internal{

class DisTestEditorPlugin::Private
{
  friend class DisTestEditorPlugin;

  Private() : _renderManager(DisTestRenderManager::createDisTestRenderManager())
  {
    this->_defaultStyleSheets=QLatin1String("");
  }

public:
  ~Private()
  {
    DisTestRenderManager::removeDisTestRenderManager();
  }

private:
  QString	_defaultStyleSheets;
  DisTestRenderManager* _renderManager;
};

DisTestEditorPlugin::DisTestEditorPlugin()
  : _d(new Private())
{
  // Create your members
}

DisTestEditorPlugin::~DisTestEditorPlugin()
{
  // Unregister objects from the plugin manager's object pool
  // Delete members
  delete this->_d;
}

bool DisTestEditorPlugin::initialize(const QStringList &arguments,
                                     QString *errorString)
{
  // Register objects in the plugin manager's object pool
  // Load settings
  // Add actions to menus
  // Connect to other plugins' signals
  // In the initialize method, a plugin can be sure that the plugins it
  // depends on have initialized their members.
  Q_UNUSED(arguments);

  initModelingResource();

  Core::MimeDatabase* mdb=Core::ICore::instance()->mimeDatabase();
  if(!mdb->addMimeTypes(QLatin1String(":/distesteditor/distesteditor.mimetypes.xml"),
                        errorString))
  {
    if(errorString)
    {
      *errorString+=QLatin1String("mimetype for distesteditor plugin "
                                  "could not be added!");
      qDebug()<<*errorString;
    }
    return false;
  }

  this->addAutoReleasedObject(new DeclEditorFactory(this));
//  this->addAutoReleasedObject(new SutEditorFactory(this));
//  this->addAutoReleasedObject(new SutGraphicFactory(this));
  this->addAutoReleasedObject(new TestSuiteEditorFactory(this));
//  this->addAutoReleasedObject(new TestSystemEditorFactory(this));
//  this->addAutoReleasedObject(new TestSystemGraphicFactory(this));
//  this->addAutoReleasedObject(new TestCaseEditorFactory(this));
//  this->addAutoReleasedObject(new TestCaseGraphicFactory(this));
  this->addAutoReleasedObject(new TestReportGraphicFactory(this));

  this->addAutoReleasedObject(new Internal::DisTestModelOutlineWidgetFactory());

  return true;
}

void DisTestEditorPlugin::extensionsInitialized()
{
  // Retrieve objects from the plugin manager's object pool
  // In the extensionsInitialized method, a plugin can be sure that all
  // plugins that depend on it are completely initialized.

  return;
}

ExtensionSystem::IPlugin::ShutdownFlag DisTestEditorPlugin::aboutToShutdown()
{
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  return SynchronousShutdown;
}

const QString& DisTestEditorPlugin::defaultStyleSheets() const
{
  return this->_d->_defaultStyleSheets;
}

}///end namespace Internal
}///end namespace distesteditor

//using namespace distesteditor;
//using namespace distesteditor::Internal;

Q_EXPORT_PLUGIN(distesteditor::Internal::DisTestEditorPlugin)

