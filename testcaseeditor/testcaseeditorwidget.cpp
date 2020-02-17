#include "testcaseeditorwidget.hpp"

#include "testcasedocument.hpp"
#include "testcasecompletionassist.hpp"
#include "testcaseoutlinemodel.hpp"
#include "combuildtestcaseoutlinemodel.hpp"
#include "testcaseeditorconstants.hpp"
#include "testcasegraphicwidget.hpp"
#include "testcasegraphiceditor.hpp"

#include <mobatawidgets/ts/comrendertestcase.hpp>

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

namespace testcaseeditor{

enum {
  UPDATE_DOCUMENT_DEFAULT_INTERVAL = 150
};

class TestCaseEditorWidget::Private
{
  friend class TestCaseEditorWidget;

  Private()
    : _testCaseEditor(0),
      _testCaseDocument(new TestCaseDocument)
  {}

public:
  ~Private()
  {}

private:
  TestCaseEditor*         _testCaseEditor;
  TestCaseDocument::Ptr   _testCaseDocument;
  QTimer*                 _updateOutlineTimer;
  QFile                   _testCaseGraphicFile;
  TestCaseGraphicWidget*  _testCaseGraphicWidget = nullptr;
};

TestCaseEditorWidget::TestCaseEditorWidget(QWidget *parent)
  : DslEditorWidget(parent),
    _d(new Private())
{
  this->_d->_testCaseEditor=new TestCaseEditor(this);
  this->setBaseTextDocument(this->_d->_testCaseDocument);

  this->baseTextDocument()->setSyntaxHighlighter(new dsleditor::DslHighlighter(this->document()));
  this->setIndenter(new dsleditor::DslIndenter());
  this->setAutoCompleter(new dsleditor::DslAutoCompleter());

  this->_d->_updateOutlineTimer = new QTimer(this);
  this->_d->_updateOutlineTimer->setInterval(UPDATE_DOCUMENT_DEFAULT_INTERVAL);
  this->_d->_updateOutlineTimer->setSingleShot(true);
  connect(this->_d->_updateOutlineTimer, &QTimer::timeout,
          this, &TestCaseEditorWidget::updateOutlineNow);
  connect(this, &TestCaseEditorWidget::textChanged,
          this, &TestCaseEditorWidget::updateOutline);
  connect(this, &TestCaseEditorWidget::cursorPositionChanged,
          this, &TestCaseEditorWidget::updateOutlineIndexNow);
}

TestCaseEditorWidget::~TestCaseEditorWidget()
{
  if(this->_d->_testCaseGraphicFile.exists())
  {
    this->_d->_testCaseGraphicFile.close();
    this->_d->_testCaseGraphicFile.remove();
  }

//  if(this->_d->_testCaseGraphicWidget)
//    this->_d->_testCaseGraphicWidget->testCaseGraphicEditor()->removeConnectedTextEditor(this->_d->_testCaseEditor);

  delete this->_d;
}

void TestCaseEditorWidget::duplicateFrom(BaseTextEditorWidget* editor)
{
  TestCaseEditorWidget* otherEditorWidget = qobject_cast<TestCaseEditorWidget*>(editor);
  Q_ASSERT(otherEditorWidget);

  BaseTextEditorWidget::duplicateFrom(otherEditorWidget);

  this->_d->_testCaseGraphicFile.setFileName(otherEditorWidget->_d->_testCaseGraphicFile.fileName());
  this->_d->_testCaseGraphicWidget = otherEditorWidget->_d->_testCaseGraphicWidget;

//  if(this->_d->_testCaseGraphicWidget)
//    this->_d->_testCaseGraphicWidget->testCaseGraphicEditor()->addConnectedTextEditor(this->_d->_testCaseEditor);

  return;
}

TestCaseEditor* TestCaseEditorWidget::createEditor()
{
  return this->_d->_testCaseEditor;
}

void TestCaseEditorWidget::setFontSettings(const TextEditor::FontSettings &fs)
{
  return DslEditorWidget::setFontSettings(fs);
}

QVector<TextEditor::TextStyle> TestCaseEditorWidget::highlighterFormatCategories()
{
  QVector<TextEditor::TextStyle> categories = DslEditorWidget::highlighterFormatCategories();
  categories << TextEditor::C_FUNCTION;

  return categories;
}

QString TestCaseEditorWidget::wordUnderCursor() const
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

const TestCaseDocument::Ptr& TestCaseEditorWidget::testCaseDocument() const
{
  return this->_d->_testCaseDocument;
}

void TestCaseEditorWidget::unCommentSelection()
{
  return Utils::unCommentSelection(this);
}

void TestCaseEditorWidget::updateOutline()
{
  this->_d->_updateOutlineTimer->start();
}

QModelIndex TestCaseEditorWidget::outlineModelIndex()
{
  QModelIndex currentModelIndex = this->indexForPosition(this->position());
  if(currentModelIndex.isValid())
    emit outlineModelIndexChanged(currentModelIndex);

  return currentModelIndex;
}

QTextCharFormat textCharFormat(int tokenType,
                               dsleditor::DslHighlighter* testCaseHighlighter)
{
  Q_ASSERT(testCaseHighlighter);

  if(tokenType == dslparser::TestCase)
    return testCaseHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Attribute)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Signal)
    return testCaseHighlighter->textCharFormat(TextEditor::C_KEYWORD);
//  else if(tokenType == dslparser::Function)
//    return testCaseHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::Port)
    return testCaseHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::Type)
    return testCaseHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Import)
    return testCaseHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Declaration)
    return testCaseHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Enabled)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
//  else if(tokenType == dslparser::LessThan)
//    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
//  else if(tokenType == dslparser::GreaterThan)
//    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Component)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Timer)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::To)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::From)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Data)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Result)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Timeout)
    return testCaseHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::At)
    return testCaseHighlighter->textCharFormat(TextEditor::C_LINK);
  else if(tokenType == dslparser::Message)
    return testCaseHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Check)
    return testCaseHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Alt)
    return testCaseHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Keyword)
    return testCaseHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::UnknownTestCaseTokenType)
    return testCaseHighlighter->textCharFormat(TextEditor::C_TEXT);

  return testCaseHighlighter->textCharFormat(TextEditor::C_TEXT);
}

void TestCaseEditorWidget::updateOutlineNow()
{
  QString errorString;
  using namespace dsleditor;

  this->_d->_updateOutlineTimer->stop();

  TestCaseOutlineModel* testCaseOutlineModel = this->_d->_testCaseDocument->testCaseOutlineModel();
  Q_ASSERT(testCaseOutlineModel);

  QString currText=this->toPlainText();
  QString praefix = this->_d->_testCaseDocument->fileName();
  ComBuildTestCaseOutlineModel buildOutlineCommand(currText,
                                                   testCaseOutlineModel,
                                                   QFileInfo(praefix).absolutePath()+QStringLiteral("/"));
  if(!buildOutlineCommand.execute(&errorString))
    return;

  //TODO: just a try, maybe we need 'updateOutlineIndexNow()'
  this->outlineModelIndex();

  /// first semantic highlights//////
  DslHighlighter* testcaseHighlighter = qobject_cast<DslHighlighter*>(this->baseTextDocument()->syntaxHighlighter());
  Q_ASSERT(testcaseHighlighter);

  QList<QTextEdit::ExtraSelection> extraSelections;
  for(const dslparser::TokenTextLocation& textLoc : testCaseOutlineModel->keywordTextSelections())
  {
    if(!textLoc.isValid())
      continue;

    QTextCursor cursor(this->baseTextDocument()->document());
    cursor.setPosition(textLoc.start());
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    QTextCharFormat textFormat = textCharFormat(textLoc.tokenType(), testcaseHighlighter);
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
  for (const dslparser::DslError& testcaseError : buildOutlineCommand.errors())
  {
    if (! testcaseError.line())
      continue;
    else if (errors.contains(testcaseError.line()))
      continue;

    errors.insert(testcaseError.line());

    QTextBlock block=document()->findBlockByLineNumber(testcaseError.line()-1);
    QTextCursor cursor(block);
    cursor.setPosition(block.position()+testcaseError.charPositionInLine());
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    QTextEdit::ExtraSelection sel;
    sel.cursor = cursor;
    sel.format = errorFormat;
    sel.format.setToolTip(testcaseError.message());
    extraSelections.append(sel);
  }
  this->setExtraSelections(CodeWarningsSelection, extraSelections);

  if(this->_d->_testCaseGraphicWidget != nullptr){
    if(!this->_d->_testCaseGraphicWidget->updateTestCaseGraphic())
      return;
  }

  if(!errorString.isEmpty())
    qWarning() << errorString.toLatin1();

  return;
}

void TestCaseEditorWidget::updateOutlineIndexNow()
{
  if (this->_d->_updateOutlineTimer->isActive())
    return; // updateOutlineNow will call this function soon anyway

  this->outlineModelIndex();

  return;
}

QModelIndex TestCaseEditorWidget::indexForPosition(unsigned cursorPosition) const
{
  using namespace dslparser;

  TestCaseOutlineModel const* testCaseOutlineModel = this->_d->_testCaseEditor->testCaseOutlineModel();
  Q_ASSERT(testCaseOutlineModel);

  const ModelTextLocations& modelTextLocations = testCaseOutlineModel->modelTextSelections();
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

IAssistInterface* TestCaseEditorWidget::createAssistInterface(AssistKind assistKind,
                                                              AssistReason assistReason) const
{
  if (assistKind == TextEditor::Completion)
    return new TestCaseCompletionAssistInterface(this->document(),
                                                 this->position(),
                                                 editor()->document()->fileName(),
                                                 assistReason/*,
                                                                                                                                                                                                                                                                                                                                                                                                                                                    mimeType(),
                                                                                                                                                                                                                                                                                                                                                                                                                                                    this->testcaseDocument()*/);
  return BaseTextEditorWidget::createAssistInterface(assistKind, assistReason);
}

Core::IEditor* TestCaseEditorWidget::showTestCaseGraphic()
{
  QString tempTestCaseGraphicFile = QDir::tempPath();
  if (!tempTestCaseGraphicFile.endsWith(QLatin1Char('/')))
    tempTestCaseGraphicFile += QLatin1Char('/');
  tempTestCaseGraphicFile += QFileInfo(this->editorDocument()->fileName()).baseName()
                             + QLatin1String(".testcasegraphic");

  if(this->_d->_testCaseGraphicFile.exists())
  {
    this->_d->_testCaseGraphicFile.close();
    this->_d->_testCaseGraphicFile.rename(tempTestCaseGraphicFile);
  }
  else
    this->_d->_testCaseGraphicFile.setFileName(tempTestCaseGraphicFile);

  QTC_ASSERT(this->_d->_testCaseGraphicFile.open(QIODevice::ReadWrite), return nullptr;);
  this->_d->_testCaseGraphicFile.close();

  qDebug()<<"temp-testCase-graphic-file: "<<this->_d->_testCaseGraphicFile.fileName();

  Core::IEditor* editor=Core::EditorManager::instance()->openEditor(this->_d->_testCaseGraphicFile.fileName(),
                                                                    Core::Id(Constants::TESTCASEGRAPHIC_ID),
                                                                    Core::EditorManager::OpenInOtherSplit);
  Core::EditorManager::instance()->gotoOtherSplit();

  TestCaseGraphicEditor* testCaseGraphicEditor=qobject_cast<TestCaseGraphicEditor*>(editor);
  if(!testCaseGraphicEditor)
    return nullptr;

  ///render testcase////
  TestCaseOutlineModel* testCaseOutlineModel = this->_d->_testCaseDocument->testCaseOutlineModel();
  Q_ASSERT(testCaseOutlineModel);

  testCaseGraphicEditor->setTestCaseItem(testCaseOutlineModel->testCaseModel().data());
  testCaseGraphicEditor->setTestCaseDocument(this->_d->_testCaseDocument.data());
  testCaseGraphicEditor->addConnectedTextEditor(this->_d->_testCaseEditor);

  this->_d->_testCaseGraphicWidget=testCaseGraphicEditor->testCaseGraphicWidget();
  Q_ASSERT(this->_d->_testCaseGraphicWidget);

  this->updateOutlineNow();

  return testCaseGraphicEditor;
}

} //end namespace testcaseeditor
