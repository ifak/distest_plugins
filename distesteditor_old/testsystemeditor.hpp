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
#ifndef DISTESTEDITOR_TESTSYSTEMEDITOR_HPP
#define DISTESTEDITOR_TESTSYSTEMEDITOR_HPP

#include "distesteditor_global.hpp"

#include <texteditor/basetexteditor.h>

#include "testsystemdocument.hpp"

namespace model{ namespace ts{
class TestSystemItem;
}}

namespace distesteditor{

class TestSystemEditorWidget;

class DISTESTEDITOR_EXPORT TestSystemEditor
    : public TextEditor::BaseTextEditor
{
  Q_OBJECT

public:
  explicit TestSystemEditor(TestSystemEditorWidget* testSystemTextEditorWidget);
  virtual ~TestSystemEditor();

private:
  void createActions();

public:
  static
  Core::Id            testSystemEditorId();

  bool                duplicateSupported() const;
  Core::IEditor*      duplicate(QWidget *parent);
  bool                isTemporary() const;
  Core::Id            id() const;

  TestSystemDocument* document();

public:
  void                              setTestSystemItem(model::ts::TestSystemItem const* testSystemItem);
  model::ts::TestSystemItem const*  testSystemItem() const;

private:
  Q_DISABLE_COPY(TestSystemEditor)
  class Private;
  QScopedPointer<Private> _d;
};

} //end namespace distesteditor

#endif //DISTESTEDITOR_TESTSYSTEMEDITOR_HPP
