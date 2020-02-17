#include "diagnosiseditorwidget.hpp"

#include "diagnosisdocument.hpp"
#include "diagnosiscompletionassist.hpp"
#include "diagnosisoutlinemodel.hpp"
#include "combuilddiagnosisoutlinemodel.hpp"
#include "diagnosiseditorconstants.hpp"
#include "diagnosisgraphicwidget.hpp"
#include "diagnosisgraphiceditor.hpp"

//#include <mobatawidgets/ts/comrenderdiagnosis.hpp>

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

namespace diagnosiseditor{

enum {
  UPDATE_DOCUMENT_DEFAULT_INTERVAL = 150
};

class DiagnosisEditorWidget::Private
{
  friend class DiagnosisEditorWidget;

  Private()
    : _diagnosisEditor(0),
      _diagnosisDocument(new DiagnosisDocument)
  {}

public:
  ~Private()
  {}

private:
  DiagnosisEditor*         _diagnosisEditor;
  DiagnosisDocument::Ptr   _diagnosisDocument;
  QTimer*                 _updateOutlineTimer;
  QFile                   _diagnosisGraphicFile;
  DiagnosisGraphicWidget*  _diagnosisGraphicWidget;
};

DiagnosisEditorWidget::DiagnosisEditorWidget(QWidget *parent)
  : DslEditorWidget(parent),
    _d(new Private())
{
  this->_d->_diagnosisEditor=new DiagnosisEditor(this);
  this->setBaseTextDocument(this->_d->_diagnosisDocument);

  this->baseTextDocument()->setSyntaxHighlighter(new dsleditor::DslHighlighter(this->document()));
  this->setIndenter(new dsleditor::DslIndenter());
  this->setAutoCompleter(new dsleditor::DslAutoCompleter());

  this->_d->_updateOutlineTimer = new QTimer(this);
  this->_d->_updateOutlineTimer->setInterval(UPDATE_DOCUMENT_DEFAULT_INTERVAL);
  this->_d->_updateOutlineTimer->setSingleShot(true);
  connect(this->_d->_updateOutlineTimer, &QTimer::timeout,
          this, &DiagnosisEditorWidget::updateOutlineNow);
  connect(this, &DiagnosisEditorWidget::textChanged,
          this, &DiagnosisEditorWidget::updateOutline);
  connect(this, &DiagnosisEditorWidget::cursorPositionChanged,
          this, &DiagnosisEditorWidget::updateOutlineIndexNow);

  //  TODO: move 'DisTestRenderManager' in own repository
  //  DisTestRenderManager* renderManager = DisTestRenderManager::instance();
  //  connect(renderManager, SIGNAL(requestForApplyingNewGlobalDiagnosisRenderSettings(QString)),
  //          this, SLOT(globalDiagnosisRenderSettingsChangedSignalHandlder(QString)));
  //  connect(renderManager, SIGNAL(requestForApplyingNewCustomDiagnosisRenderSettings(QString)),
  //          this, SLOT(customDiagnosisRenderSettingsChangedSignalHandlder(QString)));
}

DiagnosisEditorWidget::~DiagnosisEditorWidget()
{
  delete this->_d;
}

DiagnosisEditor* DiagnosisEditorWidget::createEditor()
{
  return this->_d->_diagnosisEditor;
}

void DiagnosisEditorWidget::setFontSettings(const TextEditor::FontSettings &fs)
{
  return DslEditorWidget::setFontSettings(fs);
}

QVector<TextEditor::TextStyle> DiagnosisEditorWidget::highlighterFormatCategories()
{
  QVector<TextEditor::TextStyle> categories = DslEditorWidget::highlighterFormatCategories();
  categories << TextEditor::C_FUNCTION;

  return categories;
}

QString DiagnosisEditorWidget::wordUnderCursor() const
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

const DiagnosisDocument::Ptr& DiagnosisEditorWidget::diagnosisDocument() const
{
  return this->_d->_diagnosisDocument;
}

void DiagnosisEditorWidget::unCommentSelection()
{
  return Utils::unCommentSelection(this);
}

void DiagnosisEditorWidget::updateOutline()
{
  this->_d->_updateOutlineTimer->start();
}

QModelIndex DiagnosisEditorWidget::outlineModelIndex()
{
  QModelIndex currentModelIndex = this->indexForPosition(this->position());
  if(currentModelIndex.isValid())
    emit outlineModelIndexChanged(currentModelIndex);

  return currentModelIndex;
}

QTextCharFormat textCharFormat(int tokenType,
                               dsleditor::DslHighlighter* diagnosisHighlighter)
{
  Q_ASSERT(diagnosisHighlighter);

  if(tokenType == dslparser::Diagnosis)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Attribute)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Signal)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_KEYWORD);
//  else if(tokenType == dslparser::Function)
//    return diagnosisHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::Port)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::Type)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Import)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Declaration)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Enabled)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Sequence)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Loop)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Parallel)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::ParallelSequence)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Component)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Description)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Use)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
//  else if(tokenType == dslparser::Basetype)
//    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Timer)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::To)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::From)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Data)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Result)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Timeout)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::At)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_LINK);
  else if(tokenType == dslparser::Message)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Check)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_FIELD);
  else if(tokenType == dslparser::Alt)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TYPE);
  else if(tokenType == dslparser::Keyword)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_KEYWORD);
  else if(tokenType == dslparser::UnknownDiagnosisTokenType)
    return diagnosisHighlighter->textCharFormat(TextEditor::C_TEXT);

  return diagnosisHighlighter->textCharFormat(TextEditor::C_TEXT);
}

void DiagnosisEditorWidget::updateOutlineNow()
{
  using namespace dsleditor;

  this->_d->_updateOutlineTimer->stop();

  DiagnosisOutlineModel* diagnosisOutlineModel = this->_d->_diagnosisDocument->diagnosisOutlineModel();
  Q_ASSERT(diagnosisOutlineModel);

  QString currText=this->toPlainText();
  QString praefix = this->_d->_diagnosisDocument->fileName();
  dslparser::diagnosis::ComBuildDiagnosisModel::FileType fileType = dslparser::diagnosis::ComBuildDiagnosisModel::FileType::Complete;
  QString test = QFileInfo(praefix).suffix();
  if(test==QString("diagnosis"))
    fileType = dslparser::diagnosis::ComBuildDiagnosisModel::FileType::Complete;
  else if(test==QString("components"))
    fileType = dslparser::diagnosis::ComBuildDiagnosisModel::FileType::Components;
  else if(test==QString("signals"))
    fileType = dslparser::diagnosis::ComBuildDiagnosisModel::FileType::Signals;


  ComBuildDiagnosisOutlineModel buildOutlineCommand(currText, diagnosisOutlineModel,QFileInfo(praefix).absolutePath()+QStringLiteral("/"),fileType);
  buildOutlineCommand.execute();

  //TODO: just a try, maybe we need 'updateOutlineIndexNow()'
  this->outlineModelIndex();

  /// first semantic highlights//////
  DslHighlighter* diagnosisHighlighter = qobject_cast<DslHighlighter*>(this->baseTextDocument()->syntaxHighlighter());
  Q_ASSERT(diagnosisHighlighter);

  QList<QTextEdit::ExtraSelection> extraSelections;
  for(const dslparser::TokenTextLocation& textLoc : diagnosisOutlineModel->keywordTextSelections())
  {
    if(!textLoc.isValid())
      continue;

    QTextCursor cursor(this->baseTextDocument()->document());
    cursor.setPosition(textLoc.start());
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    QTextCharFormat textFormat = textCharFormat(textLoc.tokenType(), diagnosisHighlighter);
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
  for (const dslparser::DslError& diagnosisError : buildOutlineCommand.errors())
  {
    if (! diagnosisError.line())
      continue;
    else if (errors.contains(diagnosisError.line()))
      continue;

    errors.insert(diagnosisError.line());

    QTextBlock block=document()->findBlockByLineNumber(diagnosisError.line()-1);
    QTextCursor cursor(block);
    cursor.setPosition(block.position()+diagnosisError.charPositionInLine());
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    QTextEdit::ExtraSelection sel;
    sel.cursor = cursor;
    sel.format = errorFormat;
    sel.format.setToolTip(diagnosisError.message());
    extraSelections.append(sel);
  }
  this->setExtraSelections(CodeWarningsSelection, extraSelections);

  return;
}

void DiagnosisEditorWidget::updateOutlineIndexNow()
{
  if (this->_d->_updateOutlineTimer->isActive())
    return; // updateOutlineNow will call this function soon anyway

  this->outlineModelIndex();

  return;
}

QModelIndex DiagnosisEditorWidget::indexForPosition(unsigned cursorPosition) const
{
  using namespace dslparser;

  DiagnosisOutlineModel const* diagnosisOutlineModel = this->_d->_diagnosisEditor->diagnosisOutlineModel();
  Q_ASSERT(diagnosisOutlineModel);

  const ModelTextLocations& modelTextLocations = diagnosisOutlineModel->modelTextSelections();
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

IAssistInterface* DiagnosisEditorWidget::createAssistInterface(AssistKind assistKind,
                                                               AssistReason assistReason) const
{
  if (assistKind == TextEditor::Completion)
    return new DiagnosisCompletionAssistInterface(this->document(),
                                                  this->position(),
                                                  editor()->document()->fileName(),
                                                  assistReason/*,
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              mimeType(),
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              this->diagnosisDocument()*/);
  return BaseTextEditorWidget::createAssistInterface(assistKind, assistReason);
}

void DiagnosisEditorWidget::showDiagnosisGraphic()
{
  QString tempDiagnosisGraphicFile = QDir::tempPath();
  if (!tempDiagnosisGraphicFile.endsWith(QLatin1Char('/')))
    tempDiagnosisGraphicFile += QLatin1Char('/');
  tempDiagnosisGraphicFile += QFileInfo(this->editorDocument()->fileName()).baseName()
                              + QLatin1String(".diagnosisgraphic");

  if(this->_d->_diagnosisGraphicFile.exists())
  {
    this->_d->_diagnosisGraphicFile.close();
    this->_d->_diagnosisGraphicFile.rename(tempDiagnosisGraphicFile);
  }
  else
    this->_d->_diagnosisGraphicFile.setFileName(tempDiagnosisGraphicFile);

  QTC_ASSERT(this->_d->_diagnosisGraphicFile.open(QIODevice::ReadWrite), return;);
  this->_d->_diagnosisGraphicFile.close();

  qDebug()<<"temp-diagnosis-graphic-file: "<<this->_d->_diagnosisGraphicFile.fileName();

  Core::IEditor* editor=Core::EditorManager::instance()->openEditor(this->_d->_diagnosisGraphicFile.fileName(),
                                                                    Core::Id(Constants::DIAGNOSISGRAPHIC_ID),
                                                                    Core::EditorManager::OpenInOtherSplit);
  Core::EditorManager::instance()->gotoOtherSplit();
  DiagnosisGraphicEditor* diagnosisGraphicEditor=qobject_cast<DiagnosisGraphicEditor*>(editor);
  if(!diagnosisGraphicEditor)
    return;
  /*
  DiagnosisGraphicWidget* diagnosisGraphicWidget=diagnosisGraphicEditor->widget();
  this->_d->_diagnosisGraphicWidget=diagnosisGraphicWidget;

  ///render diagnosis////
  DiagnosisOutlineModel* diagnosisOutlineModel = this->_d->_diagnosisDocument->diagnosisOutlineModel();
  Q_ASSERT(diagnosisOutlineModel);

  view::ts::ComRenderDiagnosis layoutCommand(diagnosisGraphicWidget->diagnosisScene(),
                                            diagnosisOutlineModel->diagnosisModel());
  QString errorMessage;
  bool result = layoutCommand.execute(&errorMessage);
  if(!result)
  {
    Core::MessageManager::instance()->printToOutputPane(errorMessage,
                                                        Core::MessageManager::WithFocus);
    Core::MessageManager::instance()->showOutputPane();
  }
*/
  return;
}

} //end namespace diagnosiseditor
