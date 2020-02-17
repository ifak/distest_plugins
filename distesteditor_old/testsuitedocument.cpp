#include "testsuitedocument.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

TestSuiteDocument::TestSuiteDocument(QObject *parent)
    : TextEditor::BaseTextDocument(parent)
{}

TestSuiteDocument::~TestSuiteDocument()
{}
