#include "decleditor.hpp"
#include "decleditorwidget.hpp"
#include "distesteditorconstants.hpp"

#include <texteditor/texteditorsettings.h>

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

class DeclEditor::Private
{
  friend class DeclEditor;

  Private()
  {}

public:
  ~Private()
  {}
};

DeclEditor::DeclEditor(DeclEditorWidget *declTextEditorWidget)
  : TextEditor::BaseTextEditor(declTextEditorWidget),
    _d(new Private())
{}

DeclEditor::~DeclEditor()
{
  delete this->_d;
}

Core::Id DeclEditor::declEditorId()
{
  return Core::Id(Constants::DECLEDITOR_ID);
}

bool DeclEditor::duplicateSupported() const
{
  return true;
}

Core::IEditor *DeclEditor::duplicate(QWidget *parent)
{
  qDebug()<<"DeclEditor::duplicate() with parent:"<<parent<<" executed";

  // TODO: parent is 0, how to delete editorWidget??????
  // here we have a hack

  DeclEditorWidget* editorWidget = new DeclEditorWidget(parent);
  editorWidget->duplicateFrom(this->editorWidget());
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

bool DeclEditor::isTemporary() const
{
  return false;
}

Core::Id DeclEditor::id() const
{
  return DeclEditor::declEditorId();
}

DeclDocument *DeclEditor::document()
{
  return qobject_cast<DeclDocument*>(TextEditor::BaseTextEditor::document());
}
