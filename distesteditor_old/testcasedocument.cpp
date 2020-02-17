#include "testcasedocument.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

TestCaseDocument::TestCaseDocument(QObject *parent)
    : TextEditor::BaseTextDocument(parent)
{}

TestCaseDocument::~TestCaseDocument()
{}
