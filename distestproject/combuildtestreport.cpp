#include "combuildtestreport.hpp"

#include "distestruntime/distestruntime.hpp"
#include "distestruntime/distestcase.hpp"

#include <app/app_version.h>

#include <QDateTime>
#include <QHostInfo>
#include <QThread>
#include <QFileInfo>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

using namespace distestruntime;



class ComBuildTestReport::Private
{
  friend class ComBuildTestReport;

  DisTestRuntime* _disTestRuntime;

  Private(DisTestRuntime* disTestRuntime)
    : _disTestRuntime(disTestRuntime)
  {}

private:
  QString createHtml();
  QString createHead();
  QString createSyle();
  QString createBody();

  QString createTableSummary();
  QString createTableStatistic();
  QString createTableInfo();
  QString createTableEntry(const QString &name, const QString &value, const QString &addinfo = QStringLiteral(""));

  QString createTableTestCase();
  QString createTableTestCaseEntry(int num, DisTestResult::Verdict result, const QString &testCaseName, const QString &fileName);

  QString tr(const QString &str, const QString& addinfo = QStringLiteral(""));
  QString td(const QString &str, const QString& addinfo = QStringLiteral(""));
  QString th(const QString &str, const QString& addinfo = QStringLiteral(""));
  QString legend(const QString &str, const QString& addinfo = QStringLiteral(""));
  QString createElement(const QString &str, const QString &sign, const QString& addinfo = QStringLiteral(""));

  QString attClass(const QString& value);
  QString att(const QString& name, const QString& value);
};

QString ComBuildTestReport::Private::createHtml()
{
  QString ht;
  ht+= QLatin1String("\n");
  ht+= QLatin1String("<html>");
  ht+= createHead();
  ht+= createBody();
  ht+= QLatin1String("</html>");
  return ht;
}

QString ComBuildTestReport::Private::createHead()
{
  QString ht;
  ht+= QLatin1String("\n");
  ht+= QLatin1String("<head>");
  ht+=QLatin1String("<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=iso-8859-1\">");
  ht+= QLatin1String("<title>ifak e.V. Magdeburg</title>");
  ht+= QLatin1String("\n");
  ht+= createSyle();
  ht+= QLatin1String("\n");
  ht+=QLatin1String("<script type=\"text/javascript\">\n");
  ht+=QLatin1String("function showInfo() {\n");
  ht+=QLatin1String("document.getElementById(\"info\").style.display = 'block';\n");
  ht+=QLatin1String("document.getElementById(\"grayout\").style.display = 'block';\n");
  ht+=QLatin1String("}\n");
  ht+=QLatin1String("function closeInfo() {\n");
  ht+=QLatin1String("document.getElementById(\"info\").style.display = 'none';\n");
  ht+=QLatin1String("document.getElementById(\"grayout\").style.display = 'none';\n");
  ht+=QLatin1String("}\n");
  ht+=QLatin1String("</script>\n");
  ht+= QLatin1String("</head>");
  return ht;
}

QString ComBuildTestReport::Private::createSyle()
{
  QString ht;
  ht+= QLatin1String("\n");
  ht+= QLatin1String("<style>");

  ht+=QLatin1String("#header {\n");
  ht+=QLatin1String("width: 100%;\n");
  ht+=QLatin1String("min-height: 60px;\n");
  ht+=QLatin1String("padding: 10px;\n");
  ht+=QLatin1String("background-color: #31859c;\n");
  ht+=QLatin1String("color: white;\n");
  ht+=QLatin1String("font: bold 24pt Arial;\n");
  ht+=QLatin1String("border-bottom: solid 5px #c0504d;\n");
  ht+=QLatin1String("-webkit-box-sizing: border-box;\n");
  ht+=QLatin1String("-moz-box-sizing: border-box;\n");
  ht+=QLatin1String("box-sizing: border-box;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#description {\n");
  ht+=QLatin1String("  font: bold 18pt Arial;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#main-content {\n");
  ht+=QLatin1String("  width: 100%;\n");
  ht+=QLatin1String("  margin-left: 0px;\n");
  ht+=QLatin1String("  text-color: black;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#summary-content {\n");
  ht+=QLatin1String("float: left;\n");
  ht+=QLatin1String("min-height: 170px;\n");
  ht+=QLatin1String("padding: 10px;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#statistic-content {\n");
  ht+=QLatin1String("min-height: 170px;\n");
  ht+=QLatin1String("padding: 10px;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#testcases-content {\n");
  ht+=QLatin1String("clear: left;\n");
  ht+=QLatin1String("min-height: 170px;\n");
  ht+=QLatin1String("padding-left: 10px;\n");
  ht+=QLatin1String("padding-top: 0px;\n");
  ht+=QLatin1String("padding-right: 10px;\n");
  ht+=QLatin1String("padding-bottom: 10px;\n");
  ht+=QLatin1String("}\n");

      ht+=QLatin1String("#environment-content {\n");
  ht+=QLatin1String("  position: absolute;\n");
  ht+=QLatin1String("  width: 300px;\n");
  ht+=QLatin1String("  height: 170px;\n");
  ht+=QLatin1String("  left: 740px;\n");
  ht+=QLatin1String("  top: 0px;\n");
  ht+=QLatin1String("  margin: 10px;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".legend {\n");
  ht+=QLatin1String("  font: bold 13pt Times;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("td {\n");
  ht+=QLatin1String("  font: normal 12pt Times;\n");
  ht+=QLatin1String("}\n");
  ht+=QLatin1String("td:first-child {\n");
  ht+=QLatin1String("  font-weight: bold;\n");
  ht+=QLatin1String("  text-align: right;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("td:last-child {\n");
  ht+=QLatin1String("  padding-left: 10px;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#summary-content>fieldset>table>tbody>tr>td:last-child {\n");
  ht+=QLatin1String("  padding-right: 30px;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".testcases {\n");
  ht+=QLatin1String("  border-collapse: collapse;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".testcases>tbody>tr {\n");
  ht+=QLatin1String("  cursor: pointer;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".testcases>tbody>tr:nth-child(even) {\n");
  ht+=QLatin1String("  background-color: f0f0f0;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".testcases>tbody>tr:hover {\n");
  ht+=QLatin1String("  background-color: 87b2cc;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".testcases>tbody>tr:first-child:hover {\n");
  ht+=QLatin1String("  background-color: white;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".testcases>tbody>tr>td {\n");
  ht+=QLatin1String("  padding-left: 20px;\n");
  ht+=QLatin1String("  padding-bottom: 3px;\n");
  ht+=QLatin1String("  font-weight: normal;\n");
  ht+=QLatin1String("  text-align: left;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".testcases>tbody>tr>th {\n");
  ht+=QLatin1String("  padding-left: 20px;\n");
  ht+=QLatin1String("  text-align: left;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".success {\n");
  ht+=QLatin1String("  color: green;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String(".failure {\n");
  ht+=QLatin1String("  color: red;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#impressum-container {\n");
  ht+=QLatin1String("  width: 100%;\n");
  ht+=QLatin1String("  height: 25px;\n");
  ht+=QLatin1String("  background-color: #d0d0d0;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#impressum {\n");
  ht+=QLatin1String("  color: #808080;\n");
  ht+=QLatin1String("  display: table;\n");
  ht+=QLatin1String("  margin: 0 auto;\n");
  ht+=QLatin1String("  padding: 3px;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#impressum>a {\n");
  ht+=QLatin1String("  color: #808080;\n");
  ht+=QLatin1String("  text-decoration: none;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#impressum>a:hover {\n");
  ht+=QLatin1String("  text-decoration: underline;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#info {\n");
  ht+=QLatin1String("  display: none;\n");
  ht+=QLatin1String("  position: absolute;\n");
  ht+=QLatin1String("  left: 200px;\n");
  ht+=QLatin1String("  top: 200px;\n");
  ht+=QLatin1String("  width: 300px;\n");
  ht+=QLatin1String("  height: 150px;\n");
  ht+=QLatin1String("  border-radius: 5px;\n");
  ht+=QLatin1String("  background-color: #f0f0f0;\n");
  ht+=QLatin1String("  border: solid 1px black;\n");
  ht+=QLatin1String("  box-shadow: 5px 5px 5px grey;\n");
  ht+=QLatin1String("  padding: 5px;\n");
  ht+=QLatin1String("  z-index: 100;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#error-location {\n");
  ht+=QLatin1String("  cursor: pointer;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#error-location:hover {\n");
  ht+=QLatin1String("  background-color: 87b2cc;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("#grayout {\n");
  ht+=QLatin1String("  position: fixed;\n");
  ht+=QLatin1String("  left: 0px;\n");
  ht+=QLatin1String("  top: 0px;\n");
  ht+=QLatin1String("  height: 100%;\n");
  ht+=QLatin1String("  width: 100%;\n");
  ht+=QLatin1String("  background-color: black;\n");
  ht+=QLatin1String("  opacity: 0.5;\n");
  ht+=QLatin1String("  z-index: 99;\n");
  ht+=QLatin1String("}\n");

  ht+=QLatin1String("body {\n");
  ht+=QLatin1String("margin: 0px;\n");
  ht+=QLatin1String("}\n");


  ht+=QLatin1String("</style>");
  return ht;
}

QString ComBuildTestReport::Private::createBody()
{
  QString ht;
  ht+=QLatin1String("\n");
  ht+=QLatin1String("<body>");
  ht+=QLatin1String("\n");
  ht+=QLatin1String("<!-- Für ausgegrauten Hintergrund bei Info-Anzeige -->\n");
  ht+=QLatin1String("<div id=\"grayout\" style=\"display: none;\"></div>\n");
  ht+= createTableInfo();
  ht+=QLatin1String("<!-- Header -->\n");
  ht+=QLatin1String("<div id=\"header\">Testrun Result Overview <font id=\"description\">- ")
      + this->_disTestRuntime->testSuiteName()
      + QLatin1String("</font></div>\n");
  ht+=QLatin1String("\n");
  ht+=QLatin1String("<!-- Main-Fenster -->\n");
  ht+=QLatin1String("<div id=\"main-content\">\n");
  ht+= createTableSummary();
  ht+= createTableStatistic();
  ht+= createTableTestCase();
  ht+=QLatin1String("\n");
  ht+= QLatin1String("</div>\n");
  ht+=QLatin1String("</body>");
  ht+=QLatin1String("\n");

  return ht;
}

QString ComBuildTestReport::Private::createTableSummary()
{
  QString ht;
  bool result = true;
  if(this->_disTestRuntime->testSuiteResult() == false)
  {
    result = false;
  }

  ht+=QLatin1String("\n<!-- Summary -->");
  ht+=QLatin1String("\n<div id=\"summary-content\">");
  ht+=QLatin1String("\n  <fieldset>\n");
  ht+= legend(QLatin1String("Test Suite"), attClass(QLatin1String("legend")));
  ht+=QLatin1String("\n    <table border=\"0\">");
  ht+= createTableEntry(QLatin1String("Result:"),
                        result ? QLatin1String("TestSuite successful!") : QLatin1String("TestSuite failed!"),
                        result ? attClass(QLatin1String("success")) : attClass(QLatin1String("failure")));
  ht+= createTableEntry(QLatin1String("Start:"),
                        this->_disTestRuntime->startTime().toString(QLatin1String("hh:mm:ss")));
  ht+= createTableEntry(QLatin1String("End:"),
                        this->_disTestRuntime->endTime().toString(QLatin1String("hh:mm:ss")));

  if(result == false)
  {
    QVector<DisTestCase*> tcList = this->_disTestRuntime->failedTestCases();
    if(!tcList.isEmpty())
    {
      ht+= createTableEntry(QLatin1String("Error:"),
                            QLatin1String("TestCase: ") + tcList.first()->testCaseName());
      ht+= createTableEntry(QLatin1String("Description:"), tcList.first()->testResult().errorMessage());
    }
  }
  ht+=QLatin1String("    </table>\n");
  ht+=QLatin1String("  </fieldset>\n");
  ht+=QLatin1String("</div>\n");
  return ht;
}

QString ComBuildTestReport::Private::createTableEntry(const QString& name, const QString& value, const QString& addinfo)
{
  QString ht;
  ht+=QLatin1String("\n");
  ht += tr(td(name) + td(value, addinfo));
  return ht;
}

QString ComBuildTestReport::Private::createTableStatistic()
{
  QString ht;

  ht+=QLatin1String("\n");
  ht+=QLatin1String("<!-- Statistics -->\n");
  ht+=QLatin1String("<div id=\"statistic-content\">\n");
  ht+=QLatin1String("  <fieldset>\n");
  ht+= legend(QLatin1String("Statistic"), attClass(QLatin1String("legend")));
  ht+=QLatin1String("    <table border=\"0\">\n");
  ht+= createTableEntry(QLatin1String("TestCases:"), QString::number(this->_disTestRuntime->testCaseCount()));
  ht+= createTableEntry(QLatin1String("Executed:"),QString::number(this->_disTestRuntime->executedTestCaseCount()));
  ht+= createTableEntry(QLatin1String("Excluded:"), QString::number(this->_disTestRuntime->verdictTypeCount(DisTestResult::EXCLUDE)));
  ht+= createTableEntry(QLatin1String("Succeeded:"), QString::number(this->_disTestRuntime->verdictTypeCount(DisTestResult::SUCCESS)));
  ht+= createTableEntry(QLatin1String("Failed:"), QString::number(this->_disTestRuntime->verdictTypeCount(DisTestResult::FAIL)));
  ht+=QLatin1String("\n    </table>");
  ht+=QLatin1String("\n  </fieldset>");
  ht+=QLatin1String("\n</div>");
  return ht;
}

QString ComBuildTestReport::Private::createTableInfo()
{
  QString ht;

  ht+= QLatin1String("\n");
  ht+= QLatin1String("<!-- Info-Anzeige-->\n");
  ht+= QLatin1String("<div id=\"info\">\n");
  ht+= QLatin1String("<table border=\"0\" width=\"100%\">\n");
  ht+= QLatin1String("<tr><td>&nbsp;</td><td align=\"right\"><div title='Fenster schließen' style=\""
                     "text-align: center; width: 22px; heigth: 22px; "
                     "font: bold 16pt Arial; color: white; border: solid 1px black; "
                     "background-color: e1988c; cursor: pointer; padding; 2px; "
                     "border-radius: 3px;\" onClick=\"closeInfo()\">x</div></td></tr>\n");
  ht+= createTableEntry(QLatin1String("MachineName:"),QHostInfo::localHostName());
  ht+= createTableEntry(QLatin1String("Operating system:"),QSysInfo::prettyProductName());
  ht+= createTableEntry(QLatin1String(Core::Constants::IDE_APP_NAME)
                        + QLatin1String(":"),
                        QLatin1String(Core::Constants::IDE_VERSION_LONG));
  ht+= createTableEntry(QLatin1String("Company:"),
                        QLatin1String(Core::Constants::IDE_AUTHOR));
  ht+= createTableEntry(QLatin1String("&nbsp;"),
                        QLatin1String("&nbsp;"));
  ht+= QLatin1String("</table>\n");
  ht+= QLatin1String("</div>\n");
  return ht;
}

QString ComBuildTestReport::Private::createTableTestCase()
{
  QString ht;

  ht+= QLatin1String("\n");
  ht+= QLatin1String("<!-- Test Cases und Impressum -->\n");
  ht+= QLatin1String("<div id=\"testcases-content\">\n");
  ht+= QLatin1String("  <fieldset>\n");
  ht+= legend(QLatin1String("Test Cases"),
              attClass(QLatin1String("legend")));
  ht+= QLatin1String("    <table class=\"testcases\" border=\"0\">\n");
  ht+= QLatin1String("\n")
       + tr(th(QLatin1String("No"))
            + th(QLatin1String("Result"))
            + th(QLatin1String("Name"))
            + th(QLatin1String("File Name")));
  int i=0;
  foreach(DisTestCase* tc, this->_disTestRuntime->executedTestCases())
  {
    ht+= createTableTestCaseEntry(++i,
                                  tc->testResult().verdict(),
                                  tc->testCaseName(),
                                  QFileInfo(tc->testCaseFilePath()).fileName());
  }
  ht+= QLatin1String("\n    </table>");
  ht+= QLatin1String("\n  </fieldset>");
  ht+= QLatin1String("\n <br/>");
  ht+= QLatin1String("\n <div id=\"impressum-container\"><font id=\"impressum\">")
       + QString::number(QDate::currentDate().year())
       + QLatin1String(" <a href=\"http://www.ifak.eu\" target=\"blank\">ifak e.V. Magdeburg</a>&nbsp; |&nbsp; "
                       "<a href=\"javascript:showInfo()\">Info</a></font></div>");

  ht+= QLatin1String("\n</div>");
  return ht;
}

QString ComBuildTestReport::Private::createTableTestCaseEntry(int num,
                                                              DisTestResult::Verdict result,
                                                              const QString& testCaseName,
                                                              const QString& fileName)
{
  QString ht;
  ht+= QLatin1String("\n");
  QString color(QLatin1String(""));
  QString resultStr(QLatin1String(""));
  switch (result)
  {
    case DisTestResult::FAIL:
      color = attClass(QLatin1String("failure"));
      resultStr = QLatin1String("Failure");
      break;
    case DisTestResult::SUCCESS:
      color = attClass(QLatin1String("success"));
      resultStr = QLatin1String("Success");
      break;
    default:
      break;
  }
  ht+= tr(td(QString::number(num)) + td(resultStr, color) + td(testCaseName) + td(fileName));
  return ht;
}


QString ComBuildTestReport::Private::tr(const QString& str, const QString&  addinfo)
{
  return createElement(str, QLatin1String("tr"), addinfo);
}

QString ComBuildTestReport::Private::td(const QString& str, const QString& addinfo)
{
  return createElement(str, QLatin1String("td"), addinfo);
}

QString ComBuildTestReport::Private::th(const QString& str, const QString& addinfo)
{
  return createElement(str, QLatin1String("th"), addinfo);
}

QString ComBuildTestReport::Private::legend(const QString& str, const QString& addinfo)
{
  return createElement(str, QLatin1String("legend"), addinfo);
}

QString ComBuildTestReport::Private::createElement(const QString& str,
                                                   const QString& sign,
                                                   const QString& addInfo)
{
  return (QLatin1String("<")+ sign
          + QLatin1String(" ") + addInfo
          + QLatin1String(">") + str
          + QLatin1String("</")
          + sign
          + QLatin1String(">"));
}

QString ComBuildTestReport::Private::attClass(const QString& value)
{
  return att(QLatin1String("class"), value);
}

QString ComBuildTestReport::Private::att(const QString& name, const QString& value)
{
  return name + QLatin1String(" =\"") + value + QLatin1String("\"");
}

//////////ComBuildTestReport/////////////////////////
ComBuildTestReport::ComBuildTestReport(DisTestRuntime* disTestRuntime)
  : _d(new Private(disTestRuntime))
{}

ComBuildTestReport::~ComBuildTestReport()
{
  delete this->_d;
}

QString ComBuildTestReport::execute()
{
  QString html;
  html+= QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
  html+= this->_d->createHtml();
  return html;
}



} // namespace distestproject
