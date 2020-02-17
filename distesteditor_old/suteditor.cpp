#include "suteditor.hpp"

#include "suteditorwidget.hpp"
#include "distesteditorconstants.hpp"

#include <utils/qtcassert.h>
#include <texteditor/texteditorsettings.h>

#include <mobata/utils/functors.hpp>

#include <QDir>
#include <QTemporaryFile>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

class SutEditor::Private
{
  friend class SutEditor;

  Private()
    : _sutItem(0)
  {}

public:
  ~Private()
  {}

private:
  model::ts::SutItem const* _sutItem;
};

SutEditor::SutEditor(SutEditorWidget* sutTextEditorWidget)
  : TextEditor::BaseTextEditor(sutTextEditorWidget),
    _d(new Private())
{
  this->createActions();
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
  SutEditorWidget* editorWidget = new SutEditorWidget(parent);
  editorWidget->duplicateFrom(this->editorWidget());
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
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

void SutEditor::createActions()
{
  TextEditor::BaseTextEditorWidget* textEditorWidget=this->editorWidget();
  SutEditorWidget* sutTextEditorWidget = utils::simple_cast<SutEditorWidget*>(textEditorWidget);
  Q_ASSERT(sutTextEditorWidget);

  QAction* sutGraphAction=new QAction(QIcon(QLatin1String(":/mobata/images/ts/sut.png")),
                                           tr("update/create sut graphic..."),
                                           this);
  sutGraphAction->setStatusTip(tr("sut graphic"));
  connect(sutGraphAction,
          &QAction::triggered,
          sutTextEditorWidget,
          &SutEditorWidget::showSutGraphic);
  this->toolBar()->addAction(sutGraphAction);

  return;
}

void SutEditor::setSutItem(model::ts::SutItem const* sutItem)
{
  this->_d->_sutItem=sutItem;
}

model::ts::SutItem const* SutEditor::sutItem() const
{
  return this->_d->_sutItem;
}
