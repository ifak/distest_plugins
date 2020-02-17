/*
 *  This file is part of Test Case Editor Plugin for AppCreator based application.
 *
 *  Copyright (C) 2013 Jan Krause <jan.krause.no19@gmail.com>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
*/

#include "testcaseeditorfactory.hpp"
#include "testcaseeditorconstants.hpp"
#include "testcaseeditorplugin.hpp"
#include "testcaseeditor.hpp"
#include "testcaseeditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace TextEditor;

namespace testcaseeditor{

class TestCaseEditorFactory::Private
{
  friend class TestCaseEditorFactory;

  Private(TestCaseEditorPlugin*	testCaseEditorPlugin)
    :	_testCaseEditorPlugin(testCaseEditorPlugin),
      _id(Constants::TESTCASEEDITOR_ID)
  {
    this->_mimeTypes<<QLatin1String(Constants::TESTCASE_MIME_TYPE);
  }

public:
  ~Private()
  {}

private:
  TestCaseEditorPlugin* _testCaseEditorPlugin;
  Core::Id              _id;
  QStringList           _mimeTypes;
};

TestCaseEditorFactory::TestCaseEditorFactory(TestCaseEditorPlugin* owner)
  :Core::IEditorFactory(owner),
    _d(new Private(owner))
{
  Q_ASSERT(this->_d->_testCaseEditorPlugin);
}

TestCaseEditorFactory::~TestCaseEditorFactory()
{
  delete this->_d;
}

QStringList TestCaseEditorFactory::mimeTypes() const
{
  return this->_d->_mimeTypes;
}

Core::Id TestCaseEditorFactory::id() const
{
  return this->_d->_id;
}

QString TestCaseEditorFactory::displayName() const
{
  return QLatin1String(Constants::TESTCASEEDITOR_NAME);
}

Core::IEditor* TestCaseEditorFactory::createEditor(QWidget *parent)
{
  TestCaseEditorWidget* editorWidget = new TestCaseEditorWidget(parent);
  TestCaseEditorPlugin::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //end namespace testcaseeditor
