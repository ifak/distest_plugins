#include "distestruncontrol.hpp"

#include "distestruntime/distestruntime.hpp"
#include "distestruntime/distestcase.hpp"
#include "distestruntime/distestcomponent.hpp"

#include "distestrunconfiguration.hpp"
#include "distestprojectconstants.hpp"
#include "distestproject.hpp"
#include "distestbuildconfiguration.hpp"

#include <testcaseeditor/testcaseeditorconstants.hpp>
#include <testcaseeditor/testcaseeditor.hpp>
#include <testcaseeditor/testcaseeditorwidget.hpp>
#include <testcaseeditor/testcasegraphiceditor.hpp>
#include <testcaseeditor/testcasegraphicwidget.hpp>

/* test report */
#include "combuildtestreport.hpp"
#include "testreportgraphiceditor.hpp"
#include "testreportbuilder.hpp"
#include "testreporttablemodel.hpp"

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/messagemanager.h>

#include <projectexplorer/target.h>
#include <projectexplorer/task.h>
#include <projectexplorer/projectexplorer.h>

#include <mobata/model/ts/ts.hpp>
#include <graphlayout/mscquickwidget.hpp>
#include <testcaseeditor/testcasegraphiceditor.hpp>

#include <QIcon>
#include <QDate>
#include <QDebug>

/* test report */
#include <QQuickWidget>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>
#include <QTemporaryFile>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

typedef distestruntime::DisTestRuntime  DisTestRuntime;
typedef distestruntime::DisTestCase     DisTestCase;

///DisTestRunControl/////////////////////

class DisTestRunControl::Private : public QObject
{
  friend class DisTestRunControl;

  DisTestRuntime*   _disTestRuntime;
  DisTestCase*      _currentTestCase;
  graphlayout::MscQuickWidget* _currentTestCaseScene;
  TestReportBuilder _testReportBuilder;
  QFile             _testReportFile;
  bool              _isRunning;
  QIcon             _runControlIcon;

  Private(const QIcon& runControlIcon)
    : _disTestRuntime(nullptr),
      _currentTestCase(nullptr),
      _currentTestCaseScene(nullptr),
      _isRunning(false),
      _runControlIcon(runControlIcon)
  {}

  void showTestResult();
  void highlightIDEFeature(const QUuid& stepID,
                           const QColor& color,
                           qreal width);
};

void DisTestRunControl::Private::showTestResult()
{
  qDebug()<<"DisTestRunControl::Private::showTestResult() executed!";

  ProjectExplorer::Project*  startupProject=ProjectExplorer::ProjectExplorerPlugin::instance()->startupProject();
  DisTestProject* disTestProject=qobject_cast<DisTestProject*>(startupProject);
  if(disTestProject)
  {
    QString tempTestReportFile = QDir::tempPath();
    if (!tempTestReportFile.endsWith(QLatin1Char('/')))
      tempTestReportFile += QLatin1Char('/');
    tempTestReportFile += disTestProject->projectName()+ QLatin1String(".testreportgraphic");

    if(this->_testReportFile.exists())
    {
      this->_testReportFile.close();
      this->_testReportFile.rename(tempTestReportFile);
    }
    else
      this->_testReportFile.setFileName(tempTestReportFile);

    QTC_ASSERT(this->_testReportFile.open(QIODevice::ReadWrite), return;);
    this->_testReportFile.close();
    qDebug()<<"test report file: "<<this->_testReportFile.fileName();

    Core::EditorManager* editorManager = Core::EditorManager::instance();
    editorManager->removeAllSplits();
    Core::IEditor* editor = editorManager->openEditor(this->_testReportFile.fileName(),Constants::TESTREPORTGRAPHIC_ID);

    if(TestReportGraphicEditor* testReportGraphicEditor = qobject_cast<TestReportGraphicEditor*>(editor))
    {
      QQuickWidget* testReportGraphicWidget=qobject_cast<QQuickWidget*>(testReportGraphicEditor->widget());
      if(testReportGraphicWidget)
      {
        testReportGraphicWidget->engine()->clearComponentCache();

        this->_testReportBuilder.buildReport(this->_disTestRuntime);
        testReportGraphicWidget->engine()->rootContext()->setContextProperty(QStringLiteral("testCasesModel"),
                                                                             this->_testReportBuilder.testCasesModel());
        testReportGraphicWidget->engine()->rootContext()->setContextProperty(QStringLiteral("testSuiteModel"),
                                                                             this->_testReportBuilder.disTestRuntimeModel());
        testReportGraphicWidget->engine()->rootContext()->setContextProperty(QStringLiteral("statisticModel"),
                                                                             this->_testReportBuilder.statisticModel());
        testReportGraphicWidget->engine()->rootContext()->setContextProperty("handler",
                                                                             &this->_testReportBuilder);

        testReportGraphicWidget->setSource(QUrl(QStringLiteral("qrc:/distestproject/testreport/Testreport.qml")));

        testReportGraphicWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        testReportGraphicWidget->show();
        QQuickItem* rootItem = testReportGraphicWidget->rootObject();
        QObject::connect(this, &DisTestRunControl::Private::destroyed,
                         rootItem, &QQuickWidget::deleteLater);
      }
    }

    QJsonObject jsonObj;
    QJsonValue tcCount (this->_disTestRuntime->testCaseCount());
    QJsonValue tcExCount (this->_disTestRuntime->executedTestCaseCount());
    QJsonValue tcResult (this->_disTestRuntime->testRuntimeResult());
//    QJsonValue tcSucc (this->_disTestRuntime->succeededTestCases().length());
//    QJsonValue tcFail (this->_disTestRuntime->failedTestCases().length());
    jsonObj.insert("TestCaseCount", tcCount);
    jsonObj.insert("EndResult", tcResult);
    jsonObj.insert("ExecutedCount", tcExCount);
//    jsonObj.insert("SuccessCount", tcSucc);
//    jsonObj.insert("FailCount", tcFail);
    QJsonArray array;

    for(const distestproject::distestruntime::DisTestCase* tc : this->_disTestRuntime->executedTestCases()){
      QJsonObject tcObj;

      QJsonValue tcName (tc->testCaseName());
      QString thisUuid = tc->testCaseModel()->uuid().toString();
      thisUuid = thisUuid.mid(1,thisUuid.length()-2);
      QJsonValue tcUuid (thisUuid);
      QJsonValue tcRes (tc->testResult().toString());

      tcObj.insert("name", tcName);
      tcObj.insert("uuid", tcUuid);
      tcObj.insert("result", tcRes);

      QJsonValue tcValue(tcObj);
      array.append(tcValue);
    }
    jsonObj.insert("TestCases", array);
    QJsonDocument jsonDoc(jsonObj);

    QString jsonResultPath = disTestProject->activeTarget()->activeBuildConfiguration()->buildDirectory();
    QDir dir(jsonResultPath);
    if(!dir.exists()){
      bool createPath = dir.mkpath(jsonResultPath);
      if(!createPath){
        qDebug()<<"TestResult could not be saved at"<<jsonResultPath;
        return;
      }
    }
    if(jsonResultPath.right(1) != "/"){
      jsonResultPath = jsonResultPath + "/";
    }
    jsonResultPath = jsonResultPath + "Result_" + disTestProject->projectName() + ".json";
    QFile resFile(jsonResultPath);
    bool ok = resFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    if (ok){
      resFile.write(jsonDoc.toJson());
      resFile.close();
      qDebug()<<"TestResult saved at"<<jsonResultPath;
    }else{
      qDebug()<<"TestResult could not be saved at"<<jsonResultPath;
      return;
    }
  }

  return;
}

void DisTestRunControl::Private::highlightIDEFeature(const QUuid& stepID,
                                                     const QColor& color,
                                                     qreal width)
{
  Q_UNUSED(color)
  Q_UNUSED(width)
  qDebug()<< "DisTestRunControl::Private::highlightIDEFeature() executed!";

  if(this->_currentTestCaseScene)
  {
    this->_currentTestCaseScene->unhighlightAllGraphicItems();
    this->_currentTestCaseScene->highlightItemByUuid(stepID,true);
  }
  return;
}

DisTestRunControl::DisTestRunControl(DisTestRunConfiguration* disTestRunConfiguration,
                                     ProjectExplorer::RunMode mode,
                                     const QIcon& runControlIcon)
  : ProjectExplorer::RunControl(disTestRunConfiguration, mode),
    _d(new Private(runControlIcon))
{
  Q_ASSERT(disTestRunConfiguration);

  DisTestBuildConfiguration* disTestBC = qobject_cast<DisTestBuildConfiguration*>(disTestRunConfiguration
                                                                                  ->target()
                                                                                  ->activeBuildConfiguration());
  Q_ASSERT(disTestBC);

  this->_d->_disTestRuntime = disTestBC->disTestRuntime();
  Q_ASSERT(this->_d->_disTestRuntime);

  connect(this->_d->_disTestRuntime, &DisTestRuntime::currTestCase,
          this, &DisTestRunControl::currTestCaseSlot);
  connect(this->_d->_disTestRuntime, &DisTestRuntime::startTestCaseStep,
          this, &DisTestRunControl::startTestCaseStepSlot);
  connect(this->_d->_disTestRuntime, &DisTestRuntime::finishTestCaseStep,
          this, &DisTestRunControl::finishTestCaseStepSlot);
  connect(this->_d->_disTestRuntime, &DisTestRuntime::runtimeMessage,
          this, &DisTestRunControl::runtimeMessageSlot);
  connect(this->_d->_disTestRuntime, &DisTestRuntime::finished,
          this, &DisTestRunControl::finishedSlot);
}

DisTestRunControl::~DisTestRunControl()
{
  delete this->_d;
}

void DisTestRunControl::start()
{
  Q_ASSERT(this->_d->_disTestRuntime);

  emit started();

  QString errorMessage;
  bool result = this->_d->_disTestRuntime->setup(&errorMessage);
  if(!result)
  {
    qWarning()<<errorMessage;
    return;
  }

  this->_d->_isRunning=true;

  Core::EditorManager* editorManager = Core::EditorManager::instance();
  editorManager->removeAllSplits();
  for(Core::IEditor* otherEditor : editorManager->openedEditors()){
    editorManager->saveEditor(otherEditor);
    editorManager->closeEditors(QList<Core::IEditor *>() << otherEditor);
  }

  ProjectExplorer::RunConfiguration* runConfig=this->runConfiguration();
  Q_ASSERT(runConfig);
  Q_ASSERT(runConfig->target());

  ProjectExplorer::BuildConfiguration* buildConfig = runConfig->target()->activeBuildConfiguration();
  Q_ASSERT(buildConfig);
  DisTestBuildConfiguration* disTestBuildConfig = qobject_cast<DisTestBuildConfiguration*>(buildConfig);
  Q_ASSERT(disTestBuildConfig);
  disTestBuildConfig->setEnabled(false);

  DisTestRunConfiguration* disTestRunConfig = qobject_cast<DisTestRunConfiguration*>(this->runConfiguration());
  Q_ASSERT(disTestRunConfig);
  disTestRunConfig->setEnabled(false);

  result = this->_d->_disTestRuntime->start(&errorMessage);
  if(!result)
    qWarning()<<errorMessage;

  return;
}

DisTestRunControl::StopResult DisTestRunControl::stop()
{
  Q_ASSERT(this->_d->_disTestRuntime);

  QString errorMessage;
  bool result=this->_d->_disTestRuntime->stop(&errorMessage);
  if(!result)
  {
    qWarning()<<errorMessage;
    return StoppedSynchronously;
  }

  this->_d->_isRunning=false;
  emit finished();

  ProjectExplorer::RunConfiguration* runConfig=this->runConfiguration();
  Q_ASSERT(runConfig);
  Q_ASSERT(runConfig->target());

  ProjectExplorer::BuildConfiguration* buildConfig = runConfig->target()->activeBuildConfiguration();
  Q_ASSERT(buildConfig);
  DisTestBuildConfiguration* disTestBuildConfig = qobject_cast<DisTestBuildConfiguration*>(buildConfig);
  Q_ASSERT(disTestBuildConfig);
  disTestBuildConfig->setEnabled(true);

  DisTestRunConfiguration* disTestRunConfig = qobject_cast<DisTestRunConfiguration*>(this->runConfiguration());
  Q_ASSERT(disTestRunConfig);
  disTestRunConfig->setEnabled(true);

  return StoppedSynchronously;
}

bool DisTestRunControl::isRunning() const
{
  return this->_d->_isRunning;
}

QIcon DisTestRunControl::icon() const
{
  return this->_d->_runControlIcon;
}

void DisTestRunControl::currTestCaseSlot(DisTestCase* currTestCase)
{
  qDebug()<<"DisTestRunControl::currTestCaseSlot() executed!";

  if(!currTestCase)
    return;

  this->_d->_currentTestCase = currTestCase;

  Core::EditorManager* editorManager = Core::EditorManager::instance();

  //clear
  editorManager->removeAllSplits();
  editorManager->closeAllEditors(false);

  //open Editor
  qDebug()<< "TestName_:" << this->_d->_currentTestCase->testCaseFilePath();
  Core::IEditor* baseEditor = editorManager->openEditor(this->_d->_currentTestCase->testCaseFilePath());
  if(!baseEditor)
  {
      qDebug()<< "TestName_: editor nicht geöffnet";
  }
  editorManager->splitSideBySide();

  if(testcaseeditor::TestCaseEditor* testCaseEditor=qobject_cast<testcaseeditor::TestCaseEditor*>(baseEditor))
  {
    TextEditor::BaseTextEditorWidget* textEditorWidget=testCaseEditor->editorWidget();
    testcaseeditor::TestCaseEditorWidget* baseTestCaseTextEditorWidget=
        utils::simple_cast<testcaseeditor::TestCaseEditorWidget*>(textEditorWidget);
    Q_ASSERT(baseTestCaseTextEditorWidget);


    testcaseeditor::TestCaseGraphicEditor* testCaseGraphicEditor =
        dynamic_cast<testcaseeditor::TestCaseGraphicEditor*>(baseTestCaseTextEditorWidget->showTestCaseGraphic());
    this->_d->_currentTestCaseScene = dynamic_cast<graphlayout::MscQuickWidget*>(testCaseGraphicEditor);
  }

  return;
}

void DisTestRunControl::startTestCaseStepSlot(QUuid stepId,
                                              QString message)
{
  qDebug()<<"DisTestRunControl::startTestCaseStepSlot() executed!";

  this->_d->highlightIDEFeature(stepId, Qt::red, 4);

  QString currTimeString = QTime::currentTime().toString(QLatin1String("hh:mm:ss.zzz"));

  QString stepMessage = tr("start test case step: %1")
                        .arg(message);

  this->appendMessage(currTimeString
                      +QStringLiteral(": ")
                      +stepMessage
                      +QStringLiteral("\n"),
                      Utils::NormalMessageFormat);

  return;
}

void DisTestRunControl::finishTestCaseStepSlot(QUuid stepId,
                                               bool result,
                                               QString message)
{
  QString currTimeString = QTime::currentTime().toString(QLatin1String("hh:mm:ss.zzz"));

  model::msc::MscSequenceItem const* stepItem = this->_d->_currentTestCase->testCaseModel()->sequenceItem(stepId);
  QTC_ASSERT(stepItem, return);

  QString stepMessage = tr("finish test case step: '%1': '%2'")
                        .arg(stepItem->toString()).arg(message);

  if(result)
  {
    this->appendMessage(currTimeString
                        +QStringLiteral(": ")
                        +stepMessage
                        +QStringLiteral("\n"),
                        Utils::NormalMessageFormat);
    this->_d->highlightIDEFeature(stepId, Qt::darkGreen, 3);
  }
  else
  {
    this->appendMessage(currTimeString
                        +QStringLiteral(": ")
                        +stepMessage
                        +QStringLiteral("\n"),
                        Utils::ErrorMessageFormat);
    this->_d->highlightIDEFeature(stepId, Qt::red, 3);
  }

  return;
}

void DisTestRunControl::runtimeMessageSlot(bool success, QString message)
{
  qDebug()<<"DisTestRunControl::runtimeMessageSlot() executed!";

  QString currTimeString = QTime::currentTime().toString(QLatin1String("hh:mm:ss.zzz"));

  if(success)
  {
    this->appendMessage(currTimeString
                        + QStringLiteral(": ")
                        + message
                        + QStringLiteral("\n"),
                        Utils::NormalMessageFormat);
  }
  else
  {
    this->appendMessage(currTimeString
                        + QStringLiteral(": ")
                        + message
                        + QStringLiteral("\n"),
                        Utils::ErrorMessageFormat);
  }

  return;
}

void DisTestRunControl::componentRuntimeMessageSlot(distestruntime::DisTestComponent* disTestComponent,
                                                    bool success,
                                                    QString message)
{
  qDebug()<<"DisTestRunControl::componentRuntimeMessageSlot() executed!";
  Q_ASSERT(disTestComponent);

  QString currTimeString = QTime::currentTime().toString(QLatin1String("hh:mm:ss.zzz"));
  currTimeString += disTestComponent->name() + QStringLiteral(": ");

  if(success)
  {
    this->appendMessage(currTimeString
                        + QStringLiteral(": ")
                        + message
                        + QStringLiteral("\n"),
                        Utils::NormalMessageFormat);
  }
  else
  {
    this->appendMessage(currTimeString
                        + QStringLiteral(": ")
                        + message
                        + QStringLiteral("\n"),
                        Utils::ErrorMessageFormat);
  }

  return;
}


void DisTestRunControl::finishedSlot(bool result, QString message)
{
  qDebug()<<"DisTestRunControl::finishedSlot() executed!";

  Core::EditorManager* editorManager = Core::EditorManager::instance();
  QList<Core::IEditor*> currentEditorList = editorManager->editorsForFileName(this->_d->_testReportFile.fileName());
  Core::IEditor* currentEditor = nullptr;
  if(!currentEditorList.isEmpty()){
    currentEditor = currentEditorList.first();
  }
  for(Core::IEditor* otherEditor : editorManager->openedEditors()){
    if(otherEditor != currentEditor){
      editorManager->closeEditors(QList<Core::IEditor *>() << otherEditor);
    }
  }

  QString currTimeString = QTime::currentTime().toString(QLatin1String("hh:mm:ss.zzz"));

  if(result)
    this->appendMessage(currTimeString
                        + QStringLiteral(": ")
                        + message
                        +QStringLiteral("\n"),
                        Utils::NormalMessageFormat);
  else
    this->appendMessage(currTimeString
                        + QStringLiteral(": ")
                        + message
                        +QStringLiteral("\n"),
                        Utils::ErrorMessageFormat);

  emit finished();
  this->_d->_isRunning=false;

  ProjectExplorer::RunConfiguration* runConfig=this->runConfiguration();
  Q_ASSERT(runConfig);
  Q_ASSERT(runConfig->target());

  ProjectExplorer::BuildConfiguration* buildConfig = runConfig->target()->activeBuildConfiguration();
  Q_ASSERT(buildConfig);
  DisTestBuildConfiguration* disTestBuildConfig = qobject_cast<DisTestBuildConfiguration*>(buildConfig);
  Q_ASSERT(disTestBuildConfig);
  disTestBuildConfig->setEnabled(true);

  DisTestRunConfiguration* disTestRunConfig = qobject_cast<DisTestRunConfiguration*>(this->runConfiguration());
  Q_ASSERT(disTestRunConfig);
  disTestRunConfig->setEnabled(true);

  this->_d->showTestResult();

  return;
}

///DisTestRunControlFactory/////////////////////
class DisTestRunControlFactory::Private
{
  friend class DisTestRunControlFactory;

  const Core::Id _runId;

  Private(const Core::Id& runId)
    : _runId(runId)
  {}
};

DisTestRunControlFactory::DisTestRunControlFactory(const Core::Id& runId,
                                                   QObject* parent)
  : ProjectExplorer::IRunControlFactory(parent),
    _d(new Private(runId))
{}

DisTestRunControlFactory::~DisTestRunControlFactory()
{
  delete this->_d;
}

bool DisTestRunControlFactory::canRun(ProjectExplorer::RunConfiguration* runConfiguration,
                                      ProjectExplorer::RunMode mode) const
{
  Q_ASSERT(runConfiguration);

  if(runConfiguration->id()==this->_d->_runId
     && mode == ProjectExplorer::NormalRunMode)
    return true;

  return false;
}

DisTestRunControl* DisTestRunControlFactory::create(ProjectExplorer::RunConfiguration* runConfiguration,
                                                    ProjectExplorer::RunMode mode,
                                                    QString* errorMessage)
{
  Q_ASSERT(runConfiguration);

  if(!this->canRun(runConfiguration, mode))
  {
    if(errorMessage)
      *errorMessage+=tr("run-configuration '%1' cannot be handled "
                        "by this test system!").arg(runConfiguration->displayName());
    return nullptr;
  }

  DisTestRunConfiguration* disTestRunConfig=qobject_cast<DisTestRunConfiguration*>(runConfiguration);
  if(!disTestRunConfig)
  {
    if(errorMessage)
      *errorMessage+=tr("run-configuration '%1' is not an "
                        "dis-test run configuration!").arg(runConfiguration->displayName());
    return nullptr;
  }

  DisTestBuildConfiguration* disTestBC = qobject_cast<DisTestBuildConfiguration*>(disTestRunConfig
                                                                                  ->target()
                                                                                  ->activeBuildConfiguration());
  if(!disTestBC)
  {
    if(errorMessage)
      *errorMessage+=tr("dis-test-run-configuration '%1' has no dis-test build configuration!")
                     .arg(runConfiguration->displayName());
    return nullptr;
  }

  if(!disTestBC->disTestRuntime())
  {
    if(errorMessage)
      *errorMessage += tr("there is no dis-test-runtime available. please build your project first!");

    return nullptr;
  }

  return this->createRunControl(disTestRunConfig, mode, errorMessage);
}

} // namespace distestproject

