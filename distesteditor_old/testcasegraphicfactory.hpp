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
#ifndef DISTESTEDITOR_TESTCASEGRAPHICFACTORY_HPP
#define DISTESTEDITOR_TESTCASEGRAPHICFACTORY_HPP

#include "distesteditor_global.hpp"

#include <coreplugin/editormanager/ieditorfactory.h>

namespace distesteditor {

class DISTESTEDITOR_EXPORT TestCaseGraphicFactory
    : public Core::IEditorFactory
{
  Q_OBJECT

public:
  TestCaseGraphicFactory(QObject *parent = 0);
  virtual ~TestCaseGraphicFactory();

public:
  Core::IEditor*  createEditor(QWidget* parent);
  QStringList     mimeTypes() const;
  Core::Id        id() const;
  QString         displayName() const;
};

} // namespace distesteditor

#endif // DISTESTEDITOR_TESTCASEGRAPHICFACTORY_HPP
