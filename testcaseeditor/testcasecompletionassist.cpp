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

#include "testcasecompletionassist.hpp"
#include "testcaseeditorconstants.hpp"

#include <coreplugin/idocument.h>
#include <texteditor/completionsettings.h>
#include <texteditor/codeassist/basicproposalitem.h>
#include <texteditor/codeassist/basicproposalitemlistmodel.h>
#include <texteditor/codeassist/genericproposal.h>
#include <texteditor/codeassist/functionhintproposal.h>
#include <utils/faketooltip.h>

#include <mobata/model/base/signalitem.hpp>

#include <dslparser/testcase/comcreatetestcaseproposals.hpp>

#include <QIcon>
#include <QPainter>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QDir>

using namespace testcaseeditor;
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
// TestCaseCompletionAssistProvider
// ----------------------------
bool TestCaseCompletionAssistProvider::supportsEditor(const Core::Id& editorId) const
{
    return editorId == Constants::TESTCASEEDITOR_ID;
}

IAssistProcessor* TestCaseCompletionAssistProvider::createProcessor() const
{
    return new TestCaseCompletionAssistProcessor;
}

int TestCaseCompletionAssistProvider::activationCharSequenceLength() const
{
    return 1;
}

bool TestCaseCompletionAssistProvider::isActivationCharSequence(const QString& sequence) const
{
    return (false ? sequence.isEmpty() : isActivationChar(sequence.at(0)));
}

// -----------------------------
// TestCaseCompletionAssistProcessor
// -----------------------------
TestCaseCompletionAssistProcessor::TestCaseCompletionAssistProcessor()
    : _startPosition(0)
    , _keywordIcon(QLatin1String(":/mobata/images/base/type.png"))
    , _signalIcon(QLatin1String(":/mobata/images/base/signal.png"))
    , _typeIcon(QLatin1String(":/mobata/images/base/type.png"))
    , _functionIcon(QLatin1String(":/mobata/images/base/action.png"))
    , _attributeIcon(QLatin1String(":/mobata/images/base/attribute.png"))
    , _portIcon(QLatin1String(":/mobata/images/base/port.png"))
    , _otherIcon(QLatin1String(":/mobata/images/new.png"))
{}

TestCaseCompletionAssistProcessor::~TestCaseCompletionAssistProcessor()
{}

QIcon TestCaseCompletionAssistProcessor::proposalIcon(const int proposalType)
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

IAssistProposal* TestCaseCompletionAssistProcessor::perform(const IAssistInterface* interface)
{
    this->_interface.reset(static_cast<const TestCaseCompletionAssistInterface *>(interface));

    if (interface->reason() == IdleEditor && !acceptsIdleEditor())
        return 0;

    int pos = this->_interface->position() - 1;
    this->_startPosition=pos + 1;
    QString testCaseText = this->_interface->textAt(0, this->_startPosition);

    bool result = this->createTestCaseProposals(testCaseText);
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
        testCaseText = this->_interface->textAt(0, this->_startPosition);
        this->createTestCaseProposals(testCaseText);
    }

    return createContentProposal();
}

bool TestCaseCompletionAssistProcessor::createTestCaseProposals(const QString& testCaseText)
{
    using namespace dslparser::testcase;
    QString praefix = this->_interface->fileName();
    ComCreateTestCaseProposals proposalsCommand(testCaseText,QFileInfo(praefix).absolutePath()+QStringLiteral("/"));
    QString errorString;
    bool result = proposalsCommand.execute(&errorString);
    if(!result)
        qDebug()<<"error during proposals creation: "<<errorString;

    if(proposalsCommand.testCaseProposals().size() == 0)
        return false;

    for(const dslparser::DslProposal& testCaseProposal : proposalsCommand.testCaseProposals())
        this->addCompletion(testCaseProposal.proposalText,
                            this->proposalIcon(testCaseProposal.proposalType));

    return true;
}

IAssistProposal* TestCaseCompletionAssistProcessor::createContentProposal() const
{
    IGenericProposalModel *model = new BasicProposalItemListModel(_completions);
    IAssistProposal *proposal = new GenericProposal(_startPosition, model);
    return proposal;
}

bool TestCaseCompletionAssistProcessor::acceptsIdleEditor() const
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

void TestCaseCompletionAssistProcessor::addCompletion(const QString &text,
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
// TestCaseCompletionAssistInterface
// -----------------------------
TestCaseCompletionAssistInterface::TestCaseCompletionAssistInterface(QTextDocument *textDocument,
                                                                     int position,
                                                                     const QString &fileName,
                                                                     TextEditor::AssistReason reason)
    : DefaultAssistInterface(textDocument, position, fileName, reason)
{}
