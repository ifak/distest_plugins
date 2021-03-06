#include "suteditorplugin.hpp"

#include "suteditorconstants.hpp"
#include "suteditorfactory.hpp"
#include "suthoverhandler.hpp"
#include "sutcompletionassist.hpp"
#include "suteditoroutline.hpp"
#include "suteditorwidget.hpp"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/mimedatabase.h>

#include <texteditor/texteditorplugin.h>
#include <texteditor/texteditorsettings.h>
#include <texteditor/texteditoractionhandler.h>
#include <texteditor/texteditorconstants.h>

#include <QAction>
#include <QMenu>
#include <QString>
#include <QDebug>

#include <QtPlugin>

#include <utils/qtcassert.h>

inline void initMobataResource() { Q_INIT_RESOURCE(mobata); }

using namespace TextEditor;

namespace suteditor{
namespace Internal{

SutEditorPlugin* SutEditorPlugin::_instance = 0;

class SutEditorPlugin::Private
{
  friend class SutEditorPlugin;

  Private()
    : _actionHandler(0)
  {}

private:
  TextEditorActionHandler*  _actionHandler;
};

SutEditorPlugin::SutEditorPlugin()
  : _d(new Private())
{
  _instance = this;
}

SutEditorPlugin::~SutEditorPlugin()
{
  // Unregister objects from the plugin manager's object pool
  // Delete members
  delete this->_d->_actionHandler;
  delete this->_d;
}

bool SutEditorPlugin::initialize(const QStringList &arguments,
                                    QString *errorString)
{
  // Register objects in the plugin manager's object pool
  // Load settings
  // Add actions to menus
  // Connect to other plugins' signals
  // In the initialize method, a plugin can be sure that the plugins it
  // depends on have initialized their members.
  Q_UNUSED(arguments);

  initMobataResource();

  Core::MimeDatabase* mdb=Core::ICore::instance()->mimeDatabase();
  if(!mdb->addMimeTypes(QLatin1String(":/suteditor/suteditor.mimetypes.xml"),
                        errorString))
  {
    if(errorString)
    {
      *errorString+=QLatin1String("mimetype for suteditor plugin "
                                  "could not be added!");
      qDebug()<<*errorString;
    }
    return false;
  }

  this->addAutoReleasedObject(new SutEditorFactory(this));
  this->addAutoReleasedObject(new SutHoverHandler(this));
  this->addAutoReleasedObject(new SutCompletionAssistProvider);
  this->addAutoReleasedObject(new Internal::SutEditorOutlineWidgetFactory());

  this->_d->_actionHandler = new TextEditorActionHandler(Constants::SUTEDITOR_CONTEXT,
                                                         TextEditorActionHandler::Format
                                                         | TextEditorActionHandler::UnCommentSelection
                                                         | TextEditorActionHandler::UnCollapseAll);
  this->_d->_actionHandler->initializeActions();

  return true;
}

void SutEditorPlugin::extensionsInitialized()
{
  // Retrieve objects from the plugin manager's object pool
  // In the extensionsInitialized method, a plugin can be sure that all
  // plugins that depend on it are completely initialized.

  return;
}

ExtensionSystem::IPlugin::ShutdownFlag SutEditorPlugin::aboutToShutdown()
{
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  return SynchronousShutdown;
}

void SutEditorPlugin::initializeEditor(SutEditorWidget* editorWidget)
{
  QTC_CHECK(_instance);
  this->_d->_actionHandler->setupActions(editorWidget);
  TextEditorSettings::instance()->initializeEditor(editorWidget);

  return;
}

}///end namespace Internal
}///end namespace suteditor

Q_EXPORT_PLUGIN(suteditor::Internal::SutEditorPlugin)

