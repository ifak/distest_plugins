#include "suteditor.hpp"
#include "suteditorwidget.hpp"
#include "suteditorconstants.hpp"
#include "suteditorplugin.hpp"

#include <coreplugin/coreconstants.h>
#include <texteditor/texteditorsettings.h>

#include <mobata/utils/functors.hpp>

#include <QDir>
#include <QTemporaryFile>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace suteditor;
using namespace suteditor::Internal;
using namespace model::ts;

class SutEditor::Private
{
  friend class SutEditor;
};

SutEditor::SutEditor(SutEditorWidget* sutEditorWidget)
  : TextEditor::BaseTextEditor(sutEditorWidget),
    _d(new Private)
{
  this->m_context.add(Constants::SUTEDITOR_CONTEXT);
  this->m_context.add(Constants::LANG_SUT);
  this->m_context.add(TextEditor::Constants::C_TEXTEDITOR);

  //graphic action///
//  QAction* sutGraphAction=new QAction(QIcon(QLatin1String(":/mobata/images/ts/sut.png")),
//                                         tr("update/create sut graphic..."),
//                                         this);
//  sutGraphAction->setStatusTip(tr("sut graphic"));
//  connect(sutGraphAction,
//          &QAction::triggered,
//          sutEditorWidget,
//          &SutEditorWidget::showSutGraphic);
//  this->toolBar()->addAction(sutGraphAction);
}

SutEditor::~SutEditor()
{
  delete this->_d;
}

Core::Id SutEditor::sutEditorId()
{
  return Core::Id(Constants::SUTEDITOR_ID);
}

bool SutEditor::duplicateSupported() const
{
  return true;
}

Core::IEditor* SutEditor::duplicate(QWidget *parent)
{
  SutEditorWidget* sutEditorWidget = new SutEditorWidget(parent);
  sutEditorWidget->duplicateFrom(this->editorWidget());
  SutEditorPlugin::instance()->initializeEditor(sutEditorWidget);;

  return sutEditorWidget->editor();
}

bool SutEditor::isTemporary() const
{
  return false;
}

Core::Id SutEditor::id() const
{
  return SutEditor::sutEditorId();
}

SutDocument* SutEditor::document()
{
  return qobject_cast<SutDocument*>(TextEditor::BaseTextEditor::document());
}

SutOutlineModel* SutEditor::sutOutlineModel()
{
  return this->document()?this->document()->sutOutlineModel():0;
}
