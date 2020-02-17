#include "testcaseeditorhighlighter.hpp"

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{

TestCaseEditorHighlighter::TestCaseEditorHighlighter(QTextDocument* parent)
  : DisTestDslHighlighter(parent)
{}

TestCaseEditorHighlighter::~TestCaseEditorHighlighter()
{}

} // namespace distesteditor
