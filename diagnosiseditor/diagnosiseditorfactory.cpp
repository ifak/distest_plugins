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

#include "diagnosiseditorfactory.hpp"
#include "diagnosiseditorconstants.hpp"
#include "diagnosiseditorplugin.hpp"
#include "diagnosiseditor.hpp"
#include "diagnosiseditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace TextEditor;

namespace diagnosiseditor{
namespace Internal{

class DiagnosisEditorFactory::Private
{
  friend class DiagnosisEditorFactory;

  Private(DiagnosisEditorPlugin*	diagnosisEditorPlugin)
    :	_diagnosisEditorPlugin(diagnosisEditorPlugin),
      _id(Constants::DIAGNOSISEDITOR_ID)
  {
      this->_mimeTypes<<QLatin1String(Constants::DIAGNOSIS_MIME_TYPE_RULE);
      this->_mimeTypes<<QLatin1String(Constants::DIAGNOSIS_MIME_TYPE_Component);
      this->_mimeTypes<<QLatin1String(Constants::DIAGNOSIS_MIME_TYPE_Signal);
  }

public:
  ~Private()
  {}

private:
  DiagnosisEditorPlugin* _diagnosisEditorPlugin;
  Core::Id              _id;
  QStringList           _mimeTypes;
};

DiagnosisEditorFactory::DiagnosisEditorFactory(DiagnosisEditorPlugin* owner)
  :Core::IEditorFactory(owner),
    _d(new Private(owner))
{
  Q_ASSERT(this->_d->_diagnosisEditorPlugin);
}

DiagnosisEditorFactory::~DiagnosisEditorFactory()
{
  delete this->_d;
}

QStringList DiagnosisEditorFactory::mimeTypes() const
{
  return this->_d->_mimeTypes;
}

Core::Id DiagnosisEditorFactory::id() const
{
  return this->_d->_id;
}

QString DiagnosisEditorFactory::displayName() const
{
  return QLatin1String(Constants::DIAGNOSISEDITOR_NAME);
}

Core::IEditor* DiagnosisEditorFactory::createEditor(QWidget *parent)
{
  DiagnosisEditorWidget* editorWidget = new DiagnosisEditorWidget(parent);
  DiagnosisEditorPlugin::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //namespace Internal
} //end namespace diagnosiseditor
