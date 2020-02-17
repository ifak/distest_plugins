#include "testsystemdocument.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

TestSystemDocument::TestSystemDocument(QObject *parent)
    : TextEditor::BaseTextDocument(parent)
{}

TestSystemDocument::~TestSystemDocument()
{}
