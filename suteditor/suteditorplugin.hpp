/*
 *  This file is part of SUT Editor Plugin for AppCreator based application.
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

#include "suteditor_global.hpp"

#include <extensionsystem/iplugin.h>

#include <projectexplorer/toolchainmanager.h>
#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/kitmanager.h>
#include <projectexplorer/kit.h>
#include <projectexplorer/kitinformation.h>

namespace Core{
class IEditor;
}

namespace suteditor{

class SutEditorWidget;

namespace Internal{

class SutEditorPlugin
    : public ExtensionSystem::IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "suteditor.json")

public:
  SutEditorPlugin();
  ~SutEditorPlugin();

public:
  static SutEditorPlugin* instance() { return _instance; }

public:
  bool          initialize(const QStringList &arguments,
                           QString *errorString);
  void          extensionsInitialized();

  ShutdownFlag  aboutToShutdown();

public:
  void            initializeEditor(SutEditorWidget* editorWidget);

private:
  static SutEditorPlugin* _instance;

private:
  Q_DISABLE_COPY(SutEditorPlugin)
  class Private;
  Private*  _d;
};

} // namespace Internal
} // namespace suteditor
