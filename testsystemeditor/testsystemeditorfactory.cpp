/*
 *  This file is part of Test System Editor Plugin for AppCreator based application.
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

#include "testsystemeditorfactory.hpp"
#include "testsystemeditorconstants.hpp"
#include "testsystemeditorplugin.hpp"
#include "testsystemeditor.hpp"
#include "testsystemeditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace TextEditor;

namespace testsystemeditor{
namespace Internal{

class TestSystemEditorFactory::Private
{
  friend class TestSystemEditorFactory;

  Private(TestSystemEditorPlugin*	testSystemEditorPlugin)
    :	_testSystemEditorPlugin(testSystemEditorPlugin),
      _id(Constants::TESTSYSTEMEDITOR_ID)
  {
    this->_mimeTypes<<QLatin1String(Constants::TESTSYSTEM_MIME_TYPE);
  }

public:
  ~Private()
  {}

private:
  TestSystemEditorPlugin* _testSystemEditorPlugin;
  Core::Id                _id;
  QStringList             _mimeTypes;
};

TestSystemEditorFactory::TestSystemEditorFactory(TestSystemEditorPlugin* owner)
  :Core::IEditorFactory(owner),
    _d(new Private(owner))
{
  Q_ASSERT(this->_d->_testSystemEditorPlugin);
}

TestSystemEditorFactory::~TestSystemEditorFactory()
{
  delete this->_d;
}

QStringList TestSystemEditorFactory::mimeTypes() const
{
  return this->_d->_mimeTypes;
}

Core::Id TestSystemEditorFactory::id() const
{
  return this->_d->_id;
}

QString TestSystemEditorFactory::displayName() const
{
  return QLatin1String(Constants::TESTSYSTEMEDITOR_NAME);
}

Core::IEditor* TestSystemEditorFactory::createEditor(QWidget *parent)
{
  TestSystemEditorWidget* editorWidget = new TestSystemEditorWidget(parent);
  TestSystemEditorPlugin::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //namespace Internal
} //end namespace testsystemeditor
