#include "testreportbuilder.hpp"

#include <QTime>

#include "distestruntime/distestcase.hpp"
#include "distestruntime/distestruntime.hpp"
#include "distestruntime/distestresult.hpp"
#include "testreporttablemodel.hpp"

namespace distestproject {
using namespace distestruntime;

TestReportBuilder::TestReportBuilder(QObject* parent)
  : QObject(parent)
{
  _testSuiteModel = new TestReportTableModel(2);
  _statisticModel = new TestReportTableModel(2);
  _testCasesModel = new TestReportTableModel(4);
}

TestReportBuilder::~TestReportBuilder()
{
  delete _testSuiteModel;
  delete _statisticModel;
  delete _testCasesModel;
}

void TestReportBuilder::reset()
{
  if(this->_testSuiteModel)
    delete this->_testSuiteModel;
  if(this->_statisticModel)
    delete this->_statisticModel;
  if(this->_testCasesModel)
    delete this->_testCasesModel;

  this->_testSuiteModel=nullptr;
  this->_statisticModel=nullptr;
  this->_testCasesModel=nullptr;

  return;
}

void TestReportBuilder::buildReport(distestruntime::DisTestRuntime* disTestRuntime,
                                    QString* errorString)
{
  Q_UNUSED(errorString);
  Q_ASSERT(disTestRuntime);

  this->reset();

  this->_testSuiteModel = new TestReportTableModel(2);
  this->_statisticModel = new TestReportTableModel(2);
  this->_testCasesModel = new TestReportTableModel(4);

  _succeededCount = disTestRuntime->verdictTypeCount(DisTestResult::SUCCESS);
  _failedCount = disTestRuntime->verdictTypeCount(DisTestResult::FAIL);
  _excludetCount = disTestRuntime->verdictTypeCount(DisTestResult::EXCLUDE);
  _notExecuedCount = disTestRuntime->verdictTypeCount(DisTestResult::NOT_EXECUTED);

  //Fill the table models
  QVector<QVariant> temp;

  QString textColor = QString(QLatin1String("grey"));
  temp.append(QString(QLatin1String("<font color=\"%1\">Result:</font>")).arg(textColor));
  if(disTestRuntime->testRuntimeResult())
    temp.append(QLatin1String("<font color=\"green\">TestSuite successful!</font>"));
  else
    temp.append(QLatin1String("<font color=\"red\">TestSuite unsuccessful!</font>"));
  _testSuiteModel->pushBack(temp);
  temp.clear();

  temp.append(QString(QLatin1String("<font color=\"%1\">Start:</font>")).arg(textColor));
  const QDateTime st = disTestRuntime->startTime();
  temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + st.toString() + QLatin1String("</font>")));
  _testSuiteModel->pushBack(temp);
  temp.clear();

  temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + QLatin1String("End:") + QLatin1String("</font>")));
  const QDateTime et = disTestRuntime->endTime();
  temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + et.toString() + QLatin1String("</font>")));
  _testSuiteModel->pushBack(temp);
  temp.clear();

  temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + QLatin1String("TestCases:") + QLatin1String("</font>")));
  temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + QString::number(disTestRuntime->testCaseCount()) + QLatin1String("</font>")));
  _statisticModel->pushBack(temp);
  temp.clear();
  temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + QLatin1String("Executed:") + QLatin1String("</font>")));
  temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + QString::number(disTestRuntime->executedTestCaseCount()) + QLatin1String("</font>")));
  _statisticModel->pushBack(temp);
  temp.clear();
  temp.append(QVariant(QLatin1String("<font color=\"orange\">Not Executed:</font>") + QLatin1String("</font>")));
  temp.append(QVariant(QLatin1String("<font color=\"orange\">") + QString::number(disTestRuntime->verdictTypeCount(DisTestResult::NOT_EXECUTED)) + QLatin1String("</font>")));
  _statisticModel->pushBack(temp);
  temp.clear();
  temp.append(QVariant(QLatin1String("<font color=\"#00CD00\">Excluded:</font>")));
  temp.append(QVariant(QLatin1String("<font color=\"#00CD00\">") + QString::number(disTestRuntime->verdictTypeCount(DisTestResult::EXCLUDE)) + QLatin1String("</font>")));
  _statisticModel->pushBack(temp);
  temp.clear();
  temp.append(QVariant(QLatin1String("<font color=\"green\">Succeeded:</font>")));
  temp.append(QVariant(QLatin1String("<font color=\"green\">") + QString::number(disTestRuntime->verdictTypeCount(DisTestResult::SUCCESS)) + QLatin1String("</font>")));
  _statisticModel->pushBack(temp);
  temp.clear();
  temp.append(QVariant(QLatin1String("<font color=\"red\">Failed:</font>")));
  temp.append(QVariant(QLatin1String("<font color=\"red\">") + QString::number(disTestRuntime->verdictTypeCount(DisTestResult::FAIL)) + QLatin1String("</font>")));
  _statisticModel->pushBack(temp);
  temp.clear();

  int i = 1;
  for(DisTestCase *testCase : disTestRuntime->executedTestCases()){
    temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + QString::number(i) + QLatin1String("</font>")));
    switch(testCase->testResult().verdict()){
      case DisTestResult::SUCCESS:
        temp.append(QLatin1String("<font color=\"green\">Success</font>"));
        break;
      case DisTestResult::FAIL:
        temp.append(QLatin1String("<font color=\"red\">Failed</font>"));
        break;
      case DisTestResult::EXCLUDE:
        temp.append(QLatin1String("<font color=\"#00CD00\">Excluded</font>"));
        break;
      case DisTestResult::NOT_EXECUTED:
        temp.append(QLatin1String("<font color=\"orange\">Not Executed</font>"));
        break;
      default:
        temp.append(QLatin1String("<font color=\"red\">Error!</font>"));
    }
    temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + testCase->testCaseName() + QLatin1String("</font>")));
    temp.append(QVariant(QLatin1String("<font color=\"") + textColor + QLatin1String("\">") + testCase->testCaseFilePath() + QLatin1String("</font>")));
    _testCasesModel->pushBack(temp);
    temp.clear();
    i++;
  }
}

TestReportTableModel* TestReportBuilder::disTestRuntimeModel(){
  return _testSuiteModel;
}

TestReportTableModel* TestReportBuilder::statisticModel(){
  return _statisticModel;
}

TestReportTableModel* TestReportBuilder::testCasesModel(){
  return _testCasesModel;
}

int TestReportBuilder::getExcludetCount(){
  return _excludetCount;
}

int TestReportBuilder::getFailedCount(){
  return _failedCount;
}

int TestReportBuilder::getNotExecutedCount(){
  return _notExecuedCount;
}

int TestReportBuilder::getSucceededCount(){
  return _succeededCount;
}

}
