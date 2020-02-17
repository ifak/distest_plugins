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
#ifndef DISTESTEDITOR_TESTCASEGRAPHICEDITOR_HPP
#define DISTESTEDITOR_TESTCASEGRAPHICEDITOR_HPP

#include "distesteditor_global.hpp"

#include <coreplugin/editormanager/ieditor.h>

#include "testcasegraphicwidget.hpp"

namespace model{ namespace ts{
class TestCaseItem;
}}

namespace distesteditor {

class DISTESTEDITOR_EXPORT TestCaseGraphicEditor
    : public Core::IEditor
{
  Q_OBJECT

public:
  TestCaseGraphicEditor(TestCaseGraphicWidget* testCaseGraphicWidget);
  virtual ~TestCaseGraphicEditor();

public:
  virtual bool              createNew(const QString &contents = QString());
  virtual bool              open(QString *errorString,
                                 const QString &fileName,
                                 const QString &realFileName);
  virtual Core::IDocument*  document();
  virtual Core::Id          id() const;
  virtual QString           displayName() const;
  virtual void              setDisplayName(const QString &title);
  virtual bool              isTemporary() const;
  virtual QWidget*          toolBar();

public:
  void                            setTestCaseItem(model::ts::TestCaseItem const* testCaseItem);
  model::ts::TestCaseItem const*  testCaseItem() const;

public:
  TestCaseGraphicWidget*  widget();
  QString                 fileName() const;

private:
  Q_DISABLE_COPY(TestCaseGraphicEditor)
  class Private;
  Private* _d;
};

} // namespace distesteditor

#endif // DISTESTEDITOR_TESTCASEGRAPHICEDITOR_HPP
