#include "suteditorwidget.hpp"

#include "distesteditorconstants.hpp"
#include "sutdocument.hpp"
#include "distestdslautocompleter.hpp"
#include "distestdslindenter.hpp"
#include "suteditorhighlighter.hpp"
#include "sutgraphiceditor.hpp"

#include "distestrendermanager.hpp"
#include "distestrendersettings.hpp"

#include <mobatawidgets/ts/comrendersut.hpp>

#include <coreplugin/messagemanager.h>
#include <texteditor/fontsettings.h>

#include <utils/qtcassert.h>

#include <QFileInfo>
#include <QDir>
#include <QTemporaryFile>
#include <QTextCodec>
#include <QDebug>
//#include <stdexcept>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{

class SutEditorWidget::Private
{
  friend class SutEditorWidget;

  Private()
    : _sutItem(0), _sutEditor(0), _sutGraphicWidget(0)
  {}

public:
  ~Private()
  {}

private:
  const model::ts::SutItem* _sutItem;
  SutEditor*        _sutEditor;
  QFile             _sutGraphicFile;
  SutGraphicWidget* _sutGraphicWidget;
};

SutEditorWidget::SutEditorWidget(QWidget *parent)
  : dsleditor::DslEditorWidget(parent), _d(new Private())
{
  this->setBaseTextDocument(QSharedPointer<SutDocument>(new SutDocument()));
  this->_d->_sutEditor=new SutEditor(this);

  this->baseTextDocument()->setSyntaxHighlighter(new SutEditorHighlighter(this->document()));
  this->setIndenter(new DisTestDslIndenter());
  this->setAutoCompleter(new DisTestDslAutoCompleter());

  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  connect(renderManager, SIGNAL(requestForApplyingNewGlobalSutRenderSettings(QString)),
          this, SLOT(globalSutRenderSettingsChangedSignalHandlder(QString)));
  connect(renderManager, SIGNAL(requestForApplyingNewCustomSutRenderSettings(QString)),
          this, SLOT(customSutRenderSettingsChangedSignalHandlder(QString)));
}

SutEditorWidget::~SutEditorWidget()
{
  if(this->_d->_sutGraphicFile.exists())
  {
    this->_d->_sutGraphicFile.close();
    this->_d->_sutGraphicFile.remove();
  }

  delete this->_d;
}

SutEditor *SutEditorWidget::createEditor()
{
  return this->_d->_sutEditor;
}

void SutEditorWidget::setFontSettings(const TextEditor::FontSettings &fs)
{
  return dsleditor::DslEditorWidget::setFontSettings(fs);
}

void SutEditorWidget::showSutGraphic()
{
  //get sut-item ...
  model::ts::SutItem const* sutItem=this->_d->_sutEditor->sutItem();
  if(!sutItem)
  {
    Core::MessageManager::instance()->printToOutputPane(tr("Please build your project, before you "
                                                           "seeing the sut graphic."),
                                                        Core::MessageManager::WithFocus);
    Core::MessageManager::instance()->showOutputPane();
    return;
  }
  this->_d->_sutItem=this->_d->_sutEditor->sutItem();

  QString tempSutGraphicFile = QDir::tempPath();
  if (!tempSutGraphicFile.endsWith(QLatin1Char('/')))
    tempSutGraphicFile += QLatin1Char('/');
  tempSutGraphicFile += QFileInfo(this->editorDocument()->fileName()).baseName()
                        + QLatin1String(".sutgraphic");

  if(this->_d->_sutGraphicFile.exists())
  {
    this->_d->_sutGraphicFile.close();
    this->_d->_sutGraphicFile.rename(tempSutGraphicFile);
  }
  else
    this->_d->_sutGraphicFile.setFileName(tempSutGraphicFile);

  QTC_ASSERT(this->_d->_sutGraphicFile.open(QIODevice::ReadWrite), return;);
  this->_d->_sutGraphicFile.close();

  qDebug()<<"temp-sut-graphic-file: "<<this->_d->_sutGraphicFile.fileName();

  //  Core::EditorManager::instance()->gotoOtherSplit();
  Core::IEditor* editor=Core::EditorManager::instance()->openEditor(this->_d->_sutGraphicFile.fileName(),
                                                                    Core::Id(Constants::SUTGRAPHIC_ID),
                                                                    Core::EditorManager::OpenInOtherSplit);
  Core::EditorManager::instance()->gotoOtherSplit();
  if(SutGraphicEditor* sutGraphicEditor=qobject_cast<SutGraphicEditor*>(editor))
  {
    SutGraphicWidget* sutGraphicWidget=sutGraphicEditor->widget();
    this->_d->_sutGraphicWidget=sutGraphicWidget;
    renderSut();
  }

  return;
}

void SutEditorWidget::renderSut()
{
  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  const DisTestRenderSettings *renderSettings;

  try
  {
    renderSettings = renderManager->renderSettingsFromSutDocument(this->editorDocument()->fileName());
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
    return;
  }

  QString errorMessage;
  view::ts::ComRenderSut renderCommand(this->_d->_sutGraphicWidget->sutScene(),
                                       this->_d->_sutItem,
                                       renderSettings->sutCompOptions(),
                                       renderSettings->sutPortOptions(),
                                       renderSettings->sutLinkOptions(),
                                       renderSettings->sutBoxBrush(),
                                       renderSettings->sutBoxCompMargin(),
                                       renderSettings->sutBoxMargin(),
                                       renderSettings->sutBoxRadius());
  bool result=renderCommand.execute(&errorMessage);
  if(!result)
  {
    Core::MessageManager::instance()->printToOutputPane(errorMessage,
                                                        Core::MessageManager::WithFocus);
    Core::MessageManager::instance()->showOutputPane();
  }

  return;
}

void SutEditorWidget::globalSutRenderSettingsChangedSignalHandlder(QString projectID)
{
  try
  {
    if (this->_d->_sutGraphicFile.exists())
    {
      DisTestRenderManager *renderManager = DisTestRenderManager::instance();
      QString myProjectID(renderManager->projectIDforSutDocument(this->editorDocument()->fileName()));
      if (renderManager->isGlobalRendenSettingsUsed(myProjectID))
      {
        if ((projectID.isEmpty()) || (!projectID.compare(myProjectID)))
        {
          renderSut();
        }
      }
    }
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
  }
}

void SutEditorWidget::customSutRenderSettingsChangedSignalHandlder(QString projectID)
{
  try
  {
    if (this->_d->_sutGraphicFile.exists())
    {
      DisTestRenderManager *renderManager = DisTestRenderManager::instance();
      QString myProjectID(renderManager->projectIDforSutDocument(this->editorDocument()->fileName()));
      if (!renderManager->isGlobalRendenSettingsUsed(myProjectID))
      {
        if ((projectID.isEmpty()) || (!projectID.compare(myProjectID)))
        {
          renderSut();
        }
      }
    }
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
  }
}

} //end namespace distesteditor
