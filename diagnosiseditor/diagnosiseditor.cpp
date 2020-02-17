/*
 *  This file is part of Diagnosis Editor Plugin for AppCreator based application.
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

#include "diagnosiseditor.hpp"
#include "diagnosiseditorwidget.hpp"
#include "diagnosiseditorconstants.hpp"
#include "diagnosiseditorplugin.hpp"

#include <coreplugin/coreconstants.h>
#include <texteditor/texteditorsettings.h>

#include <mobata/utils/functors.hpp>

#include <QDir>
#include <QTemporaryFile>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace diagnosiseditor;
using namespace diagnosiseditor::Internal;
using namespace model::ts;

class DiagnosisEditor::Private
{
  friend class DiagnosisEditor;
};

DiagnosisEditor::DiagnosisEditor(DiagnosisEditorWidget* diagnosisEditorWidget)
  : TextEditor::BaseTextEditor(diagnosisEditorWidget),
    _d(new Private)
{
  this->m_context.add(Constants::DIAGNOSISEDITOR_CONTEXT);
  this->m_context.add(Constants::LANG_DIAGNOSIS);
  this->m_context.add(TextEditor::Constants::C_TEXTEDITOR);

  //graphic action///
//  QAction* diagnosisGraphAction=new QAction(QIcon(QLatin1String(":/mobata/images/diagnosis/diagnosis.png")),
//                                         tr("update/create diagnosis graphic..."),
//                                         this);
//  diagnosisGraphAction->setStatusTip(tr("diagnosis graphic"));
//  connect(diagnosisGraphAction,
//          &QAction::triggered,
//          diagnosisEditorWidget,
//          &DiagnosisEditorWidget::showDiagnosisGraphic);
//  this->toolBar()->addAction(diagnosisGraphAction);
}

DiagnosisEditor::~DiagnosisEditor()
{
  delete this->_d;
}

Core::Id DiagnosisEditor::diagnosisEditorId()
{
  return Core::Id(Constants::DIAGNOSISEDITOR_ID);
}

bool DiagnosisEditor::duplicateSupported() const
{
  return true;
}

Core::IEditor* DiagnosisEditor::duplicate(QWidget *parent)
{
  DiagnosisEditorWidget* diagnosisEditorWidget = new DiagnosisEditorWidget(parent);
  diagnosisEditorWidget->duplicateFrom(this->editorWidget());
  DiagnosisEditorPlugin::instance()->initializeEditor(diagnosisEditorWidget);;

  return diagnosisEditorWidget->editor();
}

bool DiagnosisEditor::isTemporary() const
{
  return false;
}

Core::Id DiagnosisEditor::id() const
{
  return DiagnosisEditor::diagnosisEditorId();
}

DiagnosisDocument* DiagnosisEditor::document()
{
  return qobject_cast<DiagnosisDocument*>(TextEditor::BaseTextEditor::document());
}

DiagnosisOutlineModel* DiagnosisEditor::diagnosisOutlineModel()
{
  return this->document()?this->document()->diagnosisOutlineModel():0;
}
