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
#pragma once

#include "testcaseeditor_global.hpp"

#include <coreplugin/editormanager/ieditorfactory.h>

namespace testcaseeditor {

class TESTCASEEDITOR_EXPORT TestCaseGraphicFactory
    : public Core::IEditorFactory
{
  Q_OBJECT
public slots:
    void refreshGraphicIn();
signals:
    void refreshGraphicOut();
public:
  TestCaseGraphicFactory(QObject *parent = 0);
  virtual ~TestCaseGraphicFactory();

public:
  Core::IEditor*  createEditor(QWidget* parent);
  QStringList     mimeTypes() const;
  Core::Id        id() const;
  QString         displayName() const;
};

} // namespace testcaseeditor
