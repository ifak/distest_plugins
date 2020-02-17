/*
 *  This file is part of Test System Editor Plugin for AppCreator based application.
 *
 *  Copyright (C) 2013 Jan Krause <jan.krause.no19@gmail.com>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
*/

#include "testsystemeditorplugin.hpp"

#include "testsystemeditorconstants.hpp"
#include "testsystemeditorfactory.hpp"
#include "testsystemhoverhandler.hpp"
#include "testsystemcompletionassist.hpp"
#include "testsystemeditoroutline.hpp"
#include "testsystemeditorwidget.hpp"

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

namespace testsystemeditor{
namespace Internal{

TestSystemEditorPlugin* TestSystemEditorPlugin::_instance = 0;

class TestSystemEditorPlugin::Private
{
  friend class TestSystemEditorPlugin;

  Private()
    : _actionHandler(0)
  {}

private:
  TextEditorActionHandler*  _actionHandler;
};

TestSystemEditorPlugin::TestSystemEditorPlugin()
  : _d(new Private())
{
  _instance = this;
}

TestSystemEditorPlugin::~TestSystemEditorPlugin()
{
  // Unregister objects from the plugin manager's object pool
  // Delete members
  delete this->_d->_actionHandler;
  delete this->_d;
}

bool TestSystemEditorPlugin::initialize(const QStringList &arguments,
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
  if(!mdb->addMimeTypes(QLatin1String(":/testsystemeditor/testsystemeditor.mimetypes.xml"),
                        errorString))
  {
    if(errorString)
    {
      *errorString+=QLatin1String("mimetype for testsystemeditor plugin "
                                  "could not be added!");
      qDebug()<<*errorString;
    }
    return false;
  }

  this->addAutoReleasedObject(new TestSystemEditorFactory(this));
  this->addAutoReleasedObject(new TestSystemHoverHandler(this));
  this->addAutoReleasedObject(new TestSystemCompletionAssistProvider);
  this->addAutoReleasedObject(new Internal::TestSystemEditorOutlineWidgetFactory());

  this->_d->_actionHandler = new TextEditorActionHandler(Constants::TESTSYSTEMEDITOR_CONTEXT,
                                                         TextEditorActionHandler::Format
                                                         | TextEditorActionHandler::UnCommentSelection
                                                         | TextEditorActionHandler::UnCollapseAll);
  this->_d->_actionHandler->initializeActions();

  return true;
}

void TestSystemEditorPlugin::extensionsInitialized()
{
  // Retrieve objects from the plugin manager's object pool
  // In the extensionsInitialized method, a plugin can be sure that all
  // plugins that depend on it are completely initialized.

  return;
}

ExtensionSystem::IPlugin::ShutdownFlag TestSystemEditorPlugin::aboutToShutdown()
{
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  return SynchronousShutdown;
}

void TestSystemEditorPlugin::initializeEditor(TestSystemEditorWidget* editorWidget)
{
  QTC_CHECK(_instance);
  this->_d->_actionHandler->setupActions(editorWidget);
  TextEditorSettings::instance()->initializeEditor(editorWidget);

  return;
}

}///end namespace Internal
}///end namespace testsystemeditor

Q_EXPORT_PLUGIN(testsystemeditor::Internal::TestSystemEditorPlugin)

