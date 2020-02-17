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
#ifndef DISTESTEDITOR_TESTSYSTEMGRAPHICEDITOR_HPP
#define DISTESTEDITOR_TESTSYSTEMGRAPHICEDITOR_HPP

#include "distesteditor_global.hpp"

#include <coreplugin/editormanager/ieditor.h>

#include "testsystemgraphicwidget.hpp"

namespace model{ namespace ts{
class TestSystemItem;
}}

namespace distesteditor {

class DISTESTEDITOR_EXPORT TestSystemGraphicEditor
    : public Core::IEditor
{
  Q_OBJECT

public:
  TestSystemGraphicEditor(TestSystemGraphicWidget* testSystemGraphicWidget);
  ~TestSystemGraphicEditor();

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
  void                              setTestSystemItem(model::ts::TestSystemItem const* testSystemItem);
  model::ts::TestSystemItem const*  testSystemItem() const;

public:
  TestSystemGraphicWidget*  widget();
  QString                   fileName() const;

private:
  Q_DISABLE_COPY(TestSystemGraphicEditor)
  class Private;
  Private* _d;
};

} // namespace distesteditor

#endif // DISTESTEDITOR_TESTSYSTEMGRAPHICEDITOR_HPP
