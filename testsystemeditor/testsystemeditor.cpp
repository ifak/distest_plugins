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

#include "testsystemeditor.hpp"
#include "testsystemeditorwidget.hpp"
#include "testsystemeditorconstants.hpp"
#include "testsystemeditorplugin.hpp"

#include <coreplugin/coreconstants.h>
#include <texteditor/texteditorsettings.h>

#include <mobata/utils/functors.hpp>

#include <QDir>
#include <QTemporaryFile>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace testsystemeditor;
using namespace testsystemeditor::Internal;
using namespace model::ts;

class TestSystemEditor::Private
{
  friend class TestSystemEditor;
};

TestSystemEditor::TestSystemEditor(TestSystemEditorWidget* testSystemEditorWidget)
  : TextEditor::BaseTextEditor(testSystemEditorWidget),
    _d(new Private)
{
  this->m_context.add(Constants::TESTSYSTEMEDITOR_CONTEXT);
  this->m_context.add(Constants::LANG_TESTSYSTEM);
  this->m_context.add(TextEditor::Constants::C_TEXTEDITOR);

  //graphic action///
//  QAction* testsystemGraphAction=new QAction(QIcon(QLatin1String(":/mobata/images/ts/testsystem.png")),
//                                         tr("update/create testsystem graphic..."),
//                                         this);
//  testsystemGraphAction->setStatusTip(tr("testsystem graphic"));
//  connect(testsystemGraphAction,
//          &QAction::triggered,
//          testsystemEditorWidget,
//          &TestSystemEditorWidget::showTestSystemGraphic);
//  this->toolBar()->addAction(testsystemGraphAction);
}

TestSystemEditor::~TestSystemEditor()
{
  delete this->_d;
}

Core::Id TestSystemEditor::testSystemEditorId()
{
  return Core::Id(Constants::TESTSYSTEMEDITOR_ID);
}

bool TestSystemEditor::duplicateSupported() const
{
  return true;
}

Core::IEditor* TestSystemEditor::duplicate(QWidget *parent)
{
  TestSystemEditorWidget* testSystemEditorWidget = new TestSystemEditorWidget(parent);
  testSystemEditorWidget->duplicateFrom(this->editorWidget());
  TestSystemEditorPlugin::instance()->initializeEditor(testSystemEditorWidget);;

  return testSystemEditorWidget->editor();
}

bool TestSystemEditor::isTemporary() const
{
  return false;
}

Core::Id TestSystemEditor::id() const
{
  return TestSystemEditor::testSystemEditorId();
}

TestSystemDocument* TestSystemEditor::document()
{
  return qobject_cast<TestSystemDocument*>(TextEditor::BaseTextEditor::document());
}

TestSystemOutlineModel* TestSystemEditor::testSystemOutlineModel()
{
  return this->document()?this->document()->testSystemOutlineModel():0;
}
