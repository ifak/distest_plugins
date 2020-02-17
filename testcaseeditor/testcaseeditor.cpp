#include "testcaseeditor.hpp"
#include "testcaseeditorwidget.hpp"
#include "testcaseeditorconstants.hpp"
#include "testcaseeditorplugin.hpp"

#include <coreplugin/coreconstants.h>
#include <texteditor/texteditorsettings.h>

#include <mobata/utils/functors.hpp>

#include <QDir>
#include <QTemporaryFile>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace testcaseeditor;
using namespace model::ts;

class TestCaseEditor::Private
{
  friend class TestCaseEditor;
};

TestCaseEditor::TestCaseEditor(TestCaseEditorWidget* testCaseEditorWidget)
  : TextEditor::BaseTextEditor(testCaseEditorWidget),
    _d(new Private)
{
  this->m_context.add(Constants::TESTCASEEDITOR_CONTEXT);
  this->m_context.add(Constants::LANG_TESTCASE);
  this->m_context.add(TextEditor::Constants::C_TEXTEDITOR);

  //graphic action///
  QAction* testcaseGraphAction=new QAction(QIcon(QLatin1String(":/mobata/images/ts/testcase.png")),
                                         tr("update/create testcase graphic..."),
                                         this);
  testcaseGraphAction->setStatusTip(tr("testcase graphic"));
  connect(testcaseGraphAction,
          &QAction::triggered,
          testCaseEditorWidget,
          &TestCaseEditorWidget::showTestCaseGraphic);
  this->toolBar()->addAction(testcaseGraphAction);
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
  TestCaseEditorWidget* testCaseEditorWidget = new TestCaseEditorWidget(parent);
  testCaseEditorWidget->duplicateFrom(this->editorWidget());
  TestCaseEditorPlugin::instance()->initializeEditor(testCaseEditorWidget);;

  return testCaseEditorWidget->editor();
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

TestCaseOutlineModel* TestCaseEditor::testCaseOutlineModel()
{
  return this->document()?this->document()->testCaseOutlineModel():0;
}
