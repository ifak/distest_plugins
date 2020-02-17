/*
 *  This file is part of Test System Editor Plugin for AppCreator based application.
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

#include "testsystemeditorwidget.hpp"

#include "testsystemdocument.hpp"
#include "testsystemcompletionassist.hpp"
#include "testsystemoutlinemodel.hpp"
#include "combuildtestsystemoutlinemodel.hpp"
#include "testsystemeditorconstants.hpp"

#include <dsleditor/dslhighlighter.hpp>
#include <dsleditor/dslindenter.hpp>
#include <dsleditor/dslautocompleter.hpp>

#include <coreplugin/messagemanager.h>
#include <texteditor/fontsettings.h>
#include <utils/qtcassert.h>
#include <utils/uncommentselection.h>

#include <QFileInfo>
#include <QDir>
#include <QTemporaryFile>
#include <QTextCodec>
#include <QTextBlock>
#include <QTimer>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace TextEditor;

namespace testsystemeditor{

enum {
  UPDATE_DOCUMENT_DEFAULT_INTERVAL = 150
};

class TestSystemEditorWidget::Private
{
  friend class TestSystemEditorWidget;

  Private()
    : _testsystemEditor(0),
      _testsystemDocument(new TestSystemDocument)
  {}

public:
  ~Private()
  {}

private:
  TestSystemEditor*        _testsystemEditor;
  TestSystemDocument::Ptr  _testsystemDocument;
  QTimer*           _updateOutlineTimer;
};

TestSystemEditorWidget::TestSystemEditorWidget(QWidget *parent)
  : DslEditorWidget(parent),
    _d(new Private())
{
  this->_d->_testsystemEditor=new TestSystemEditor(this);
  this->setBaseTextDocument(this->_d->_testsystemDocument);

  this->baseTextDocument()->setSyntaxHighlighter(new dsleditor::DslHighlighter(this->document()));
  this->setIndenter(new dsleditor::DslIndenter());
  this->setAutoCompleter(new dsleditor::DslAutoCompleter());

  this->_d->_updateOutlineTimer = new QTimer(this);
  this->_d->_updateOutlineTimer->setInterval(UPDATE_DOCUMENT_DEFAULT_INTERVAL);
  this->_d->_updateOutlineTimer->setSingleShot(true);
  connect(this->_d->_updateOutlineTimer, &QTimer::timeout,
          this, &TestSystemEditorWidget::updateOutlineNow);
  connect(this, &TestSystemEditorWidget::textChanged,
          this, &TestSystemEditorWidget::updateOutline);
  connect(this, &TestSystemEditorWidget::cursorPositionChanged,
          this, &TestSystemEditorWidget::updateOutlineIndexNow);

  //  TestSystemRenderManager *renderManager = TestSystemRenderManager::instance();
  //  connect(renderManager, SIGNAL(requestForApplyingNewGlobalTestSystemRenderSettings(QString)),
  //          this, SLOT(globalTestSystemRenderSettingsChangedSignalHandlder(QString)));
  //  connect(renderManager, SIGNAL(requestForApplyingNewCustomTestSystemRenderSettings(QString)),
  //          this, SLOT(customTestSystemRenderSettingsChangedSignalHandlder(QString)));
}

TestSystemEditorWidget::~TestSystemEditorWidget()
{
  delete this->_d;
}

TestSystemEditor* TestSystemEditorWidget::createEditor()
{
  return this->_d->_testsystemEditor;
}

void TestSystemEditorWidget::setFontSettings(const TextEditor::FontSettings &fs)
{
  return DslEditorWidget::setFontSettings(fs);
}

QVector<TextEditor::TextStyle> TestSystemEditorWidget::highlighterFormatCategories()
{
  QVector<TextEditor::TextStyle> categories = DslEditorWidget::highlighterFormatCategories();
  categories << TextEditor::C_FUNCTION;

  return categories;
}

QString TestSystemEditorWidget::wordUnderCursor() const
{
  QTextCursor tc = textCursor();
  const QChar ch = document()->characterAt(tc.position() - 1);
  // make sure that we're not at the start of the next word.
  if (ch.isLetterOrNumber() || ch == QLatin1Char('_'))
    tc.movePosition(QTextCursor::Left);
  tc.movePosition(QTextCursor::StartOfWord);
  tc.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
  const QString word = tc.selectedText();

  return word;
}

const TestSystemDocument::Ptr& TestSystemEditorWidget::testsystemDocument() const
{
  return this->_d->_testsystemDocument;
}

void TestSystemEditorWidget::unCommentSelection()
{
  return Utils::unCommentSelection(this);
}

void TestSystemEditorWidget::updateOutline()
{
  this->_d->_updateOutlineTimer->start();
}

QModelIndex TestSystemEditorWidget::outlineModelIndex()
{
  QModelIndex currentModelIndex = this->indexForPosition(this->position());
  if(currentModelIndex.isValid())
    emit outlineModelIndexChanged(currentModelIndex);

  return currentModelIndex;
}

QTextCharFormat textCharFormat(int tokenType,
                               dsleditor::DslHighlighter* testSystemHighlighter)
{
  Q_ASSERT(testSystemHighlighter);

  if(tokenType == dslparser::TestComponent)
    return testSystemHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::TestSystem)
    return testSystemHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Import)
    return testSystemHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Attribute)
    return testSystemHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Signal)
    return testSystemHighlighter->textCharFormat(TextEditor::C_KEYWORD);
//  else if(tokenType == dslparser::Function)
//    return testSystemHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::Port)
    return testSystemHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::Type)
    return testSystemHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Keyword)
    return testSystemHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::UnknownTestSystemTokenType)
    return testSystemHighlighter->textCharFormat(TextEditor::C_TEXT);

  return testSystemHighlighter->textCharFormat(TextEditor::C_TEXT);
}

void TestSystemEditorWidget::updateOutlineNow()
{
  using namespace dsleditor;

  this->_d->_updateOutlineTimer->stop();

  TestSystemOutlineModel* testSystemOutlineModel = this->_d->_testsystemDocument->testSystemOutlineModel();
  Q_ASSERT(testSystemOutlineModel);

  QString currText=this->toPlainText();
  QString praefix = this->_d->_testsystemDocument->fileName();
  if(praefix.size()){
      int i = praefix.size()-1;
      QChar test = praefix.at(i);
      i--;
      while(i>=0 && test != QStringLiteral("/"))
          test = praefix.at(--i);
      praefix.chop(praefix.size()-i-1);
  }
  QString homePath = QDir().absolutePath();
  while(homePath.size() && praefix.size() && homePath.at(0) == praefix.at(0)){
      homePath.remove(0,1);
      praefix.remove(0,1);
  }
  int i = 0;
  foreach (QChar c, homePath) {
      if(c == QStringLiteral("/")) i++;
  }
  if(homePath.at(homePath.size()-1) != QStringLiteral("/")) i++;
  for(;i>0;i--){
      praefix = QStringLiteral("../") + praefix;
  }
  ComBuildTestSystemOutlineModel buildOutlineCommand(currText, testSystemOutlineModel,praefix);
  buildOutlineCommand.execute();

  //TODO: just a try, maybe we need 'updateOutlineIndexNow()'
  this->outlineModelIndex();

  /// first semantic highlights//////
  DslHighlighter* testsystemHighlighter = qobject_cast<DslHighlighter*>(this->baseTextDocument()->syntaxHighlighter());
  Q_ASSERT(testsystemHighlighter);

  QList<QTextEdit::ExtraSelection> extraSelections;
  for(const dslparser::TokenTextLocation& textLoc : testSystemOutlineModel->keywordTextSelections())
  {
    if(!textLoc.isValid())
      continue;

    QTextCursor cursor(this->baseTextDocument()->document());
    cursor.setPosition(textLoc.start());
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    QTextCharFormat textFormat = textCharFormat(textLoc.tokenType(), testsystemHighlighter);
    if(!textFormat.isValid())
      continue;

    QTextEdit::ExtraSelection sel;
    sel.cursor = cursor;
    sel.format = textFormat;
    extraSelections.append(sel);
  }
  this->setExtraSelections(OtherSelection, extraSelections);

  ///now warnings and/or errors
  extraSelections.clear();

  QTextCharFormat errorFormat;
  errorFormat.setBackground(Qt::NoBrush);
  errorFormat.setUnderlineStyle(QTextCharFormat::WaveUnderline);
  errorFormat.setUnderlineColor(Qt::red);

  QSet<int> errors;
  for (const dslparser::DslError& testsystemError : buildOutlineCommand.errors())
  {
    if (! testsystemError.line())
      continue;
    else if (errors.contains(int(testsystemError.line())))
      continue;

    errors.insert(int(testsystemError.line()));

    QTextBlock block=document()->findBlockByLineNumber(int(testsystemError.line())-1);
    QTextCursor cursor(block);
    cursor.setPosition(block.position()+testsystemError.charPositionInLine());
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    QTextEdit::ExtraSelection sel;
    sel.cursor = cursor;
    sel.format = errorFormat;
    sel.format.setToolTip(testsystemError.message());
    extraSelections.append(sel);
  }
  this->setExtraSelections(CodeWarningsSelection, extraSelections);

  return;
}

void TestSystemEditorWidget::updateOutlineIndexNow()
{
  if (this->_d->_updateOutlineTimer->isActive())
    return; // updateOutlineNow will call this function soon anyway

  this->outlineModelIndex();

  return;
}

QModelIndex TestSystemEditorWidget::indexForPosition(unsigned cursorPosition) const
{
  using namespace dslparser;

  TestSystemOutlineModel const* testsystemOutlineModel = this->_d->_testsystemEditor->testSystemOutlineModel();
  Q_ASSERT(testsystemOutlineModel);

  const ModelTextLocations& modelTextLocations = testsystemOutlineModel->modelTextSelections();
  ModelTextLocations::ConstIterator mt_it = modelTextLocations.begin();
  for( ; mt_it != modelTextLocations.end(); ++mt_it)
  {
    const QModelIndex& currModelIndex = mt_it.key();
    const TokenTextLocation& currTokLocation = mt_it.value();

    if(!currTokLocation.isValid())
      continue;

    if(cursorPosition >= unsigned(currTokLocation.start()))
    {
      if(cursorPosition <= (unsigned(currTokLocation.start())
                            + unsigned(currTokLocation.length())))
      {
        return currModelIndex;
      }
    }
  }

  return QModelIndex();
}

IAssistInterface* TestSystemEditorWidget::createAssistInterface(AssistKind assistKind,
                                                            AssistReason assistReason) const
{
  if (assistKind == TextEditor::Completion)
    return new TestSystemCompletionAssistInterface(this->document(),
                                               this->position(),
                                               editor()->document()->fileName(),
                                               assistReason/*,
                                                                                                                                                                                                                                                                                                                                                                                                       mimeType(),
                                                                                                                                                                                                                                                                                                                                                                                                       this->testsystemDocument()*/);
  return BaseTextEditorWidget::createAssistInterface(assistKind, assistReason);
}

//void TestSystemEditorWidget::showTestSystemGraphic()
//{
//  QString tempTestSystemGraphicFile = QDir::tempPath();
//  if (!tempTestSystemGraphicFile.endsWith(QLatin1Char('/')))
//    tempTestSystemGraphicFile += QLatin1Char('/');
//  tempTestSystemGraphicFile += QFileInfo(this->editorDocument()->fileName()).baseName()
//                           + QLatin1String(".testsystemgraphic");

//  if(this->_d->_testsystemGraphicFile.exists())
//  {
//    this->_d->_testsystemGraphicFile.close();
//    this->_d->_testsystemGraphicFile.rename(tempTestSystemGraphicFile);
//  }
//  else
//    this->_d->_testsystemGraphicFile.setFileName(tempTestSystemGraphicFile);

//  QTC_ASSERT(this->_d->_testsystemGraphicFile.open(QIODevice::ReadWrite), return;);
//  this->_d->_testsystemGraphicFile.close();

//  qDebug()<<"temp-testsystem-graphic-file: "<<this->_d->_testsystemGraphicFile.fileName();

//  Core::IEditor* editor=Core::EditorManager::instance()->openEditor(this->_d->_testsystemGraphicFile.fileName(),
//                                                                    Core::Id(Constants::SPENATGRAPHIC_ID),
//                                                                    Core::EditorManager::OpenInOtherSplit);
//  Core::EditorManager::instance()->gotoOtherSplit();
//  TestSystemGraphicEditor* testsystemGraphicEditor=qobject_cast<TestSystemGraphicEditor*>(editor);
//  if(!testsystemGraphicEditor)
//    return;

//  TestSystemGraphicWidget* testsystemGraphicWidget=testsystemGraphicEditor->widget();
//  this->_d->_testsystemGraphicWidget=testsystemGraphicWidget;

//  ///render testsystem////
//  TestSystemOutlineModel* testsystemOutlineModel = this->_d->_testsystemDocument->testsystemOutlineModel();
//  Q_ASSERT(testsystemOutlineModel);

//  graphlayout::ComLayoutDeclModel layoutCommand(testsystemOutlineModel,
//                                                testsystemGraphicWidget->declScene());
//  QString errorMessage;
//  bool result = layoutCommand.execute(&errorMessage);
//  if(!result)
//  {
//    Core::MessageManager::instance()->printToOutputPane(errorMessage,
//                                                        Core::MessageManager::WithFocus);
//    Core::MessageManager::instance()->showOutputPane();
//  }

//  return;
//}

} //end namespace testsystemeditor
