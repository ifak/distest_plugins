/*
 *  This file is part of Diagnosis Editor Plugin for AppCreator based application.
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

#include "diagnosiseditor.hpp"

#include <texteditor/codeassist/completionassistprovider.h>
#include <texteditor/codeassist/iassistprocessor.h>
#include <texteditor/codeassist/defaultassistinterface.h>
#include <texteditor/codeassist/ifunctionhintproposalmodel.h>

#include <QScopedPointer>
#include <QIcon>

namespace TextEditor {
class BasicProposalItem;
}

namespace diagnosiseditor {

class DiagnosisCompletionAssistInterface;

class DiagnosisCompletionAssistProvider : public TextEditor::CompletionAssistProvider
{
public:
  virtual bool supportsEditor(const Core::Id &editorId) const;
  virtual TextEditor::IAssistProcessor *createProcessor() const;

  virtual int activationCharSequenceLength() const;
  virtual bool isActivationCharSequence(const QString& sequence) const;
};

class DiagnosisCompletionAssistProcessor : public TextEditor::IAssistProcessor
{
public:
  DiagnosisCompletionAssistProcessor();
  virtual ~DiagnosisCompletionAssistProcessor();

  virtual TextEditor::IAssistProposal *perform(const TextEditor::IAssistInterface *interface);

private:
  bool createDiagnosisProposals(const QString& diagnosisText);
  TextEditor::IAssistProposal* createContentProposal() const;
  bool acceptsIdleEditor() const;
  void addCompletion(const QString &text, const QIcon &icon, int order = 0);
  QIcon proposalIcon(const int proposalType);

private:
  int                                                 _startPosition;
  QScopedPointer<const DiagnosisCompletionAssistInterface>  _interface;
  QList<TextEditor::BasicProposalItem *>              _completions;

  QIcon _keywordIcon;
  QIcon _signalIcon;
  QIcon _typeIcon;
  QIcon _functionIcon;
  QIcon _attributeIcon;
  QIcon _portIcon;
  QIcon _otherIcon;
};

class DiagnosisCompletionAssistInterface : public TextEditor::DefaultAssistInterface
{
public:
  DiagnosisCompletionAssistInterface(QTextDocument *textDocument,
                                    int position,
                                    const QString &fileName,
                                    TextEditor::AssistReason reason);
};

} // diagnosiseditor
