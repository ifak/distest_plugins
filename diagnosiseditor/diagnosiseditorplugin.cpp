/*
 *  This file is part of Diagnosis Editor Plugin for AppCreator based application.
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

#include "diagnosiseditorplugin.hpp"

#include "diagnosiseditorconstants.hpp"
#include "diagnosiseditorfactory.hpp"
#include "diagnosishoverhandler.hpp"
#include "diagnosiscompletionassist.hpp"
#include "diagnosiseditoroutline.hpp"
#include "diagnosiseditorwidget.hpp"

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

inline void initModelingResource() { Q_INIT_RESOURCE(mobata); }

using namespace TextEditor;

namespace diagnosiseditor{
namespace Internal{

DiagnosisEditorPlugin* DiagnosisEditorPlugin::_instance = 0;

class DiagnosisEditorPlugin::Private
{
  friend class DiagnosisEditorPlugin;

  Private()
    : _actionHandler(0)
  {}

private:
  TextEditorActionHandler*  _actionHandler;
};

DiagnosisEditorPlugin::DiagnosisEditorPlugin()
  : _d(new Private())
{
  _instance = this;
}

DiagnosisEditorPlugin::~DiagnosisEditorPlugin()
{
  // Unregister objects from the plugin manager's object pool
  // Delete members
  delete this->_d->_actionHandler;
  delete this->_d;
}

bool DiagnosisEditorPlugin::initialize(const QStringList &arguments,
                                      QString* errorString)
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
  if(!mdb->addMimeTypes(QLatin1String(":/diagnosiseditor/diagnosiseditor.mimetypes.xml"),
                        errorString))
  {
    if(errorString)
    {
      *errorString+=QLatin1String("mimetype for diagnosiseditor plugin "
                                  "could not be added!");
      qDebug()<<*errorString;
    }
    return false;
  }

  this->addAutoReleasedObject(new DiagnosisEditorFactory(this));
  this->addAutoReleasedObject(new DiagnosisHoverHandler(this));
  this->addAutoReleasedObject(new DiagnosisCompletionAssistProvider);
  this->addAutoReleasedObject(new Internal::DiagnosisEditorOutlineWidgetFactory());

  this->_d->_actionHandler = new TextEditorActionHandler(Constants::DIAGNOSISEDITOR_CONTEXT,
                                                         TextEditorActionHandler::Format
                                                         | TextEditorActionHandler::UnCommentSelection
                                                         | TextEditorActionHandler::UnCollapseAll);
  this->_d->_actionHandler->initializeActions();

  return true;
}

void DiagnosisEditorPlugin::extensionsInitialized()
{
  // Retrieve objects from the plugin manager's object pool
  // In the extensionsInitialized method, a plugin can be sure that all
  // plugins that depend on it are completely initialized.

  return;
}

ExtensionSystem::IPlugin::ShutdownFlag DiagnosisEditorPlugin::aboutToShutdown()
{
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  return SynchronousShutdown;
}

void DiagnosisEditorPlugin::initializeEditor(DiagnosisEditorWidget* editorWidget)
{
  QTC_CHECK(_instance);
  this->_d->_actionHandler->setupActions(editorWidget);
  TextEditorSettings::instance()->initializeEditor(editorWidget);

  return;
}

}///end namespace Internal
}///end namespace diagnosiseditor

Q_EXPORT_PLUGIN(diagnosiseditor::Internal::DiagnosisEditorPlugin)

