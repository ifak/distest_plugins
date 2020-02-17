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
#ifndef DISTESTEDITOR_TESTCASEEDITOR_HPP
#define DISTESTEDITOR_TESTCASEEDITOR_HPP

#include "distesteditor_global.hpp"

#include <texteditor/basetexteditor.h>

#include "testcasedocument.hpp"

namespace model{ namespace ts{
class TestCaseItem;
}}

namespace distesteditor{

class TestCaseEditorWidget;

class DISTESTEDITOR_EXPORT TestCaseEditor
    : public TextEditor::BaseTextEditor
{
  Q_OBJECT

public:
  explicit TestCaseEditor(TestCaseEditorWidget* testCaseTextEditorWidget);
  virtual ~TestCaseEditor();

private:
  void createActions();

public:
  static Core::Id    testCaseEditorId();

  bool              duplicateSupported() const;
  Core::IEditor*    duplicate(QWidget *parent);
  bool              isTemporary() const;
  Core::Id          id() const;

  TestCaseDocument* document();

public:
  void                            setTestCaseItem(model::ts::TestCaseItem const* testCaseItem);
  model::ts::TestCaseItem const*  testCaseItem() const;

private:
  Q_DISABLE_COPY(TestCaseEditor)
  class Private;
  Private* _d;
};

} //end namespace distesteditor
#endif //DISTESTEDITOR_TESTCASEEDITOR_H
