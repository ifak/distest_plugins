#include "testsystemeditor.hpp"
#include "testsystemeditorwidget.hpp"
#include "distesteditorconstants.hpp"

#include <texteditor/texteditorsettings.h>

#include <mobata/utils/functors.hpp>

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

class TestSystemEditor::Private
{
  friend class TestSystemEditor;

  Private()
    : _testSystemItem(0)
  {}

public:
  ~Private()
  {}

private:
  model::ts::TestSystemItem const*  _testSystemItem;
};

TestSystemEditor::TestSystemEditor(TestSystemEditorWidget* testSystemTextEditorWidget)
  : TextEditor::BaseTextEditor(testSystemTextEditorWidget),
    _d(new Private())
{
  this->createActions();
}

TestSystemEditor::~TestSystemEditor()
{}

void TestSystemEditor::createActions()
{
  TextEditor::BaseTextEditorWidget* textEditorWidget=this->editorWidget();
  TestSystemEditorWidget* baseTestSystemEditorWidget=
      utils::simple_cast<TestSystemEditorWidget*>(textEditorWidget);
  Q_ASSERT(baseTestSystemEditorWidget);

  QAction* testSystemGraphAction=new QAction(QIcon(QLatin1String(":/mobata/images/ts/testsystem.png")),
                                             tr("update/create test system graphic..."),
                                             this);
  testSystemGraphAction->setStatusTip(tr("test system graphic"));
  connect(testSystemGraphAction,
          &QAction::triggered,
          baseTestSystemEditorWidget,
          &TestSystemEditorWidget::showTestSystemGraphic);
  this->toolBar()->addAction(testSystemGraphAction);

  return;
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
  // TODO: parent is 0, how to delete editorWidget??????
  // here we have a hack

  TestSystemEditorWidget* editorWidget = new TestSystemEditorWidget(parent);
  editorWidget->duplicateFrom(this->editorWidget());
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
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

void TestSystemEditor::setTestSystemItem(model::ts::TestSystemItem const* testSystemItem)
{
  this->_d->_testSystemItem=testSystemItem;

  return;
}

model::ts::TestSystemItem const* TestSystemEditor::testSystemItem() const
{
  return this->_d->_testSystemItem;
}
