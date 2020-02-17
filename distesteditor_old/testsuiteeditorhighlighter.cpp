#include "testsuiteeditorhighlighter.hpp"

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{

TestSuiteEditorHighlighter::TestSuiteEditorHighlighter(QTextDocument* parent)
  : DisTestDslHighlighter(parent)
{}

TestSuiteEditorHighlighter::~TestSuiteEditorHighlighter()
{}

} // namespace distesteditor
