#include "testsystemeditorhighlighter.hpp"

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor {

TestSystemEditorHighlighter::TestSystemEditorHighlighter(QTextDocument *parent)
  : DisTestDslHighlighter(parent)
{}

TestSystemEditorHighlighter::~TestSystemEditorHighlighter()
{}

} // namespace distesteditor

