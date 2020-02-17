#include "suteditorhighlighter.hpp"

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{

SutEditorHighlighter::SutEditorHighlighter(QTextDocument* parent)
  : DisTestDslHighlighter(parent)
{}

SutEditorHighlighter::~SutEditorHighlighter()
{}

} // namespace distesteditor
