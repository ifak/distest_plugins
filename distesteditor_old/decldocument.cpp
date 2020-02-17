#include "decldocument.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

DeclDocument::DeclDocument(QObject *parent)
  : TextEditor::BaseTextDocument(parent)
{}

DeclDocument::~DeclDocument()
{}
