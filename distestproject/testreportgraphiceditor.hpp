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

#include "distestproject_global.hpp"

#include <coreplugin/editormanager/ieditor.h>

class QQuickWidget;

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT TestReportGraphicEditor
    : public Core::IEditor
{
  Q_OBJECT

public:
  TestReportGraphicEditor(QQuickWidget* testReportGraphicWidget);
  virtual ~TestReportGraphicEditor();

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

private:
  Q_DISABLE_COPY(TestReportGraphicEditor)
  class Private;
  Private* _d;
};

} // namespace distestproject
