#include "testcaseeditor.hpp"

#include "testcaseeditorwidget.hpp"
#include "distesteditorconstants.hpp"

#include <texteditor/texteditorsettings.h>
#include <texteditor/basetexteditor.h>

#include <mobata/utils/functors.hpp>

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

class TestCaseEditor::Private
{
  friend class TestCaseEditor;

  Private()
    : _testCaseItem(0)
  {}

public:
  ~Private()
  {}

private:
  model::ts::TestCaseItem const*  _testCaseItem;
};

TestCaseEditor::TestCaseEditor(TestCaseEditorWidget* testCaseTextEditorWidget)
  : TextEditor::BaseTextEditor(testCaseTextEditorWidget),
    _d(new Private())
{
  this->createActions();
}

TestCaseEditor::~TestCaseEditor()
{
  delete this->_d;
}

Core::Id TestCaseEditor::testCaseEditorId()
{
  return Core::Id(Constants::TESTCASEEDITOR_ID);
}

bool TestCaseEditor::duplicateSupported() const
{
  return true;
}

Core::IEditor* TestCaseEditor::duplicate(QWidget *parent)
{
  TestCaseEditorWidget* editorWidget = new TestCaseEditorWidget(parent);
  editorWidget->duplicateFrom(this->editorWidget());
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

bool TestCaseEditor::isTemporary() const
{
  return false;
}

Core::Id TestCaseEditor::id() const
{
  return TestCaseEditor::testCaseEditorId();
}

TestCaseDocument* TestCaseEditor::document()
{
  return qobject_cast<TestCaseDocument*>(TextEditor::BaseTextEditor::document());
}

void TestCaseEditor::createActions()
{
  TextEditor::BaseTextEditorWidget* textEditorWidget=this->editorWidget();
  TestCaseEditorWidget* baseTestCaseTextEditorWidget=
      utils::simple_cast<TestCaseEditorWidget*>(textEditorWidget);
  Q_ASSERT(baseTestCaseTextEditorWidget);

  QAction* testCaseGraphAction=new QAction(QIcon(QLatin1String(":/mobata/images/ts/testcase.png")),
                                           tr("update/create test case graphic..."),
                                           this);
  testCaseGraphAction->setStatusTip(tr("test case graphic"));
  connect(testCaseGraphAction,
          &QAction::triggered,
          baseTestCaseTextEditorWidget,
          &TestCaseEditorWidget::showTestCaseGraphic);
  this->toolBar()->addAction(testCaseGraphAction);

  return;
}

void TestCaseEditor::setTestCaseItem(model::ts::TestCaseItem const* testCaseItem)
{
  this->_d->_testCaseItem=testCaseItem;

  return;
}

model::ts::TestCaseItem const* TestCaseEditor::testCaseItem() const
{
  return this->_d->_testCaseItem;
}
