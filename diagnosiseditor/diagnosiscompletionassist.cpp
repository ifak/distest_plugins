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

#include "diagnosiscompletionassist.hpp"
#include "diagnosiseditorconstants.hpp"

#include <coreplugin/idocument.h>
#include <texteditor/completionsettings.h>
#include <texteditor/codeassist/basicproposalitem.h>
#include <texteditor/codeassist/basicproposalitemlistmodel.h>
#include <texteditor/codeassist/genericproposal.h>
#include <texteditor/codeassist/functionhintproposal.h>
#include <utils/faketooltip.h>

#include <mobata/model/base/signalitem.hpp>

#include <dslparser/diagnosis/comcreatediagnosisproposals.hpp>

#include <QIcon>
#include <QPainter>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QDir>

using namespace diagnosiseditor;
using namespace TextEditor;

namespace {

enum CompletionOrder {
    SpecialMemberOrder = -5
};


bool isActivationChar(const QChar &ch)
{
    return ch == QLatin1Char('(') || ch == QLatin1Char('.') || ch == QLatin1Char(',');
}

bool isIdentifierChar(QChar ch)
{
    return ch.isLetterOrNumber() || ch == QLatin1Char('_');
}

bool isDelimiter(QChar ch)
{
    switch (ch.unicode()) {
    case '{':
    case '}':
    case '[':
    case ']':
    case ')':
    case '?':
    case '!':
    case ':':
    case ';':
    case ',':
    case '+':
    case '-':
    case '*':
    case '/':
        return true;

    default:
        return false;
    }
}

bool checkStartOfIdentifier(const QString &word)
{
    if (! word.isEmpty()) {
        const QChar ch = word.at(0);
        if (ch.isLetter() || ch == QLatin1Char('_'))
            return true;
    }

    return false;
}

} // Anonymous

// ----------------------------
// DiagnosisCompletionAssistProvider
// ----------------------------
bool DiagnosisCompletionAssistProvider::supportsEditor(const Core::Id& editorId) const
{
    return editorId == Constants::DIAGNOSISEDITOR_ID;
}

IAssistProcessor* DiagnosisCompletionAssistProvider::createProcessor() const
{
    return new DiagnosisCompletionAssistProcessor;
}

int DiagnosisCompletionAssistProvider::activationCharSequenceLength() const
{
    return 1;
}

bool DiagnosisCompletionAssistProvider::isActivationCharSequence(const QString& sequence) const
{
    return (false ? sequence.isEmpty() : isActivationChar(sequence.at(0)));
}

// -----------------------------
// DiagnosisCompletionAssistProcessor
// -----------------------------
DiagnosisCompletionAssistProcessor::DiagnosisCompletionAssistProcessor()
    : _startPosition(0)
    , _keywordIcon(QLatin1String(":/mobata/images/base/type.png"))
    , _signalIcon(QLatin1String(":/mobata/images/base/signal.png"))
    , _typeIcon(QLatin1String(":/mobata/images/base/type.png"))
    , _functionIcon(QLatin1String(":/mobata/images/base/action.png"))
    , _attributeIcon(QLatin1String(":/mobata/images/base/attribute.png"))
    , _portIcon(QLatin1String(":/mobata/images/base/port.png"))
    , _otherIcon(QLatin1String(":/mobata/images/new.png"))
{}

DiagnosisCompletionAssistProcessor::~DiagnosisCompletionAssistProcessor()
{}

QIcon DiagnosisCompletionAssistProcessor::proposalIcon(const int proposalType)
{
    if(proposalType == dslparser::Keyword)
        return this->_keywordIcon;
    else if(proposalType == dslparser::Signal)
        return this->_signalIcon;
    else if(proposalType == dslparser::Attribute)
        return this->_attributeIcon;
//    else if(proposalType == dslparser::Function)
//        return this->_functionIcon;
    else if(proposalType == dslparser::Port)
        return this->_portIcon;
    else if(proposalType == dslparser::Type)
        return this->_typeIcon;

    return this->_otherIcon;
}

IAssistProposal* DiagnosisCompletionAssistProcessor::perform(const IAssistInterface* interface)
{
    this->_interface.reset(static_cast<const DiagnosisCompletionAssistInterface *>(interface));

    if (interface->reason() == IdleEditor && !acceptsIdleEditor())
        return 0;

    int pos = this->_interface->position() - 1;
    this->_startPosition=pos + 1;
    QString diagnosisText = this->_interface->textAt(0, this->_startPosition);

    bool result = this->createDiagnosisProposals(diagnosisText);
    if(!result)//next (and last) try
    {
        QString currText(QStringLiteral(""));
        QChar ch = this->_interface->characterAt(pos);
        while (ch.isLetterOrNumber() || ch == QLatin1Char('_'))
        {
            currText.insert(0,ch);
            ch = this->_interface->characterAt(--pos);
        }
        qDebug()<<"currText: "<<currText;

        this->_startPosition=pos + 1;
        diagnosisText = this->_interface->textAt(0, this->_startPosition);
        this->createDiagnosisProposals(diagnosisText);
    }

    return createContentProposal();
}

bool DiagnosisCompletionAssistProcessor::createDiagnosisProposals(const QString& diagnosisText)
{
    using namespace dslparser::diagnosis;
    QString praefix = this->_interface->fileName();
    ComCreateDiagnosisProposals proposalsCommand(diagnosisText,QFileInfo(praefix).absolutePath()+QStringLiteral("/"));
    QString errorString;
    bool result = proposalsCommand.execute(&errorString);
    if(!result)
        qDebug()<<"error during proposals creation: "<<errorString;

    if(proposalsCommand.diagnosisProposals().size() == 0)
        return false;

    for(const DiagnosisProposal& diagnosisProposal : proposalsCommand.diagnosisProposals())
        this->addCompletion(diagnosisProposal.proposalText,
                            this->proposalIcon(diagnosisProposal.proposalType));

    return true;
}

IAssistProposal* DiagnosisCompletionAssistProcessor::createContentProposal() const
{
    IGenericProposalModel *model = new BasicProposalItemListModel(_completions);
    IAssistProposal *proposal = new GenericProposal(_startPosition, model);
    return proposal;
}

bool DiagnosisCompletionAssistProcessor::acceptsIdleEditor() const
{
    const int cursorPosition = this->_interface->position();
    const QChar ch = this->_interface->characterAt(cursorPosition - 1);

    const QChar characterUnderCursor = this->_interface->characterAt(cursorPosition);

    if (isIdentifierChar(ch) && (characterUnderCursor.isSpace() ||
                                 characterUnderCursor.isNull() ||
                                 isDelimiter(characterUnderCursor)))
    {
        int pos = _interface->position() - 1;
        for (; pos != -1; --pos) {
            if (! isIdentifierChar(this->_interface->characterAt(pos)))
                break;
        }
        ++pos;

        const QString word = _interface->textAt(pos, cursorPosition - pos);
        if (word.length() > 2 && checkStartOfIdentifier(word))
        {
            for (int i = 0; i < word.length(); ++i)
            {
                if (! isIdentifierChar(word.at(i)))
                    return false;
            }
            return true;
        }
    }

    return isActivationChar(ch);
}

void DiagnosisCompletionAssistProcessor::addCompletion(const QString &text,
                                                      const QIcon &icon,
                                                      int order)
{
    BasicProposalItem* item = new BasicProposalItem;
    item->setText(text);
    item->setIcon(icon);
    item->setOrder(order);
    _completions.append(item);
}

// -----------------------------
// DiagnosisCompletionAssistInterface
// -----------------------------
DiagnosisCompletionAssistInterface::DiagnosisCompletionAssistInterface(QTextDocument *textDocument,
                                                                     int position,
                                                                     const QString &fileName,
                                                                     TextEditor::AssistReason reason)
    : DefaultAssistInterface(textDocument, position, fileName, reason)
{}
