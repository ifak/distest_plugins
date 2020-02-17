/*
 * This file is part of mobata.
 *
 * mobata is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * mobata is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with mobata.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DISTESTPROJECT_DISTESTPROJECTPLUGIN_HPP
#define DISTESTPROJECT_DISTESTPROJECTPLUGIN_HPP

#include <extensionsystem/iplugin.h>

class QAction;

namespace ProjectExplorer
{
class Project;
class Node;
}

namespace distestproject {
namespace Internal {

class DisTestProjectPlugin : public ExtensionSystem::IPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "distestproject.json")
  
public:
  DisTestProjectPlugin();
  ~DisTestProjectPlugin();
  
public:  
  bool initialize(const QStringList &arguments, QString *errorString);
  void extensionsInitialized();
  bool delayedInitialize();
  ShutdownFlag aboutToShutdown();

private slots:
  void showContextMenu(ProjectExplorer::Project *project,
                       ProjectExplorer::Node *node);
  void addTestCase();
  void addPrio();
  void startTestCase();

private:
  void hideAction(QAction* action);

private:
  Q_DISABLE_COPY(DisTestProjectPlugin)
  class Private;
  Private*  _d;
};

} // namespace Internal
} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTPROJECTPLUGIN_HPP

