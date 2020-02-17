#include "sutdocument.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace distesteditor;

SutDocument::SutDocument(QObject *parent)
    : TextEditor::BaseTextDocument(parent)
{}

SutDocument::~SutDocument()
{}
