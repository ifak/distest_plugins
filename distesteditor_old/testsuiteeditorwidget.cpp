#include "testsuiteeditorwidget.hpp"

#include "testsuitedocument.hpp"
#include "distestdslautocompleter.hpp"
#include "distestdslindenter.hpp"
#include "testsuiteeditorhighlighter.hpp"

#include <texteditor/fontsettings.h>

#include <QTextCodec>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{

class TestSuiteEditorWidget::Private
{
  friend class TestSuiteEditorWidget;

  Private()
    : _testSuiteEditor(0)
  {}

public:
  ~Private()
  {}

private:
  TestSuiteEditor* _testSuiteEditor;
};

TestSuiteEditorWidget::TestSuiteEditorWidget(QWidget *parent)
  : dsleditor::DslEditorWidget(parent), _d(new Private())
{
  this->setBaseTextDocument(QSharedPointer<TestSuiteDocument>(new TestSuiteDocument()));
  this->_d->_testSuiteEditor=new TestSuiteEditor(this);

  this->baseTextDocument()->setSyntaxHighlighter(new TestSuiteEditorHighlighter(this->document()));
  this->setIndenter(new DisTestDslIndenter());
  this->setAutoCompleter(new DisTestDslAutoCompleter());
}

TestSuiteEditorWidget::~TestSuiteEditorWidget()
{}

TestSuiteEditor *TestSuiteEditorWidget::createEditor()
{
  return this->_d->_testSuiteEditor;
}

void TestSuiteEditorWidget::setFontSettings(const TextEditor::FontSettings &fs)
{
  return dsleditor::DslEditorWidget::setFontSettings(fs);
}

} //end namespace distesteditor
