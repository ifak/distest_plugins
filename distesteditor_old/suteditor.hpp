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
#ifndef DISTESTEDITOR_SUTEDITOR_HPP
#define DISTESTEDITOR_SUTEDITOR_HPP

#include "distesteditor_global.hpp"

#include <texteditor/basetexteditor.h>

#include "sutdocument.hpp"

namespace model{ namespace ts{
class SutItem;
}}

namespace distesteditor{

class SutEditorWidget;

class DISTESTEDITOR_EXPORT SutEditor
    : public TextEditor::BaseTextEditor
{
  Q_OBJECT

public:
  explicit SutEditor(SutEditorWidget* sutTextEditorWidget);
  virtual ~SutEditor();

private:
  void createActions();

public:
  static Core::Id sutEditorId();

  bool            duplicateSupported() const;
  Core::IEditor*  duplicate(QWidget *parent);
  bool            isTemporary() const;
  Core::Id        id() const;

  SutDocument*    document();

public:
  void                      setSutItem(model::ts::SutItem const* sutItem);
  model::ts::SutItem const* sutItem() const;

private:
  Q_DISABLE_COPY(SutEditor)
  class Private;
  Private* _d;
};

} //end namespace distesteditor
#endif //DISTESTEDITOR_SUTEDITOR_H
