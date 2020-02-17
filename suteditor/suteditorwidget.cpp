#include "suteditorwidget.hpp"

#include "sutdocument.hpp"
#include "sutcompletionassist.hpp"
#include "sutoutlinemodel.hpp"
#include "combuildsutoutlinemodel.hpp"
#include "suteditorconstants.hpp"

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

namespace suteditor{

enum {
  UPDATE_DOCUMENT_DEFAULT_INTERVAL = 150
};

class SutEditorWidget::Private
{
  friend class SutEditorWidget;

  Private()
    : _sutEditor(0),
      _sutDocument(new SutDocument)
  {}

public:
  ~Private()
  {}

private:
  SutEditor*        _sutEditor;
  SutDocument::Ptr  _sutDocument;
  QTimer*           _updateOutlineTimer;
};

SutEditorWidget::SutEditorWidget(QWidget *parent)
  : DslEditorWidget(parent),
    _d(new Private())
{
  this->_d->_sutEditor=new SutEditor(this);
  this->setBaseTextDocument(this->_d->_sutDocument);

  this->baseTextDocument()->setSyntaxHighlighter(new dsleditor::DslHighlighter(this->document()));
  this->setIndenter(new dsleditor::DslIndenter());
  this->setAutoCompleter(new dsleditor::DslAutoCompleter());

  this->_d->_updateOutlineTimer = new QTimer(this);
  this->_d->_updateOutlineTimer->setInterval(UPDATE_DOCUMENT_DEFAULT_INTERVAL);
  this->_d->_updateOutlineTimer->setSingleShot(true);
  connect(this->_d->_updateOutlineTimer, &QTimer::timeout,
          this, &SutEditorWidget::updateOutlineNow);
  connect(this, &SutEditorWidget::textChanged,
          this, &SutEditorWidget::updateOutline);
  connect(this, &SutEditorWidget::cursorPositionChanged,
          this, &SutEditorWidget::updateOutlineIndexNow);

  //  SutRenderManager *renderManager = SutRenderManager::instance();
  //  connect(renderManager, SIGNAL(requestForApplyingNewGlobalSutRenderSettings(QString)),
  //          this, SLOT(globalSutRenderSettingsChangedSignalHandlder(QString)));
  //  connect(renderManager, SIGNAL(requestForApplyingNewCustomSutRenderSettings(QString)),
  //          this, SLOT(customSutRenderSettingsChangedSignalHandlder(QString)));
}

SutEditorWidget::~SutEditorWidget()
{
  delete this->_d;
}

SutEditor* SutEditorWidget::createEditor()
{
  return this->_d->_sutEditor;
}

void SutEditorWidget::setFontSettings(const TextEditor::FontSettings &fs)
{
  return DslEditorWidget::setFontSettings(fs);
}

QVector<TextEditor::TextStyle> SutEditorWidget::highlighterFormatCategories()
{
  QVector<TextEditor::TextStyle> categories = DslEditorWidget::highlighterFormatCategories();
  categories << TextEditor::C_FUNCTION;

  return categories;
}

QString SutEditorWidget::wordUnderCursor() const
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

const SutDocument::Ptr& SutEditorWidget::sutDocument() const
{
  return this->_d->_sutDocument;
}

void SutEditorWidget::unCommentSelection()
{
  return Utils::unCommentSelection(this);
}

void SutEditorWidget::updateOutline()
{
  this->_d->_updateOutlineTimer->start();
}

QModelIndex SutEditorWidget::outlineModelIndex()
{
  QModelIndex currentModelIndex = this->indexForPosition(this->position());
  if(currentModelIndex.isValid())
    emit outlineModelIndexChanged(currentModelIndex);

  return currentModelIndex;
}

QTextCharFormat textCharFormat(int tokenType,
                               dsleditor::DslHighlighter* sutHighlighter)
{
  Q_ASSERT(sutHighlighter);

  if(tokenType == dslparser::Sut)
    return sutHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Attribute)
    return sutHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Signal)
    return sutHighlighter->textCharFormat(TextEditor::C_KEYWORD);
//  else if(tokenType == dslparser::Function)
//    return sutHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::Port)
    return sutHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::Type)
    return sutHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Keyword)
    return sutHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::UnknownSutTokenType)
    return sutHighlighter->textCharFormat(TextEditor::C_TEXT);

  return sutHighlighter->textCharFormat(TextEditor::C_TEXT);
}

void SutEditorWidget::updateOutlineNow()
{
  using namespace dsleditor;

  this->_d->_updateOutlineTimer->stop();

  SutOutlineModel* sutOutlineModel = this->_d->_sutDocument->sutOutlineModel();
  Q_ASSERT(sutOutlineModel);

  QString currText=this->toPlainText();
  ComBuildSutOutlineModel buildOutlineCommand(currText, sutOutlineModel);
  buildOutlineCommand.execute();

  //TODO: just a try, maybe we need 'updateOutlineIndexNow()'
  this->outlineModelIndex();

  /// first semantic highlights//////
  DslHighlighter* sutHighlighter = qobject_cast<DslHighlighter*>(this->baseTextDocument()->syntaxHighlighter());
  Q_ASSERT(sutHighlighter);

  QList<QTextEdit::ExtraSelection> extraSelections;
  for(const dslparser::TokenTextLocation& textLoc : sutOutlineModel->keywordTextSelections())
  {
    if(!textLoc.isValid())
      continue;

    QTextCursor cursor(this->baseTextDocument()->document());
    cursor.setPosition(textLoc.start());
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    QTextCharFormat textFormat = textCharFormat(textLoc.tokenType(), sutHighlighter);
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
  for (const dslparser::DslError& sutError : buildOutlineCommand.errors())
  {
    if (! sutError.line())
      continue;
    else if (errors.contains(int(sutError.line())))
      continue;

    errors.insert(int(sutError.line()));

    QTextBlock block=document()->findBlockByLineNumber(int(sutError.line())-1);
    QTextCursor cursor(block);
    cursor.setPosition(block.position()+sutError.charPositionInLine());
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    QTextEdit::ExtraSelection sel;
    sel.cursor = cursor;
    sel.format = errorFormat;
    sel.format.setToolTip(sutError.message());
    extraSelections.append(sel);
  }
  this->setExtraSelections(CodeWarningsSelection, extraSelections);

  return;
}

void SutEditorWidget::updateOutlineIndexNow()
{
  if (this->_d->_updateOutlineTimer->isActive())
    return; // updateOutlineNow will call this function soon anyway

  this->outlineModelIndex();

  return;
}

QModelIndex SutEditorWidget::indexForPosition(unsigned cursorPosition) const
{
  using namespace dslparser;

  SutOutlineModel const* sutOutlineModel = this->_d->_sutEditor->sutOutlineModel();
  Q_ASSERT(sutOutlineModel);

  const ModelTextLocations& modelTextLocations = sutOutlineModel->modelTextSelections();
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

IAssistInterface* SutEditorWidget::createAssistInterface(AssistKind assistKind,
                                                            AssistReason assistReason) const
{
  if (assistKind == TextEditor::Completion)
    return new SutCompletionAssistInterface(this->document(),
                                               this->position(),
                                               editor()->document()->fileName(),
                                               assistReason/*,
                                                                                                                                                                                                                                                                                                                                                                                                       mimeType(),
                                                                                                                                                                                                                                                                                                                                                                                                       this->sutDocument()*/);
  return BaseTextEditorWidget::createAssistInterface(assistKind, assistReason);
}

//void SutEditorWidget::showSutGraphic()
//{
//  QString tempSutGraphicFile = QDir::tempPath();
//  if (!tempSutGraphicFile.endsWith(QLatin1Char('/')))
//    tempSutGraphicFile += QLatin1Char('/');
//  tempSutGraphicFile += QFileInfo(this->editorDocument()->fileName()).baseName()
//                           + QLatin1String(".sutgraphic");

//  if(this->_d->_sutGraphicFile.exists())
//  {
//    this->_d->_sutGraphicFile.close();
//    this->_d->_sutGraphicFile.rename(tempSutGraphicFile);
//  }
//  else
//    this->_d->_sutGraphicFile.setFileName(tempSutGraphicFile);

//  QTC_ASSERT(this->_d->_sutGraphicFile.open(QIODevice::ReadWrite), return;);
//  this->_d->_sutGraphicFile.close();

//  qDebug()<<"temp-sut-graphic-file: "<<this->_d->_sutGraphicFile.fileName();

//  Core::IEditor* editor=Core::EditorManager::instance()->openEditor(this->_d->_sutGraphicFile.fileName(),
//                                                                    Core::Id(Constants::SPENATGRAPHIC_ID),
//                                                                    Core::EditorManager::OpenInOtherSplit);
//  Core::EditorManager::instance()->gotoOtherSplit();
//  SutGraphicEditor* sutGraphicEditor=qobject_cast<SutGraphicEditor*>(editor);
//  if(!sutGraphicEditor)
//    return;

//  SutGraphicWidget* sutGraphicWidget=sutGraphicEditor->widget();
//  this->_d->_sutGraphicWidget=sutGraphicWidget;

//  ///render sut////
//  SutOutlineModel* sutOutlineModel = this->_d->_sutDocument->sutOutlineModel();
//  Q_ASSERT(sutOutlineModel);

//  graphlayout::ComLayoutDeclModel layoutCommand(sutOutlineModel,
//                                                sutGraphicWidget->declScene());
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

} //end namespace suteditor
