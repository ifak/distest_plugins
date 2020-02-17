/*
 *  This file is part of Testsystem Editor Plugin for AppCreator based application.
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

#include <extensionsystem/iplugin.h>

namespace Core{
class IEditor;
}

namespace testsystemeditor{

class TestSystemEditorWidget;

namespace Internal{

class TestSystemEditorPlugin
    : public ExtensionSystem::IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "testsystemeditor.json")

public:
  TestSystemEditorPlugin();
  ~TestSystemEditorPlugin();

public:
  static TestSystemEditorPlugin* instance() { return _instance; }

public:
  bool          initialize(const QStringList& arguments,
                           QString* errorString);
  void          extensionsInitialized();
  ShutdownFlag  aboutToShutdown();

public:
  void  initializeEditor(TestSystemEditorWidget* editorWidget);

private:
  static TestSystemEditorPlugin* _instance;

private:
  Q_DISABLE_COPY(TestSystemEditorPlugin)
  class Private;
  Private*  _d;
};

} // namespace Internal
} // namespace testsystemeditor
