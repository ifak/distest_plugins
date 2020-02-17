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
#ifndef DISTESTEDITOR_TESTSUITEEDITOR_HPP
#define DISTESTEDITOR_TESTSUITEEDITOR_HPP

#include "distesteditor_global.hpp"

#include <texteditor/basetexteditor.h>

#include "testsuitedocument.hpp"

namespace model{ namespace ts{
class TestSuite;
}}

namespace distesteditor{

class TestSuiteEditorWidget;

class DISTESTEDITOR_EXPORT TestSuiteEditor
    : public TextEditor::BaseTextEditor
{
  Q_OBJECT

public:
  explicit TestSuiteEditor(TestSuiteEditorWidget* testSuiteTextEditorWidget);
  virtual ~TestSuiteEditor();

public:
  static Core::Id    testSuiteEditorId();

  bool            duplicateSupported() const;
  Core::IEditor*  duplicate(QWidget *parent);
  bool            isTemporary() const;
  Core::Id        id() const;

  TestSuiteDocument*   document();

public:
  void                        setTestSuite(model::ts::TestSuite const* testSuite);
  model::ts::TestSuite const* testSuite() const;

private:
  Q_DISABLE_COPY(TestSuiteEditor)
  class Private;
  QScopedPointer<Private> _d;
};

} //end namespace distesteditor
#endif //DISTESTEDITOR_TESTSUITEEDITOR_HPP
