#include "testsuiteeditor.hpp"

#include "testsuiteeditorwidget.hpp"
#include "distesteditorconstants.hpp"

#include <texteditor/texteditorsettings.h>

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

class TestSuiteEditor::Private
{
  friend class TestSuiteEditor;

  Private()
    : _testSuite(0)
  {}

public:
  ~Private()
  {}

private:
  model::ts::TestSuite const*   _testSuite;
};

TestSuiteEditor::TestSuiteEditor(TestSuiteEditorWidget* testSuiteTextEditorWidget)
  : TextEditor::BaseTextEditor(testSuiteTextEditorWidget),
    _d(new Private())
{}

TestSuiteEditor::~TestSuiteEditor()
{}

Core::Id TestSuiteEditor::testSuiteEditorId()
{
  return Core::Id(Constants::TESTCASEEDITOR_ID);
}

bool TestSuiteEditor::duplicateSupported() const
{
  return true;
}

Core::IEditor* TestSuiteEditor::duplicate(QWidget *parent)
{
  qDebug()<<"TestSuiteEditor::duplicate() with parent:"<<parent<<" executed";

  // TODO: parent is 0, how to delete editorWidget??????
  // here we have a hack

  TestSuiteEditorWidget* editorWidget = new TestSuiteEditorWidget(parent);
  editorWidget->duplicateFrom(this->editorWidget());
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

bool TestSuiteEditor::isTemporary() const
{
  return false;
}

Core::Id TestSuiteEditor::id() const
{
  return TestSuiteEditor::testSuiteEditorId();
}

TestSuiteDocument* TestSuiteEditor::document()
{
  return qobject_cast<TestSuiteDocument*>(TextEditor::BaseTextEditor::document());
}

void TestSuiteEditor::setTestSuite(model::ts::TestSuite const* testSuite)
{
  this->_d->_testSuite=testSuite;

  return;
}

model::ts::TestSuite const* TestSuiteEditor::testSuite() const
{
  return this->_d->_testSuite;
}
