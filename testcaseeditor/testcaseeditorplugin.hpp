/*
 * This file is part of distest_plugins.
 *
 * distest_plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * distest_plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with distest_plugins.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "testcaseeditor_global.hpp"

#include <extensionsystem/iplugin.h>

namespace Core{
class IEditor;
}

namespace testcaseeditor{

class TestCaseEditorWidget;
class TestCaseGraphicWidget;

class TestCaseEditorPlugin
    : public ExtensionSystem::IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "testcaseeditor.json")

public:
  TestCaseEditorPlugin();
  ~TestCaseEditorPlugin();

public:
  static TestCaseEditorPlugin* instance() { return _instance; }

public:
  bool          initialize(const QStringList &arguments,
                           QString *errorString);
  void          extensionsInitialized();
  ShutdownFlag  aboutToShutdown();

public:
  void  initializeEditor(TestCaseEditorWidget* editorWidget);
  void  initializeGraphicEditor(TestCaseGraphicWidget* editorWidget);

private:
  static TestCaseEditorPlugin* _instance;

private:
  Q_DISABLE_COPY(TestCaseEditorPlugin)
  class Private;
  Private*  _d;
};

} // namespace testcaseeditor
