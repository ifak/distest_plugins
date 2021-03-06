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

#include <coreplugin/dialogs/ioptionspage.h>

#include <QWidget>
#include <QPointer>
#include <QUuid>

namespace testcaseeditor {

namespace Internal {

class TestcaseEditorSettingsWidget
    : public QWidget
{
  Q_OBJECT

public:
  explicit TestcaseEditorSettingsWidget(QWidget *parent = 0);
  ~TestcaseEditorSettingsWidget();

private:
  class Private;
  Private* _d;
};

class TestcaseEditorSettingsPage
    : public Core::IOptionsPage
{
  Q_OBJECT

public:
  TestcaseEditorSettingsPage();
  ~TestcaseEditorSettingsPage();

public:
  QWidget*  createPage(QWidget *parent);
  void apply();
  void finish();
  bool matches(const QString& s) const;

private:
  QString                               _searchKeywords;
  QPointer<TestcaseEditorSettingsWidget>  _widget;
};

}// namespace Internal
}// namespace testcaseeditor
