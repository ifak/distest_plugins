#include "testcaseeditorwidget.hpp"

#include "distesteditorconstants.hpp"
#include "testcasedocument.hpp"
#include "distestdslautocompleter.hpp"
#include "distestdslindenter.hpp"
#include "testcaseeditorhighlighter.hpp"
#include "testcasegraphiceditor.hpp"

#include "distestrendermanager.hpp"
#include "distestrendersettings.hpp"

#include <mobatawidgets/ts/comrendertestcase.hpp>

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

class TestCaseEditorWidget::Private
{
  friend class TestCaseEditorWidget;

  Private()
    : _testCaseItem(0), _testCaseEditor(0), _testCaseGraphicWidget(0)
  {}

public:
  ~Private()
  {}

private:
  const model::ts::TestCaseItem* _testCaseItem;
  TestCaseEditor*        _testCaseEditor;
  QFile                  _testCaseGraphicFile;
  TestCaseGraphicWidget* _testCaseGraphicWidget;
};

TestCaseEditorWidget::TestCaseEditorWidget(QWidget *parent)
  : dsleditor::DslEditorWidget(parent), _d(new Private())
{
  this->setBaseTextDocument(QSharedPointer<TestCaseDocument>(new TestCaseDocument()));
  this->_d->_testCaseEditor=new TestCaseEditor(this);

  this->baseTextDocument()->setSyntaxHighlighter(new TestCaseEditorHighlighter(this->document()));
  this->setIndenter(new DisTestDslIndenter());
  this->setAutoCompleter(new DisTestDslAutoCompleter());

  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  connect(renderManager, SIGNAL(requestForApplyingNewGlobalTestCaseRenderSettings(QString)),
          this, SLOT(globalTestCaseRenderSettingsChangedSignalHandlder(QString)));
  connect(renderManager, SIGNAL(requestForApplyingNewCustomTestCaseRenderSettings(QString)),
            this, SLOT(customTestCaseRenderSettingsChangedSignalHandlder(QString)));
}

TestCaseEditorWidget::~TestCaseEditorWidget()
{
  if(this->_d->_testCaseGraphicFile.exists())
  {
    this->_d->_testCaseGraphicFile.close();
    this->_d->_testCaseGraphicFile.remove();
  }

  delete this->_d;
}

TestCaseEditor* TestCaseEditorWidget::createEditor()
{
  return this->_d->_testCaseEditor;
}

void TestCaseEditorWidget::setFontSettings(const TextEditor::FontSettings &fs)
{
  return dsleditor::DslEditorWidget::setFontSettings(fs);
}

void TestCaseEditorWidget::showTestCaseGraphic()
{
  //get test-case-item ...
  model::ts::TestCaseItem const* testCaseItem=this->_d->_testCaseEditor->testCaseItem();
  if(!testCaseItem)
  {
    Core::MessageManager::instance()->printToOutputPane(tr("Please build your project, before you "
                                                           "seeing the test case graphic."),
                                                        Core::MessageManager::WithFocus);
    Core::MessageManager::instance()->showOutputPane();
    return;
  }
  this->_d->_testCaseItem=testCaseItem;

  if(this->_d->_testCaseItem->sequenceItems().count()==0)
  {
    Core::MessageManager::instance()->printToOutputPane(tr("No steps within this test case specified, "
                                                           "no test case graphic necessary!"),
                                                        Core::MessageManager::WithFocus);
    Core::MessageManager::instance()->showOutputPane();
    return;
  }

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

  QTC_ASSERT(this->_d->_testCaseGraphicFile.open(QIODevice::ReadWrite), return;);
  this->_d->_testCaseGraphicFile.close();

  qDebug()<<"temp-test-case-graphic-file: "<<this->_d->_testCaseGraphicFile.fileName();

//  Core::EditorManager::instance()->gotoOtherSplit();
  Core::IEditor* editor=Core::EditorManager::instance()->openEditor(this->_d->_testCaseGraphicFile.fileName(),
                                                                    Core::Id(Constants::TESTCASEGRAPHIC_ID),
                                                                    Core::EditorManager::OpenInOtherSplit);
  Core::EditorManager::instance()->gotoOtherSplit();
  if(TestCaseGraphicEditor* testCaseGraphicEditor=qobject_cast<TestCaseGraphicEditor*>(editor))
  {
    TestCaseGraphicWidget* testCaseGraphicWidget=testCaseGraphicEditor->widget();
    this->_d->_testCaseGraphicWidget=testCaseGraphicWidget;
    renderTestCase();
  }

  return;
}

void TestCaseEditorWidget::renderTestCase()
{
  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  const DisTestRenderSettings *renderSettings;

  try
  {
    renderSettings = renderManager->renderSettingsFromTestCaseDocument(this->editorDocument()->fileName());
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
    return;
  }

  QString errorMessage;
  view::ts::ComRenderTestCase renderCommand(this->_d->_testCaseGraphicWidget->testCaseScene(),
                                            this->_d->_testCaseItem,
                                            renderSettings->testCaseSutCompOptions(),
                                            renderSettings->testCaseSutCompLifeLineColor(),
                                            renderSettings->testCaseSutCompLifeLineWidth(),
                                            renderSettings->testCaseTestCompOptions(),
                                            renderSettings->testCaseTestCompLifeLineColor(),
                                            renderSettings->testCaseTestCompLifeLineWidth(),
                                            renderSettings->testCaseSequItemOptions());
  bool result=renderCommand.execute(&errorMessage);
  if(!result)
  {
    Core::MessageManager::instance()->printToOutputPane(errorMessage,
                                                        Core::MessageManager::WithFocus);
    Core::MessageManager::instance()->showOutputPane();
  }

  return;
}

void TestCaseEditorWidget::globalTestCaseRenderSettingsChangedSignalHandlder(QString projectID)
{
  try
  {
    if (this->_d->_testCaseGraphicFile.exists())
    {
      DisTestRenderManager *renderManager = DisTestRenderManager::instance();
      QString myProjectID(renderManager->projectIDforTestCaseDocument(this->editorDocument()->fileName()));
      if (renderManager->isGlobalRendenSettingsUsed(myProjectID))
      {
        if ((projectID.isEmpty()) || (!projectID.compare(myProjectID)))
        {
          renderTestCase();
        }
      }
    }
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
  }
}

void TestCaseEditorWidget::customTestCaseRenderSettingsChangedSignalHandlder(QString projectID)
{
  try
  {
    if (this->_d->_testCaseGraphicFile.exists())
    {
      DisTestRenderManager *renderManager = DisTestRenderManager::instance();
      QString myProjectID(renderManager->projectIDforTestCaseDocument(this->editorDocument()->fileName()));
      if (!renderManager->isGlobalRendenSettingsUsed(myProjectID))
      {
        if ((projectID.isEmpty()) || (!projectID.compare(myProjectID)))
        {
          renderTestCase();
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
