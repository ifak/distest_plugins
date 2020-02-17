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
#ifndef DISTESTEDITOR_DECLEDITORFACTORY_HPP
#define DISTESTEDITOR_DECLEDITORFACTORY_HPP

#include <coreplugin/editormanager/ieditorfactory.h>

namespace distesteditor{
namespace Internal{

class DisTestEditorPlugin;

class DeclEditorFactory : public Core::IEditorFactory
{
  Q_OBJECT

public:
  explicit DeclEditorFactory(DisTestEditorPlugin *owner);
  virtual ~DeclEditorFactory();

public:
  QStringList     mimeTypes() const;
  Core::Id        id() const;
  QString         displayName() const;
  Core::IEditor*  createEditor(QWidget *parent);

private:
  Q_DISABLE_COPY(DeclEditorFactory)
  class Private;
  QScopedPointer<Private> _d;
};

} //end namespace Internal
} //end namespace distesteditor
#endif //DISTESTEDITOR_DECLEDITORFACTORY_HPP
