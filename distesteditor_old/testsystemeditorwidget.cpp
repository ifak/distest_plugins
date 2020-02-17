#include "testsystemeditorwidget.hpp"

#include "distesteditorconstants.hpp"
#include "testsystemdocument.hpp"
#include "distestdslautocompleter.hpp"
#include "distestdslindenter.hpp"
#include "testsystemeditorhighlighter.hpp"
#include "testsystemgraphiceditor.hpp"

#include "distestrendermanager.hpp"
#include "distestrendersettings.hpp"

#include <mobatawidgets/ts/comrendertestsystem.hpp>

#include <coreplugin/messagemanager.h>
#include <texteditor/fontsettings.h>

#include <utils/qtcassert.h>

#include <QFileInfo>
#include <QDir>
#include <QTemporaryFile>
#include <QTextCodec>
#include <QDebug>
#include <stdexcept>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{

class TestSystemEditorWidget::Private
{
  friend class TestSystemEditorWidget;

  Private()
    : _testSystemItem(0), _testSystemEditor(0), _testSystemGraphicWidget(0)
  {}

public:
  ~Private()
  {}

private:
  const model::ts::TestSystemItem* _testSystemItem;
  TestSystemEditor*        _testSystemEditor;
  QFile                    _testSystemGraphicFile;
  TestSystemGraphicWidget* _testSystemGraphicWidget;
};

TestSystemEditorWidget::TestSystemEditorWidget(QWidget *parent)
  : dsleditor::DslEditorWidget(parent), _d(new Private())
{
  this->setBaseTextDocument(QSharedPointer<TestSystemDocument>(new TestSystemDocument()));
  this->_d->_testSystemEditor=new TestSystemEditor(this);

  this->baseTextDocument()->setSyntaxHighlighter(new TestSystemEditorHighlighter(this->document()));
  this->setIndenter(new DisTestDslIndenter());
  this->setAutoCompleter(new DisTestDslAutoCompleter());

  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  connect(renderManager, SIGNAL(requestForApplyingNewGlobalSutRenderSettings(QString)),
          this, SLOT(globalTestSystemRenderSettingsChangedSignalHandlder(QString)));
  connect(renderManager, SIGNAL(requestForApplyingNewCustomSutRenderSettings(QString)),
          this, SLOT(customTestSystemRenderSettingsChangedSignalHandlder(QString)));
  connect(renderManager, SIGNAL(requestForApplyingNewGlobalTestSystemRenderSettings(QString)),
          this, SLOT(globalTestSystemRenderSettingsChangedSignalHandlder(QString)));
  connect(renderManager, SIGNAL(requestForApplyingNewCustomTestSystemRenderSettings(QString)),
          this, SLOT(customTestSystemRenderSettingsChangedSignalHandlder(QString)));
}

TestSystemEditorWidget::~TestSystemEditorWidget()
{
  if(this->_d->_testSystemGraphicFile.exists())
  {
    this->_d->_testSystemGraphicFile.close();
    this->_d->_testSystemGraphicFile.remove();
  }

  delete this->_d;
}

TestSystemEditor *TestSystemEditorWidget::createEditor()
{
  return this->_d->_testSystemEditor;
}

void TestSystemEditorWidget::setFontSettings(const TextEditor::FontSettings &fs)
{
  return dsleditor::DslEditorWidget::setFontSettings(fs);
}

void TestSystemEditorWidget::showTestSystemGraphic()
{

  //get test-system-item ...
  model::ts::TestSystemItem const* testSystemItem=this->_d->_testSystemEditor->testSystemItem();
  if(!testSystemItem)
  {
    Core::MessageManager::instance()->printToOutputPane(tr("Please build your project, before you "
                                                           "seeing the test system graphic."),
                                                        Core::MessageManager::WithFocus);
    Core::MessageManager::instance()->showOutputPane();
    return;
  }
  this->_d->_testSystemItem=this->_d->_testSystemEditor->testSystemItem();

  QString tempTestSystemGraphicFile = QDir::tempPath();
  if (!tempTestSystemGraphicFile.endsWith(QLatin1Char('/')))
    tempTestSystemGraphicFile += QLatin1Char('/');
  tempTestSystemGraphicFile += QFileInfo(this->editorDocument()->fileName()).baseName()
                               + QLatin1String(".testsystemgraphic");

  if(this->_d->_testSystemGraphicFile.exists())
  {
    this->_d->_testSystemGraphicFile.close();
    this->_d->_testSystemGraphicFile.rename(tempTestSystemGraphicFile);
  }
  else
    this->_d->_testSystemGraphicFile.setFileName(tempTestSystemGraphicFile);

  QTC_ASSERT(this->_d->_testSystemGraphicFile.open(QIODevice::ReadWrite), return;);
  this->_d->_testSystemGraphicFile.close();

  qDebug()<<"temp-test-system-graphic-file: "<<this->_d->_testSystemGraphicFile.fileName();

  //  Core::EditorManager::instance()->gotoOtherSplit();
  Core::IEditor* editor=Core::EditorManager::instance()->openEditor(this->_d->_testSystemGraphicFile.fileName(),
                                                                    Core::Id(Constants::TESTSYSTEMGRAPHIC_ID),
                                                                    Core::EditorManager::OpenInOtherSplit);
  Core::EditorManager::instance()->gotoOtherSplit();
  if(TestSystemGraphicEditor* testSystemGraphicEditor=qobject_cast<TestSystemGraphicEditor*>(editor))
  {
    TestSystemGraphicWidget* testSystemGraphicWidget=testSystemGraphicEditor->widget();
    this->_d->_testSystemGraphicWidget=testSystemGraphicWidget;
    renderTestSystem();
  }

  return;
}

void TestSystemEditorWidget::renderTestSystem()
{
  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  const DisTestRenderSettings *renderSettings;

  try
  {
    renderSettings = renderManager->renderSettingsFromTestSystemDocument(this->editorDocument()->fileName());
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
    return;
  }

  QString errorMessage;
  view::ts::ComRenderTestSystem renderCommand(this->_d->_testSystemGraphicWidget->testSystemScene(),
                                              this->_d->_testSystemItem,
                                              renderSettings->sutCompOptions(),
                                              renderSettings->sutPortOptions(),
                                              renderSettings->sutLinkOptions(),
                                              renderSettings->sutBoxBrush(),
                                              renderSettings->sutBoxCompMargin(),
                                              renderSettings->sutBoxMargin(),
                                              renderSettings->sutBoxRadius(),
                                              renderSettings->testSystemCompOptions(),
                                              renderSettings->testSystemPortOptions(),
                                              renderSettings->testSystemLinkOptions(),
                                              renderSettings->testSystemSpaceToSutBox(),
                                              renderSettings->testSystemBoxOptions(),
                                              renderSettings->testSystemBoxMargin(),
                                              renderSettings->testSystemBoxRadius());
  bool result=renderCommand.execute(&errorMessage);
  if(!result)
  {
    Core::MessageManager::instance()->printToOutputPane(errorMessage,
                                                        Core::MessageManager::WithFocus);
    Core::MessageManager::instance()->showOutputPane();
  }

  return;
}

void TestSystemEditorWidget::globalTestSystemRenderSettingsChangedSignalHandlder(QString projectID)
{
  try
  {
    if (this->_d->_testSystemGraphicFile.exists())
    {
      DisTestRenderManager *renderManager = DisTestRenderManager::instance();
      QString myProjectID(renderManager->projectIDforTestSystemDocument(this->editorDocument()->fileName()));
      if ((renderManager->isGlobalRendenSettingsUsed(myProjectID)))
      {
        if ((projectID.isEmpty()) || (!projectID.compare(myProjectID)))
        {
          renderTestSystem();
        }
      }
    }
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
  }
}

void TestSystemEditorWidget::customTestSystemRenderSettingsChangedSignalHandlder(QString projectID)
{
  try
  {
    if (this->_d->_testSystemGraphicFile.exists())
    {
      DisTestRenderManager *renderManager = DisTestRenderManager::instance();
      QString myProjectID(renderManager->projectIDforTestSystemDocument(this->editorDocument()->fileName()));
      if (!renderManager->isGlobalRendenSettingsUsed(myProjectID))
      {
        if ((projectID.isEmpty()) || (!projectID.compare(myProjectID)))
        {
          renderTestSystem();
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
