/*
 *  This file is part of Test Case Editor Plugin for AppCreator based application.
 *
 *  Copyright (C) 2013 Jan Krause <jan.krause.no19@gmail.com>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
*/

#pragma once

#include "testcaseeditor.hpp"

#include <texteditor/codeassist/completionassistprovider.h>
#include <texteditor/codeassist/iassistprocessor.h>
#include <texteditor/codeassist/defaultassistinterface.h>
#include <texteditor/codeassist/ifunctionhintproposalmodel.h>

#include <QScopedPointer>
#include <QIcon>

namespace TextEditor {
class BasicProposalItem;
}

namespace testcaseeditor {

class TestCaseCompletionAssistInterface;

class TestCaseCompletionAssistProvider : public TextEditor::CompletionAssistProvider
{
public:
  virtual bool supportsEditor(const Core::Id &editorId) const;
  virtual TextEditor::IAssistProcessor *createProcessor() const;

  virtual int activationCharSequenceLength() const;
  virtual bool isActivationCharSequence(const QString& sequence) const;
};

class TestCaseCompletionAssistProcessor : public TextEditor::IAssistProcessor
{
public:
  TestCaseCompletionAssistProcessor();
  virtual ~TestCaseCompletionAssistProcessor();

  virtual TextEditor::IAssistProposal *perform(const TextEditor::IAssistInterface *interface);

private:
  bool createTestCaseProposals(const QString& testCaseText);
  TextEditor::IAssistProposal* createContentProposal() const;
  bool acceptsIdleEditor() const;
  void addCompletion(const QString &text, const QIcon &icon, int order = 0);
  QIcon proposalIcon(const int proposalType);

private:
  int                                                 _startPosition;
  QScopedPointer<const TestCaseCompletionAssistInterface>  _interface;
  QList<TextEditor::BasicProposalItem *>              _completions;

  QIcon _keywordIcon;
  QIcon _signalIcon;
  QIcon _typeIcon;
  QIcon _functionIcon;
  QIcon _attributeIcon;
  QIcon _portIcon;
  QIcon _otherIcon;
};

class TestCaseCompletionAssistInterface : public TextEditor::DefaultAssistInterface
{
public:
  TestCaseCompletionAssistInterface(QTextDocument *textDocument,
                                    int position,
                                    const QString &fileName,
                                    TextEditor::AssistReason reason);
};

} // testcaseeditor
