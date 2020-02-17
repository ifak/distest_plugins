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
#ifndef DISTESTEDITOR_TESTSYSTEMEDITORFACTORY_HPP
#define DISTESTEDITOR_TESTSYSTEMEDITORFACTORY_HPP

#include <coreplugin/editormanager/ieditorfactory.h>

namespace distesteditor{
namespace Internal{

class DisTestEditorPlugin;

class TestSystemEditorFactory : public Core::IEditorFactory
{
  Q_OBJECT

public:
  explicit TestSystemEditorFactory(DisTestEditorPlugin *owner);
  virtual ~TestSystemEditorFactory();

public:
  QStringList     mimeTypes() const;
  Core::Id        id() const;
  QString         displayName() const;
  Core::IEditor*  createEditor(QWidget *parent);

private:
  Q_DISABLE_COPY(TestSystemEditorFactory)
  class Private;
  QScopedPointer<Private> _d;
};

} //end namespace Internal
} //end namespace distesteditor

#endif //DISTESTEDITOR_TESTSYSTEMEDITORFACTORY_HPP
