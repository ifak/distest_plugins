#include "distestconfiguration.hpp"
#include "globalrendersettings.hpp"
#include "distestproject.hpp"

#include "distestrendermanager.hpp"
#include "distestrendersettings.hpp"

#include <stdexcept>
#include <QDebug>

static const QLatin1String kUseGlobal("DisTestConfiguration.UseGlobal");

static const QLatin1String kSutCompTextFontName("DisTestConfiguration.SUT.CompTextFontName");
static const QLatin1String kSutCompTextFontSize("DisTestConfiguration.SUT.CompTextFontSize");
static const QLatin1String kSutCompTextFontBold("DisTestConfiguration.SUT.CompTextFontBold");
static const QLatin1String kSutCompTextFontItalic("DisTestConfiguration.SUT.CompTextFontItalic");
static const QLatin1String kSutCompTextColorName("DisTestConfiguration.SUT.CompTextColorName");
static const QLatin1String kSutCompBoxWidth("DisTestConfiguration.SUT.CompBoxWidth");
static const QLatin1String kSutCompBoxHeight("DisTestConfiguration.SUT.CompBoxHeight");
static const QLatin1String kSutCompBoxColorName("DisTestConfiguration.SUT.CompBoxColorName");
static const QLatin1String kSutCompBorderWidth("DisTestConfiguration.SUT.CompBorderWidth");
static const QLatin1String kSutCompBorderColorName("DisTestConfiguration.SUT.CompBorderColorName");
static const QLatin1String kSutPortBoxWidth("DisTestConfiguration.SUT.PortBoxWidth");
static const QLatin1String kSutPortBoxHeight("DisTestConfiguration.SUT.PortBoxHeight");
static const QLatin1String kSutPortBoxColorName("DisTestConfiguration.SUT.PortBoxColorName");
static const QLatin1String kSutPortBorderWidth("DisTestConfiguration.SUT.PortBorderWidth");
static const QLatin1String kSutPortBorderColorName("DisTestConfiguration.SUT.PortBorderColorName");
static const QLatin1String kSutLinkLineWidth("DisTestConfiguration.SUT.LinkLineWidth");
static const QLatin1String kSutLinkLineColorName("DisTestConfiguration.SUT.LinkLineColorName");
static const QLatin1String kSutBoxColorName("DisTestConfiguration.SUT.SutBoxColorName");
static const QLatin1String kSutBoxCompMargin("DisTestConfiguration.SUT.SutBoxCompMargin");
static const QLatin1String kSutBoxMargin("DisTestConfiguration.SUT.SutBoxMargin");
static const QLatin1String kSutBoxRadius("DisTestConfiguration.SUT.SutBoxRadius");

static const QLatin1String kTsCompTextFontName("DisTestConfiguration.TestSystem.CompTextFontName");
static const QLatin1String kTsCompTextFontSize("DisTestConfiguration.TestSystem.CompTextFontSize");
static const QLatin1String kTsCompTextFontBold("DisTestConfiguration.TestSystem.CompTextFontBold");
static const QLatin1String kTsCompTextFontItalic("DisTestConfiguration.TestSystem.CompTextFontItalic");
static const QLatin1String kTsCompTextColorName("DisTestConfiguration.TestSystem.CompTextColorName");
static const QLatin1String kTsCompBoxWidth("DisTestConfiguration.TestSystem.CompBoxWidth");
static const QLatin1String kTsCompBoxHeight("DisTestConfiguration.TestSystem.CompBoxHeight");
static const QLatin1String kTsCompBoxColorName("DisTestConfiguration.TestSystem.CompBoxColorName");
static const QLatin1String kTsCompBorderWidth("DisTestConfiguration.TestSystem.CompBorderWidth");
static const QLatin1String kTsCompBorderColorName("DisTestConfiguration.TestSystem.CompBorderColorName");
static const QLatin1String kTsPortBoxWidth("DisTestConfiguration.TestSystem.PortBoxWidth");
static const QLatin1String kTsPortBoxHeight("DisTestConfiguration.TestSystem.PortBoxHeight");
static const QLatin1String kTsPortBoxColorName("DisTestConfiguration.TestSystem.PortBoxColorName");
static const QLatin1String kTsPortBorderWidth("DisTestConfiguration.TestSystem.PortBorderWidth");
static const QLatin1String kTsPortBorderColorName("DisTestConfiguration.TestSystem.PortBorderColorName");
static const QLatin1String kTsLinkLineWidth("DisTestConfiguration.TestSystem.LinkLineWidth");
static const QLatin1String kTsLinkLineColorName("DisTestConfiguration.TestSystem.LinkLineColorName");
static const QLatin1String kTsSpaceToSutBox("DisTestConfiguration.TestSystem.SpaceToSutBox");
static const QLatin1String kTsBoxTextFontName("DisTestConfiguration.TestSystem.TsBoxTextFontName");
static const QLatin1String kTsBoxTextFontSize("DisTestConfiguration.TestSystem.TsBoxTextFontSize");
static const QLatin1String kTsBoxTextFontBold("DisTestConfiguration.TestSystem.TsBoxTextFontBold");
static const QLatin1String kTsBoxTextFontItalic("DisTestConfiguration.TestSystem.TsBoxTextFontItalic");
static const QLatin1String kTsBoxTextColorName("DisTestConfiguration.TestSystem.TsBoxTextColorName");
static const QLatin1String kTsBoxBoxWidth("DisTestConfiguration.TestSystem.TsBoxBoxWidth");
static const QLatin1String kTsBoxBoxHeight("DisTestConfiguration.TestSystem.TsBoxBoxHeight");
static const QLatin1String kTsBoxBoxColorName("DisTestConfiguration.TestSystem.TsBoxBoxColorName");
static const QLatin1String kTsBoxBorderWidth("DisTestConfiguration.TestSystem.TsBoxBorderWidth");
static const QLatin1String kTsBoxBorderColorName("DisTestConfiguration.TestSystem.TsBoxBorderColorName");
static const QLatin1String kTsBoxMargin("DisTestConfiguration.TestSystem.TsBoxMargin");
static const QLatin1String kTsBoxRadius("DisTestConfiguration.TestSystem.TsBoxRadius");

static const QLatin1String kTcSutCompTextFontName("DisTestConfiguration.TestCase.SutCompTextFontName");
static const QLatin1String kTcSutCompTextFontSize("DisTestConfiguration.TestCase.SutCompTextFontSize");
static const QLatin1String kTcSutCompTextFontBold("DisTestConfiguration.TestCase.SutCompTextFontBold");
static const QLatin1String kTcSutCompTextFontItalic("DisTestConfiguration.TestCase.SutCompTextFontItalic");
static const QLatin1String kTcSutCompTextColorName("DisTestConfiguration.TestCase.SutCompTextColorName");
static const QLatin1String kTcSutCompBoxWidth("DisTestConfiguration.TestCase.SutCompBoxWidth");
static const QLatin1String kTcSutCompBoxHeight("DisTestConfiguration.TestCase.SutCompBoxHeight");
static const QLatin1String kTcSutCompBoxColorName("DisTestConfiguration.TestCase.SutCompBoxColorName");
static const QLatin1String kTcSutCompBorderWidth("DisTestConfiguration.TestCase.SutCompBorderWidth");
static const QLatin1String kTcSutCompBorderColorName("DisTestConfiguration.TestCase.SutCompBorderColorName");
static const QLatin1String kTcSutLifeLineWidth("DisTestConfiguration.TestCase.SutCompLifeLineWidth");
static const QLatin1String kTcSutLifeLineColorName("DisTestConfiguration.TestCase.SutCompLifeLineColorName");
static const QLatin1String kTcTestCompTextFontName("DisTestConfiguration.TestCase.TestCompTextFontName");
static const QLatin1String kTcTestCompTextFontSize("DisTestConfiguration.TestCase.TestCompTextFontSize");
static const QLatin1String kTcTestCompTextFontBold("DisTestConfiguration.TestCase.TestCompTextFontBold");
static const QLatin1String kTcTestCompTextFontItalic("DisTestConfiguration.TestCase.TestCompTextFontItalic");
static const QLatin1String kTcTestCompTextColorName("DisTestConfiguration.TestCase.TestCompTextColorName");
static const QLatin1String kTcTestCompBoxWidth("DisTestConfiguration.TestCase.TestCompBoxWidth");
static const QLatin1String kTcTestCompBoxHeight("DisTestConfiguration.TestCase.TestCompBoxHeight");
static const QLatin1String kTcTestCompBoxColorName("DisTestConfiguration.TestCase.TestCompBoxColorName");
static const QLatin1String kTcTestCompBorderWidth("DisTestConfiguration.TestCase.TestCompBorderWidth");
static const QLatin1String kTcTestCompBorderColorName("DisTestConfiguration.TestCase.TestCompBorderColorName");
static const QLatin1String kTcTestLifeLineWidth("DisTestConfiguration.TestCase.TestCompLifeLineWidth");
static const QLatin1String kTcTestLifeLineColorName("DisTestConfiguration.TestCase.TestCompLifeLineColorName");
static const QLatin1String kTcSequItemTextFontName("DisTestConfiguration.TestCase.SequItemTextFontName");
static const QLatin1String kTcSequItemTextFontSize("DisTestConfiguration.TestCase.SequItemTextFontSize");
static const QLatin1String kTcSequItemTextFontBold("DisTestConfiguration.TestCase.SequItemTextFontBold");
static const QLatin1String kTcSequItemTextFontItalic("DisTestConfiguration.TestCase.SequItemTextFontItalic");
static const QLatin1String kTcSequItemTextColorName("DisTestConfiguration.TestCase.SequItemTextColorName");
static const QLatin1String kTcSequItemLineWidth("DisTestConfiguration.TestCase.SequItemLineWidth");
static const QLatin1String kTcSequItemLineColorName("DisTestConfiguration.TestCase.SequItemLineColorName");

namespace distestproject {

struct DisTestConfigurationPrivate
{
  DisTestConfigurationPrivate(DisTestProject* project)
    : _project(project),
      m_useGlobal(true),
      m_sutSettings(GlobalRenderSettings::globalInstance()->sutSettings()),
      m_testSystemSettings(GlobalRenderSettings::globalInstance()->testSystemSettings()),
      m_testCaseSettings(GlobalRenderSettings::globalInstance()->testCaseSettings())
  {}

  DisTestProject* _project;
  bool m_useGlobal;
  DisTestSutSettings m_sutSettings;
  DisTestTestSystemSettings m_testSystemSettings;
  DisTestTestCaseSettings m_testCaseSettings;
};

DisTestConfiguration::DisTestConfiguration(DisTestProject *project)
  : _d(new DisTestConfigurationPrivate(project))
{
  connect(this, SIGNAL(sutRenderSettingsChanged()), this, SLOT(changeCustomSutRenderSettingsInDisTestEditor()));
  connect(this, SIGNAL(testSystemRenderSettingsChanged()), this, SLOT(changeCustomTestSystemRenderSettingsInDisTestEditor()));
  connect(this, SIGNAL(testCaseRenderSettingsChanged()), this, SLOT(changeCustomTestCaseRenderSettingsInDisTestEditor()));
}

DisTestConfiguration::~DisTestConfiguration()
{
  delete this->_d;
}

void DisTestConfiguration::setUseGlobalSettings(bool use)
{
  this->_d->m_useGlobal = use;

  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  QString projectID(this->_d->_project->document()->fileName());
  renderManager->registerRenderSettings(projectID, use);
}

bool DisTestConfiguration::useGlobalSettings() const
{
  return this->_d->m_useGlobal;
}

void DisTestConfiguration::cloneGlobalSettings()
{
  const GlobalRenderSettings *globalRenderSettings = GlobalRenderSettings::globalInstance();

  this->_d->m_sutSettings.setCompTextFontSeries(globalRenderSettings->sutSettings().compTextFontSeries());
  this->_d->m_sutSettings.setCompTextFontSize(globalRenderSettings->sutSettings().compTextFontSize());
  this->_d->m_sutSettings.setCompTextFontBold(globalRenderSettings->sutSettings().compTextFontBold());
  this->_d->m_sutSettings.setCompTextFontItalic(globalRenderSettings->sutSettings().compTextFontItalic());
  this->_d->m_sutSettings.setCompTextColorName(globalRenderSettings->sutSettings().compTextColorName());
  this->_d->m_sutSettings.setCompBoxWidth(globalRenderSettings->sutSettings().compBoxWidth());
  this->_d->m_sutSettings.setCompBoxHeight(globalRenderSettings->sutSettings().compBoxHeight());
  this->_d->m_sutSettings.setCompBoxColorName(globalRenderSettings->sutSettings().compBoxColorName());
  this->_d->m_sutSettings.setCompBorderWidth(globalRenderSettings->sutSettings().compBorderWidth());
  this->_d->m_sutSettings.setCompBorderColorName(globalRenderSettings->sutSettings().compBorderColorName());
  this->_d->m_sutSettings.setPortBoxWidth(globalRenderSettings->sutSettings().portBoxWidth());
  this->_d->m_sutSettings.setPortBoxHeight(globalRenderSettings->sutSettings().portBoxHeight());
  this->_d->m_sutSettings.setPortBoxColorName(globalRenderSettings->sutSettings().portBoxColorName());
  this->_d->m_sutSettings.setPortBorderWidth(globalRenderSettings->sutSettings().portBorderWidth());
  this->_d->m_sutSettings.setPortBorderColorName(globalRenderSettings->sutSettings().portBorderColorName());
  this->_d->m_sutSettings.setLinkLineWidth(globalRenderSettings->sutSettings().linkLineWidth());
  this->_d->m_sutSettings.setLinkLineColorName(globalRenderSettings->sutSettings().linkLineColorName());
  this->_d->m_sutSettings.setSutBoxColorName(globalRenderSettings->sutSettings().sutBoxColorName());
  this->_d->m_sutSettings.setSutBoxCompMargin(globalRenderSettings->sutSettings().sutBoxCompMargin());
  this->_d->m_sutSettings.setSutBoxMargin(globalRenderSettings->sutSettings().sutBoxMargin());
  this->_d->m_sutSettings.setSutBoxRadius(globalRenderSettings->sutSettings().sutBoxRadius());

  this->_d->m_testSystemSettings.setCompTextFontSeries(globalRenderSettings->testSystemSettings().compTextFontSeries());
  this->_d->m_testSystemSettings.setCompTextFontSize(globalRenderSettings->testSystemSettings().compTextFontSize());
  this->_d->m_testSystemSettings.setCompTextFontBold(globalRenderSettings->testSystemSettings().compTextFontBold());
  this->_d->m_testSystemSettings.setCompTextFontItalic(globalRenderSettings->testSystemSettings().compTextFontItalic());
  this->_d->m_testSystemSettings.setCompTextColorName(globalRenderSettings->testSystemSettings().compTextColorName());
  this->_d->m_testSystemSettings.setCompBoxWidth(globalRenderSettings->testSystemSettings().compBoxWidth());
  this->_d->m_testSystemSettings.setCompBoxHeight(globalRenderSettings->testSystemSettings().compBoxHeight());
  this->_d->m_testSystemSettings.setCompBoxColorName(globalRenderSettings->testSystemSettings().compBoxColorName());
  this->_d->m_testSystemSettings.setCompBorderWidth(globalRenderSettings->testSystemSettings().compBorderWidth());
  this->_d->m_testSystemSettings.setCompBorderColorName(globalRenderSettings->testSystemSettings().compBorderColorName());
  this->_d->m_testSystemSettings.setPortBoxWidth(globalRenderSettings->testSystemSettings().portBoxWidth());
  this->_d->m_testSystemSettings.setPortBoxHeight(globalRenderSettings->testSystemSettings().portBoxHeight());
  this->_d->m_testSystemSettings.setPortBoxColorName(globalRenderSettings->testSystemSettings().portBoxColorName());
  this->_d->m_testSystemSettings.setPortBorderWidth(globalRenderSettings->testSystemSettings().portBorderWidth());
  this->_d->m_testSystemSettings.setPortBorderColorName(globalRenderSettings->testSystemSettings().portBorderColorName());
  this->_d->m_testSystemSettings.setLinkLineWidth(globalRenderSettings->testSystemSettings().linkLineWidth());
  this->_d->m_testSystemSettings.setLinkLineColorName(globalRenderSettings->testSystemSettings().linkLineColorName());
  this->_d->m_testSystemSettings.setSpaceToSutBox(globalRenderSettings->testSystemSettings().spaceToSutBox());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontSeries(globalRenderSettings->testSystemSettings().testSystemBoxTextFontSeries());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontSize(globalRenderSettings->testSystemSettings().testSystemBoxTextFontSize());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontBold(globalRenderSettings->testSystemSettings().testSystemBoxTextFontBold());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontItalic(globalRenderSettings->testSystemSettings().testSystemBoxTextFontItalic());
  this->_d->m_testSystemSettings.setTestSystemBoxTextColorName(globalRenderSettings->testSystemSettings().testSystemBoxTextColorName());
  this->_d->m_testSystemSettings.setTestSystemBoxBoxWidth(globalRenderSettings->testSystemSettings().testSystemBoxBoxWidth());
  this->_d->m_testSystemSettings.setTestSystemBoxBoxHeight(globalRenderSettings->testSystemSettings().testSystemBoxBoxHeight());
  this->_d->m_testSystemSettings.setTestSystemBoxBoxColorName(globalRenderSettings->testSystemSettings().testSystemBoxBoxColorName());
  this->_d->m_testSystemSettings.setTestSystemBoxBorderWidth(globalRenderSettings->testSystemSettings().testSystemBoxBorderWidth());
  this->_d->m_testSystemSettings.setTestSystemBoxBorderColorName(globalRenderSettings->testSystemSettings().testSystemBoxBorderColorName());
  this->_d->m_testSystemSettings.setTestSystemBoxMargin(globalRenderSettings->testSystemSettings().testSystemBoxMargin());
  this->_d->m_testSystemSettings.setTestSystemBoxRadius(globalRenderSettings->testSystemSettings().testSystemBoxRadius());

  this->_d->m_testCaseSettings.setSutCompTextFontSeries(globalRenderSettings->testCaseSettings().sutCompTextFontSeries());
  this->_d->m_testCaseSettings.setSutCompTextFontSize(globalRenderSettings->testCaseSettings().sutCompTextFontSize());
  this->_d->m_testCaseSettings.setSutCompTextFontBold(globalRenderSettings->testCaseSettings().sutCompTextFontBold());
  this->_d->m_testCaseSettings.setSutCompTextFontItalic(globalRenderSettings->testCaseSettings().sutCompTextFontItalic());
  this->_d->m_testCaseSettings.setSutCompTextColorName(globalRenderSettings->testCaseSettings().sutCompTextColorName());
  this->_d->m_testCaseSettings.setSutCompBoxWidth(globalRenderSettings->testCaseSettings().sutCompBoxWidth());
  this->_d->m_testCaseSettings.setSutCompBoxHeight(globalRenderSettings->testCaseSettings().sutCompBoxHeight());
  this->_d->m_testCaseSettings.setSutCompBoxColorName(globalRenderSettings->testCaseSettings().sutCompBoxColorName());
  this->_d->m_testCaseSettings.setSutCompBorderWidth(globalRenderSettings->testCaseSettings().sutCompBorderWidth());
  this->_d->m_testCaseSettings.setSutCompBorderColorName(globalRenderSettings->testCaseSettings().sutCompBorderColorName());
  this->_d->m_testCaseSettings.setSutCompLifeLineWidth(globalRenderSettings->testCaseSettings().sutCompLifeLineWidth());
  this->_d->m_testCaseSettings.setSutCompLifeLineColorName(globalRenderSettings->testCaseSettings().sutCompLifeLineColorName());
  this->_d->m_testCaseSettings.setTestCompTextFontSeries(globalRenderSettings->testCaseSettings().testCompTextFontSeries());
  this->_d->m_testCaseSettings.setTestCompTextFontSize(globalRenderSettings->testCaseSettings().testCompTextFontSize());
  this->_d->m_testCaseSettings.setTestCompTextFontBold(globalRenderSettings->testCaseSettings().testCompTextFontBold());
  this->_d->m_testCaseSettings.setTestCompTextFontItalic(globalRenderSettings->testCaseSettings().testCompTextFontItalic());
  this->_d->m_testCaseSettings.setTestCompTextColorName(globalRenderSettings->testCaseSettings().testCompTextColorName());
  this->_d->m_testCaseSettings.setTestCompBoxWidth(globalRenderSettings->testCaseSettings().testCompBoxWidth());
  this->_d->m_testCaseSettings.setTestCompBoxHeight(globalRenderSettings->testCaseSettings().testCompBoxHeight());
  this->_d->m_testCaseSettings.setTestCompBoxColorName(globalRenderSettings->testCaseSettings().testCompBoxColorName());
  this->_d->m_testCaseSettings.setTestCompBorderWidth(globalRenderSettings->testCaseSettings().testCompBorderWidth());
  this->_d->m_testCaseSettings.setTestCompBorderColorName(globalRenderSettings->testCaseSettings().testCompBorderColorName());
  this->_d->m_testCaseSettings.setTestCompLifeLineWidth(globalRenderSettings->testCaseSettings().testCompLifeLineWidth());
  this->_d->m_testCaseSettings.setTestCompLifeLineColorName(globalRenderSettings->testCaseSettings().testCompLifeLineColorName());
  this->_d->m_testCaseSettings.setSequItemTextFontSeries(globalRenderSettings->testCaseSettings().sequItemTextFontSeries());
  this->_d->m_testCaseSettings.setSequItemTextFontSize(globalRenderSettings->testCaseSettings().sequItemTextFontSize());
  this->_d->m_testCaseSettings.setSequItemTextFontBold(globalRenderSettings->testCaseSettings().sequItemTextFontBold());
  this->_d->m_testCaseSettings.setSequItemTextFontItalic(globalRenderSettings->testCaseSettings().sequItemTextFontItalic());
  this->_d->m_testCaseSettings.setSequItemTextColorName(globalRenderSettings->testCaseSettings().sequItemTextColorName());
  this->_d->m_testCaseSettings.setSequItemLineWidth(globalRenderSettings->testCaseSettings().sequItemLineWidth());
  this->_d->m_testCaseSettings.setSequItemLineColorName(globalRenderSettings->testCaseSettings().sequItemLineColorName());
}

const DisTestSutSettings &DisTestConfiguration::sutSettings() const
{
  return this->_d->m_sutSettings;
}

const DisTestTestSystemSettings &DisTestConfiguration::testSystemSettings() const
{
  return this->_d->m_testSystemSettings;
}

const DisTestTestCaseSettings &DisTestConfiguration::testCaseSettings() const
{
  return this->_d->m_testCaseSettings;
}

void DisTestConfiguration::changeCustomSutRenderSettingsInDisTestEditor() const
{
  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  QString projectID(this->_d->_project->document()->fileName());
  try
  {
    DisTestRenderSettings *customRenderSettings = renderManager->customRenderSettings(projectID);
    customRenderSettings->changeSutSettings(this->_d->m_sutSettings.compOptionsFromSettings(),
                                            this->_d->m_sutSettings.portOptionsFromSettings(),
                                            this->_d->m_sutSettings.linkOptionsFromSettings(),
                                            QBrush(QColor(this->_d->m_sutSettings.sutBoxColorName())),
                                            this->_d->m_sutSettings.sutBoxCompMargin(),
                                            this->_d->m_sutSettings.sutBoxMargin(),
                                            this->_d->m_sutSettings.sutBoxRadius());
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
  }
}

void DisTestConfiguration::changeCustomTestSystemRenderSettingsInDisTestEditor() const
{
  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  QString projectID(this->_d->_project->document()->fileName());
  try
  {
    DisTestRenderSettings *customRenderSettings = renderManager->customRenderSettings(projectID);
    customRenderSettings->changeTestSystemSettings(this->_d->m_testSystemSettings.compOptionsFromSettings(),
                                                   this->_d->m_testSystemSettings.portOptionsFromSettings(),
                                                   this->_d->m_testSystemSettings.linkOptionsFromSettings(),
                                                   this->_d->m_testSystemSettings.spaceToSutBox(),
                                                   this->_d->m_testSystemSettings.testSystemBoxOptionsFromSettings(),
                                                   this->_d->m_testSystemSettings.testSystemBoxMargin(),
                                                   this->_d->m_testSystemSettings.testSystemBoxRadius());
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
  }
}

void DisTestConfiguration::changeCustomTestCaseRenderSettingsInDisTestEditor() const
{
  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  QString projectID(this->_d->_project->document()->fileName());
  try
  {
    DisTestRenderSettings *customRenderSettings = renderManager->customRenderSettings(projectID);
    customRenderSettings->changeTestCaseSettings(this->_d->m_testCaseSettings.sutCompOptionsFromSettings(),
                                                 QColor(this->_d->m_testCaseSettings.sutCompLifeLineColorName()),
                                                 this->_d->m_testCaseSettings.sutCompLifeLineWidth(),
                                                 this->_d->m_testCaseSettings.testCompOptionsFromSettings(),
                                                 QColor(this->_d->m_testCaseSettings.testCompLifeLineColorName()),
                                                 this->_d->m_testCaseSettings.testCompLifeLineWidth(),
                                                 this->_d->m_testCaseSettings.sequenceItemOptionsFromSettings());
  }
  catch (std::runtime_error &ex)
  {
    qDebug() << ex.what();
  }
}

void DisTestConfiguration::changeSutCompTextFont(const QFont font)
{
  this->_d->m_sutSettings.setCompTextFontSeries(font.family());
  this->_d->m_sutSettings.setCompTextFontSize(font.pointSize());
  this->_d->m_sutSettings.setCompTextFontBold(font.bold());
  this->_d->m_sutSettings.setCompTextFontItalic(font.italic());

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutCompTextFontSize(int size)
{
  this->_d->m_sutSettings.setCompTextFontSize(size);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutCompTextColor(QString colorName)
{
  this->_d->m_sutSettings.setCompTextColorName(colorName);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutCompBoxWidth(qreal width)
{
  this->_d->m_sutSettings.setCompBoxWidth(width);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutCompBoxHeight(qreal height)
{
  this->_d->m_sutSettings.setCompBoxHeight(height);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutCompBoxColor(QString colorName)
{
  this->_d->m_sutSettings.setCompBoxColorName(colorName);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutCompBorderWidth(int width)
{
  this->_d->m_sutSettings.setCompBorderWidth(width);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutCompBorderColor(QString colorName)
{
  this->_d->m_sutSettings.setCompBorderColorName(colorName);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutPortBoxWidth(qreal width)
{
  this->_d->m_sutSettings.setPortBoxWidth(width);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutPortBoxHeight(qreal height)
{
  this->_d->m_sutSettings.setPortBoxHeight(height);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutPortBoxColor(QString colorName)
{
  this->_d->m_sutSettings.setPortBoxColorName(colorName);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutPortBorderWidth(int width)
{
  this->_d->m_sutSettings.setPortBorderWidth(width);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutPortBorderColor(QString colorName)
{
  this->_d->m_sutSettings.setPortBorderColorName(colorName);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutLinkLineWidth(int width)
{
  this->_d->m_sutSettings.setLinkLineWidth(width);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutLinkLineColor(QString colorName)
{
  this->_d->m_sutSettings.setLinkLineColorName(colorName);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutBoxColor(QString colorName)
{
  this->_d->m_sutSettings.setSutBoxColorName(colorName);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutBoxCompMargin(qreal margin)
{
  this->_d->m_sutSettings.setSutBoxCompMargin(margin);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutBoxMargin(qreal margin)
{
  this->_d->m_sutSettings.setSutBoxMargin(margin);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeSutBoxRadius(qreal radius)
{
  this->_d->m_sutSettings.setSutBoxRadius(radius);

  emit sutRenderSettingsChanged();
}

void DisTestConfiguration::changeTsCompTextFontName(const QFont font)
{
  this->_d->m_testSystemSettings.setCompTextFontSeries(font.family());
  this->_d->m_testSystemSettings.setCompTextFontSize(font.pointSize());
  this->_d->m_testSystemSettings.setCompTextFontBold(font.bold());
  this->_d->m_testSystemSettings.setCompTextFontItalic(font.italic());

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsCompTextFontSize(int size)
{
  this->_d->m_testSystemSettings.setCompTextFontSize(size);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsCompTextColor(QString colorName)
{
  this->_d->m_testSystemSettings.setCompTextColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsCompBoxWidth(qreal width)
{
  this->_d->m_testSystemSettings.setCompBoxWidth(width);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsCompBoxHeight(qreal height)
{
  this->_d->m_testSystemSettings.setCompBoxHeight(height);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsCompBoxColor(QString colorName)
{
  this->_d->m_testSystemSettings.setCompBoxColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsCompBorderWidth(int width)
{
  this->_d->m_testSystemSettings.setCompBorderWidth(width);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsCompBorderColor(QString colorName)
{
  this->_d->m_testSystemSettings.setCompBorderColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsPortBoxWidth(qreal width)
{
  this->_d->m_testSystemSettings.setPortBoxWidth(width);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsPortBoxHeight(qreal height)
{
  this->_d->m_testSystemSettings.setPortBoxHeight(height);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsPortBoxColor(QString colorName)
{
  this->_d->m_testSystemSettings.setPortBoxColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsPortBorderWidth(int width)
{
  this->_d->m_testSystemSettings.setPortBorderWidth(width);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsPortBorderColor(QString colorName)
{
  this->_d->m_testSystemSettings.setPortBorderColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsLinkLineWidth(int width)
{
  this->_d->m_testSystemSettings.setLinkLineWidth(width);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsLinkLineColor(QString colorName)
{
  this->_d->m_testSystemSettings.setLinkLineColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeSpaceToSutBox(qreal margin)
{
  this->_d->m_testSystemSettings.setSpaceToSutBox(margin);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxTextFontName(const QFont font)
{
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontSeries(font.family());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontSize(font.pointSize());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontBold(font.bold());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontItalic(font.italic());

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxTextFontSize(int size)
{
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontSize(size);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxTextColor(QString colorName)
{
  this->_d->m_testSystemSettings.setTestSystemBoxTextColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxBoxWidth(qreal width)
{
  this->_d->m_testSystemSettings.setTestSystemBoxBoxWidth(width);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxBoxHeight(qreal height)
{
  this->_d->m_testSystemSettings.setTestSystemBoxBoxHeight(height);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxBoxColor(QString colorName)
{
  this->_d->m_testSystemSettings.setTestSystemBoxBoxColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxBorderWidth(int width)
{
  this->_d->m_testSystemSettings.setTestSystemBoxBorderWidth(width);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxBorderColor(QString colorName)
{
  this->_d->m_testSystemSettings.setTestSystemBoxBorderColorName(colorName);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxMargin(qreal margin)
{
  this->_d->m_testSystemSettings.setTestSystemBoxMargin(margin);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTsBoxRadius(qreal radius)
{
  this->_d->m_testSystemSettings.setTestSystemBoxRadius(radius);

  emit testSystemRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompTextFontName(const QFont font)
{
  this->_d->m_testCaseSettings.setSutCompTextFontSeries(font.family());
  this->_d->m_testCaseSettings.setSutCompTextFontSize(font.pointSize());
  this->_d->m_testCaseSettings.setSutCompTextFontBold(font.bold());
  this->_d->m_testCaseSettings.setSutCompTextFontItalic(font.italic());

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompTextFontSize(int size)
{
  this->_d->m_testCaseSettings.setSutCompTextFontSize(size);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompTextColor(QString colorName)
{
  this->_d->m_testCaseSettings.setSutCompTextColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompBoxWidth(qreal width)
{
  this->_d->m_testCaseSettings.setSutCompBoxWidth(width);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompBoxHeight(qreal height)
{
  this->_d->m_testCaseSettings.setSutCompBoxHeight(height);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompBoxColor(QString colorName)
{
  this->_d->m_testCaseSettings.setSutCompBoxColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompBorderWidth(int width)
{
  this->_d->m_testCaseSettings.setSutCompBorderWidth(width);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompBorderColor(QString colorName)
{
  this->_d->m_testCaseSettings.setSutCompBorderColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompLifeLineWidth(int width)
{
  this->_d->m_testCaseSettings.setSutCompLifeLineWidth(width);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSutCompLifeLineColor(QString colorName)
{
  this->_d->m_testCaseSettings.setSutCompLifeLineColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompTextFontName(const QFont font)
{
  this->_d->m_testCaseSettings.setTestCompTextFontSeries(font.family());
  this->_d->m_testCaseSettings.setTestCompTextFontSize(font.pointSize());
  this->_d->m_testCaseSettings.setTestCompTextFontBold(font.bold());
  this->_d->m_testCaseSettings.setTestCompTextFontItalic(font.italic());

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompTextFontSize(int size)
{
  this->_d->m_testCaseSettings.setTestCompTextFontSize(size);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompTextColor(QString colorName)
{
  this->_d->m_testCaseSettings.setTestCompTextColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompBoxWidth(qreal width)
{
  this->_d->m_testCaseSettings.setTestCompBoxWidth(width);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompBoxHeight(qreal height)
{
  this->_d->m_testCaseSettings.setTestCompBoxHeight(height);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompBoxColor(QString colorName)
{
  this->_d->m_testCaseSettings.setTestCompBoxColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompBorderWidth(int width)
{
  this->_d->m_testCaseSettings.setTestCompBorderWidth(width);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompBorderColor(QString colorName)
{
  this->_d->m_testCaseSettings.setTestCompBorderColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompLifeLineWidth(int width)
{
  this->_d->m_testCaseSettings.setTestCompLifeLineWidth(width);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcTestCompLifeLineColor(QString colorName)
{
  this->_d->m_testCaseSettings.setTestCompLifeLineColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSequItemTextFontName(const QFont font)
{
  this->_d->m_testCaseSettings.setSequItemTextFontSeries(font.family());
  this->_d->m_testCaseSettings.setSequItemTextFontSize(font.pointSize());
  this->_d->m_testCaseSettings.setSequItemTextFontBold(font.bold());
  this->_d->m_testCaseSettings.setSequItemTextFontItalic(font.italic());

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSequItemTextFontSize(int size)
{
  this->_d->m_testCaseSettings.setSequItemTextFontSize(size);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSequItemTextColor(QString colorName)
{
  this->_d->m_testCaseSettings.setSequItemTextColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSequItemLineWidth(int width)
{
  this->_d->m_testCaseSettings.setSequItemLineWidth(width);

  emit testCaseRenderSettingsChanged();
}

void DisTestConfiguration::changeTcSequItemLineColor(QString colorName)
{
  this->_d->m_testCaseSettings.setSequItemLineColorName(colorName);

  emit testCaseRenderSettingsChanged();
}

QVariantMap DisTestConfiguration::toMap() const
{
  QVariantMap map;
  map.insert(kUseGlobal, this->_d->m_useGlobal);

  map.insert(kSutCompTextFontName, this->_d->m_sutSettings.compTextFontSeries());
  map.insert(kSutCompTextFontSize, this->_d->m_sutSettings.compTextFontSize());
  map.insert(kSutCompTextFontBold, this->_d->m_sutSettings.compTextFontBold());
  map.insert(kSutCompTextFontItalic, this->_d->m_sutSettings.compTextFontItalic());
  map.insert(kSutCompTextColorName, this->_d->m_sutSettings.compTextColorName());
  map.insert(kSutCompBoxWidth, this->_d->m_sutSettings.compBoxWidth());
  map.insert(kSutCompBoxHeight, this->_d->m_sutSettings.compBoxHeight());
  map.insert(kSutCompBoxColorName, this->_d->m_sutSettings.compBoxColorName());
  map.insert(kSutCompBorderWidth, this->_d->m_sutSettings.compBorderWidth());
  map.insert(kSutCompBorderColorName, this->_d->m_sutSettings.compBorderColorName());
  map.insert(kSutPortBoxWidth, this->_d->m_sutSettings.portBoxWidth());
  map.insert(kSutPortBoxHeight, this->_d->m_sutSettings.portBoxHeight());
  map.insert(kSutPortBoxColorName, this->_d->m_sutSettings.portBoxColorName());
  map.insert(kSutPortBorderWidth, this->_d->m_sutSettings.portBorderWidth());
  map.insert(kSutPortBorderColorName, this->_d->m_sutSettings.portBorderColorName());
  map.insert(kSutLinkLineWidth, this->_d->m_sutSettings.linkLineWidth());
  map.insert(kSutLinkLineColorName, this->_d->m_sutSettings.linkLineColorName());
  map.insert(kSutBoxColorName, this->_d->m_sutSettings.sutBoxColorName());
  map.insert(kSutBoxCompMargin,this->_d->m_sutSettings.sutBoxCompMargin());
  map.insert(kSutBoxMargin, this->_d->m_sutSettings.sutBoxMargin());
  map.insert(kSutBoxRadius, this->_d->m_sutSettings.sutBoxRadius());

  map.insert(kTsCompTextFontName, this->_d->m_testSystemSettings.compTextFontSeries());
  map.insert(kTsCompTextFontSize, this->_d->m_testSystemSettings.compTextFontSize());
  map.insert(kTsCompTextFontBold, this->_d->m_testSystemSettings.compTextFontBold());
  map.insert(kTsCompTextFontItalic, this->_d->m_testSystemSettings.compTextFontItalic());
  map.insert(kTsCompTextColorName, this->_d->m_testSystemSettings.compTextColorName());
  map.insert(kTsCompBoxWidth, this->_d->m_testSystemSettings.compBoxWidth());
  map.insert(kTsCompBoxHeight, this->_d->m_testSystemSettings.compBoxHeight());
  map.insert(kTsCompBoxColorName, this->_d->m_testSystemSettings.compBoxColorName());
  map.insert(kTsCompBorderWidth, this->_d->m_testSystemSettings.compBorderWidth());
  map.insert(kTsCompBorderColorName, this->_d->m_testSystemSettings.compBorderColorName());
  map.insert(kTsPortBoxWidth, this->_d->m_testSystemSettings.portBoxWidth());
  map.insert(kTsPortBoxHeight, this->_d->m_testSystemSettings.portBoxHeight());
  map.insert(kTsPortBoxColorName, this->_d->m_testSystemSettings.portBoxColorName());
  map.insert(kTsPortBorderWidth, this->_d->m_testSystemSettings.portBorderWidth());
  map.insert(kTsPortBorderColorName, this->_d->m_testSystemSettings.portBorderColorName());
  map.insert(kTsLinkLineWidth, this->_d->m_testSystemSettings.linkLineWidth());
  map.insert(kTsLinkLineColorName, this->_d->m_testSystemSettings.linkLineColorName());
  map.insert(kTsSpaceToSutBox,this->_d->m_testSystemSettings.spaceToSutBox());
  map.insert(kTsBoxTextFontName, this->_d->m_testSystemSettings.testSystemBoxTextFontSeries());
  map.insert(kTsBoxTextFontSize, this->_d->m_testSystemSettings.testSystemBoxTextFontSize());
  map.insert(kTsBoxTextFontBold, this->_d->m_testSystemSettings.testSystemBoxTextFontBold());
  map.insert(kTsBoxTextFontItalic, this->_d->m_testSystemSettings.testSystemBoxTextFontItalic());
  map.insert(kTsBoxTextColorName, this->_d->m_testSystemSettings.testSystemBoxTextColorName());
  map.insert(kTsBoxBoxWidth, this->_d->m_testSystemSettings.testSystemBoxBoxWidth());
  map.insert(kTsBoxBoxHeight, this->_d->m_testSystemSettings.testSystemBoxBoxHeight());
  map.insert(kTsBoxBoxColorName, this->_d->m_testSystemSettings.testSystemBoxBoxColorName());
  map.insert(kTsBoxBorderWidth, this->_d->m_testSystemSettings.testSystemBoxBorderWidth());
  map.insert(kTsBoxBorderColorName, this->_d->m_testSystemSettings.testSystemBoxBorderColorName());
  map.insert(kTsBoxMargin, this->_d->m_testSystemSettings.testSystemBoxMargin());
  map.insert(kTsBoxRadius, this->_d->m_testSystemSettings.testSystemBoxRadius());

  map.insert(kTcSutCompTextFontName, this->_d->m_testCaseSettings.sutCompTextFontSeries());
  map.insert(kTcSutCompTextFontSize, this->_d->m_testCaseSettings.sutCompTextFontSize());
  map.insert(kTcSutCompTextFontBold, this->_d->m_testCaseSettings.sutCompTextFontBold());
  map.insert(kTcSutCompTextFontItalic, this->_d->m_testCaseSettings.sutCompTextFontItalic());
  map.insert(kTcSutCompTextColorName, this->_d->m_testCaseSettings.sutCompTextColorName());
  map.insert(kTcSutCompBoxWidth, this->_d->m_testCaseSettings.sutCompBoxWidth());
  map.insert(kTcSutCompBoxHeight, this->_d->m_testCaseSettings.sutCompBoxHeight());
  map.insert(kTcSutCompBoxColorName, this->_d->m_testCaseSettings.sutCompBoxColorName());
  map.insert(kTcSutCompBorderWidth, this->_d->m_testCaseSettings.sutCompBorderWidth());
  map.insert(kTcSutCompBorderColorName, this->_d->m_testCaseSettings.sutCompBorderColorName());
  map.insert(kTcSutLifeLineWidth, this->_d->m_testCaseSettings.sutCompLifeLineWidth());
  map.insert(kTcSutLifeLineColorName, this->_d->m_testCaseSettings.sutCompLifeLineColorName());
  map.insert(kTcTestCompTextFontName, this->_d->m_testCaseSettings.testCompTextFontSeries());
  map.insert(kTcTestCompTextFontSize, this->_d->m_testCaseSettings.testCompTextFontSize());
  map.insert(kTcTestCompTextFontBold, this->_d->m_testCaseSettings.testCompTextFontBold());
  map.insert(kTcTestCompTextFontItalic, this->_d->m_testCaseSettings.testCompTextFontItalic());
  map.insert(kTcTestCompTextColorName, this->_d->m_testCaseSettings.testCompTextColorName());
  map.insert(kTcTestCompBoxWidth, this->_d->m_testCaseSettings.testCompBoxWidth());
  map.insert(kTcTestCompBoxHeight, this->_d->m_testCaseSettings.testCompBoxHeight());
  map.insert(kTcTestCompBoxColorName, this->_d->m_testCaseSettings.testCompBoxColorName());
  map.insert(kTcTestCompBorderWidth, this->_d->m_testCaseSettings.testCompBorderWidth());
  map.insert(kTcTestCompBorderColorName, this->_d->m_testCaseSettings.testCompBorderColorName());
  map.insert(kTcTestLifeLineWidth, this->_d->m_testCaseSettings.testCompLifeLineWidth());
  map.insert(kTcTestLifeLineColorName, this->_d->m_testCaseSettings.testCompLifeLineColorName());
  map.insert(kTcSequItemTextFontName, this->_d->m_testCaseSettings.sequItemTextFontSeries());
  map.insert(kTcSequItemTextFontSize, this->_d->m_testCaseSettings.sequItemTextFontSize());
  map.insert(kTcSequItemTextFontBold, this->_d->m_testCaseSettings.sequItemTextFontBold());
  map.insert(kTcSequItemTextFontItalic, this->_d->m_testCaseSettings.sequItemTextFontItalic());
  map.insert(kTcSequItemTextColorName, this->_d->m_testCaseSettings.sequItemTextColorName());
  map.insert(kTcSequItemLineWidth, this->_d->m_testCaseSettings.sequItemLineWidth());
  map.insert(kTcSequItemLineColorName, this->_d->m_testCaseSettings.sequItemLineColorName());

  return map;
}

void DisTestConfiguration::fromMap(const QVariantMap &map)
{
  this->_d->m_useGlobal = map.value(kUseGlobal, this->_d->m_useGlobal).toBool();

  DisTestRenderManager *renderManager = DisTestRenderManager::instance();
  QString projectID(this->_d->_project->document()->fileName());
  renderManager->registerRenderSettings(projectID, this->_d->m_useGlobal);

  this->_d->m_sutSettings.setCompTextFontSeries(map.value(kSutCompTextFontName, this->_d->m_sutSettings.compTextFontSeries()).toString());
  this->_d->m_sutSettings.setCompTextFontSize(map.value(kSutCompTextFontSize, this->_d->m_sutSettings.compTextFontSize()).toInt());
  this->_d->m_sutSettings.setCompTextFontBold(map.value(kSutCompTextFontBold, this->_d->m_sutSettings.compTextFontBold()).toBool());
  this->_d->m_sutSettings.setCompTextFontItalic(map.value(kSutCompTextFontItalic, this->_d->m_sutSettings.compTextFontItalic()).toBool());
  this->_d->m_sutSettings.setCompTextColorName(map.value(kSutCompTextColorName, this->_d->m_sutSettings.compTextColorName()).toString());
  this->_d->m_sutSettings.setCompBoxWidth(map.value(kSutCompBoxWidth, this->_d->m_sutSettings.compBoxWidth()).toDouble());
  this->_d->m_sutSettings.setCompBoxHeight(map.value(kSutCompBoxHeight, this->_d->m_sutSettings.compBoxHeight()).toDouble());
  this->_d->m_sutSettings.setCompBoxColorName(map.value(kSutCompBoxColorName, this->_d->m_sutSettings.compBoxColorName()).toString());
  this->_d->m_sutSettings.setCompBorderWidth(map.value(kSutCompBorderWidth, this->_d->m_sutSettings.compBorderWidth()).toInt());
  this->_d->m_sutSettings.setCompBorderColorName(map.value(kSutCompBorderColorName, this->_d->m_sutSettings.compBorderColorName()).toString());
  this->_d->m_sutSettings.setPortBoxWidth(map.value(kSutPortBoxWidth, this->_d->m_sutSettings.portBoxWidth()).toDouble());
  this->_d->m_sutSettings.setPortBoxHeight(map.value(kSutPortBoxHeight, this->_d->m_sutSettings.portBoxHeight()).toDouble());
  this->_d->m_sutSettings.setPortBoxColorName(map.value(kSutPortBoxColorName, this->_d->m_sutSettings.portBoxColorName()).toString());
  this->_d->m_sutSettings.setPortBorderWidth(map.value(kSutPortBorderWidth, this->_d->m_sutSettings.portBorderWidth()).toInt());
  this->_d->m_sutSettings.setPortBorderColorName(map.value(kSutPortBorderColorName, this->_d->m_sutSettings.portBorderColorName()).toString());
  this->_d->m_sutSettings.setLinkLineWidth(map.value(kSutLinkLineWidth, this->_d->m_sutSettings.linkLineWidth()).toInt());
  this->_d->m_sutSettings.setLinkLineColorName(map.value(kSutLinkLineColorName, this->_d->m_sutSettings.linkLineColorName()).toString());
  this->_d->m_sutSettings.setSutBoxColorName(map.value(kSutBoxColorName, this->_d->m_sutSettings.sutBoxColorName()).toString());
  this->_d->m_sutSettings.setSutBoxCompMargin(map.value(kSutBoxCompMargin,this->_d->m_sutSettings.sutBoxCompMargin()).toDouble());
  this->_d->m_sutSettings.setSutBoxMargin(map.value(kSutBoxMargin, this->_d->m_sutSettings.sutBoxMargin()).toDouble());
  this->_d->m_sutSettings.setSutBoxRadius(map.value(kSutBoxRadius, this->_d->m_sutSettings.sutBoxRadius()).toDouble());

  emit sutRenderSettingsChanged();

  this->_d->m_testSystemSettings.setCompTextFontSeries(map.value(kTsCompTextFontName, this->_d->m_testSystemSettings.compTextFontSeries()).toString());
  this->_d->m_testSystemSettings.setCompTextFontSize(map.value(kTsCompTextFontSize, this->_d->m_testSystemSettings.compTextFontSize()).toInt());
  this->_d->m_testSystemSettings.setCompTextFontBold(map.value(kTsCompTextFontBold, this->_d->m_testSystemSettings.compTextFontBold()).toBool());
  this->_d->m_testSystemSettings.setCompTextFontItalic(map.value(kTsCompTextFontItalic, this->_d->m_testSystemSettings.compTextFontItalic()).toBool());
  this->_d->m_testSystemSettings.setCompTextColorName(map.value(kTsCompTextColorName, this->_d->m_testSystemSettings.compTextColorName()).toString());
  this->_d->m_testSystemSettings.setCompBoxWidth(map.value(kTsCompBoxWidth, this->_d->m_testSystemSettings.compBoxWidth()).toDouble());
  this->_d->m_testSystemSettings.setCompBoxHeight(map.value(kTsCompBoxHeight, this->_d->m_testSystemSettings.compBoxHeight()).toDouble());
  this->_d->m_testSystemSettings.setCompBoxColorName(map.value(kTsCompBoxColorName, this->_d->m_testSystemSettings.compBoxColorName()).toString());
  this->_d->m_testSystemSettings.setCompBorderWidth(map.value(kTsCompBorderWidth, this->_d->m_testSystemSettings.compBorderWidth()).toInt());
  this->_d->m_testSystemSettings.setCompBorderColorName(map.value(kTsCompBorderColorName, this->_d->m_testSystemSettings.compBorderColorName()).toString());
  this->_d->m_testSystemSettings.setPortBoxWidth(map.value(kTsPortBoxWidth, this->_d->m_testSystemSettings.portBoxWidth()).toDouble());
  this->_d->m_testSystemSettings.setPortBoxHeight(map.value(kTsPortBoxHeight, this->_d->m_testSystemSettings.portBoxHeight()).toDouble());
  this->_d->m_testSystemSettings.setPortBoxColorName(map.value(kTsPortBoxColorName, this->_d->m_testSystemSettings.portBoxColorName()).toString());
  this->_d->m_testSystemSettings.setPortBorderWidth(map.value(kTsPortBorderWidth, this->_d->m_testSystemSettings.portBorderWidth()).toInt());
  this->_d->m_testSystemSettings.setPortBorderColorName(map.value(kTsPortBorderColorName, this->_d->m_testSystemSettings.portBorderColorName()).toString());
  this->_d->m_testSystemSettings.setLinkLineWidth(map.value(kTsLinkLineWidth, this->_d->m_testSystemSettings.linkLineWidth()).toInt());
  this->_d->m_testSystemSettings.setLinkLineColorName(map.value(kTsLinkLineColorName, this->_d->m_testSystemSettings.linkLineColorName()).toString());
  this->_d->m_testSystemSettings.setSpaceToSutBox(map.value(kTsSpaceToSutBox,this->_d->m_testSystemSettings.spaceToSutBox()).toDouble());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontSeries(map.value(kTsBoxTextFontName, this->_d->m_testSystemSettings.testSystemBoxTextFontSeries()).toString());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontSize(map.value(kTsBoxTextFontSize, this->_d->m_testSystemSettings.testSystemBoxTextFontSize()).toInt());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontBold(map.value(kTsBoxTextFontBold, this->_d->m_testSystemSettings.testSystemBoxTextFontBold()).toBool());
  this->_d->m_testSystemSettings.setTestSystemBoxTextFontItalic(map.value(kTsBoxTextFontItalic, this->_d->m_testSystemSettings.testSystemBoxTextFontItalic()).toBool());
  this->_d->m_testSystemSettings.setTestSystemBoxTextColorName(map.value(kTsBoxTextColorName, this->_d->m_testSystemSettings.testSystemBoxTextColorName()).toString());
  this->_d->m_testSystemSettings.setTestSystemBoxBoxWidth(map.value(kTsBoxBoxWidth, this->_d->m_testSystemSettings.testSystemBoxBoxWidth()).toDouble());
  this->_d->m_testSystemSettings.setTestSystemBoxBoxHeight(map.value(kTsBoxBoxHeight, this->_d->m_testSystemSettings.testSystemBoxBoxHeight()).toDouble());
  this->_d->m_testSystemSettings.setTestSystemBoxBoxColorName(map.value(kTsBoxBoxColorName, this->_d->m_testSystemSettings.testSystemBoxBoxColorName()).toString());
  this->_d->m_testSystemSettings.setTestSystemBoxBorderWidth(map.value(kTsBoxBorderWidth, this->_d->m_testSystemSettings.testSystemBoxBorderWidth()).toInt());
  this->_d->m_testSystemSettings.setTestSystemBoxBorderColorName(map.value(kTsBoxBorderColorName, this->_d->m_testSystemSettings.testSystemBoxBorderColorName()).toString());
  this->_d->m_testSystemSettings.setTestSystemBoxMargin(map.value(kTsBoxMargin, this->_d->m_testSystemSettings.testSystemBoxMargin()).toDouble());
  this->_d->m_testSystemSettings.setTestSystemBoxRadius(map.value(kTsBoxRadius, this->_d->m_testSystemSettings.testSystemBoxRadius()).toDouble());

  emit testSystemRenderSettingsChanged();

  this->_d->m_testCaseSettings.setSutCompTextFontSeries(map.value(kTcSutCompTextFontName, this->_d->m_testCaseSettings.sutCompTextFontSeries()).toString());
  this->_d->m_testCaseSettings.setSutCompTextFontSize(map.value(kTcSutCompTextFontSize, this->_d->m_testCaseSettings.sutCompTextFontSize()).toInt());
  this->_d->m_testCaseSettings.setSutCompTextFontBold(map.value(kTcSutCompTextFontBold, this->_d->m_testCaseSettings.sutCompTextFontBold()).toBool());
  this->_d->m_testCaseSettings.setSutCompTextFontItalic(map.value(kTcSutCompTextFontItalic, this->_d->m_testCaseSettings.sutCompTextFontItalic()).toBool());
  this->_d->m_testCaseSettings.setSutCompTextColorName(map.value(kTcSutCompTextColorName, this->_d->m_testCaseSettings.sutCompTextColorName()).toString());
  this->_d->m_testCaseSettings.setSutCompBoxWidth(map.value(kTcSutCompBoxWidth, this->_d->m_testCaseSettings.sutCompBoxWidth()).toDouble());
  this->_d->m_testCaseSettings.setSutCompBoxHeight(map.value(kTcSutCompBoxHeight, this->_d->m_testCaseSettings.sutCompBoxHeight()).toDouble());
  this->_d->m_testCaseSettings.setSutCompBoxColorName(map.value(kTcSutCompBoxColorName, this->_d->m_testCaseSettings.sutCompBoxColorName()).toString());
  this->_d->m_testCaseSettings.setSutCompBorderWidth(map.value(kTcSutCompBorderWidth, this->_d->m_testCaseSettings.sutCompBorderWidth()).toInt());
  this->_d->m_testCaseSettings.setSutCompBorderColorName(map.value(kTcSutCompBorderColorName, this->_d->m_testCaseSettings.sutCompBorderColorName()).toString());
  this->_d->m_testCaseSettings.setSutCompLifeLineWidth(map.value(kTcSutLifeLineWidth, this->_d->m_testCaseSettings.sutCompLifeLineWidth()).toInt());
  this->_d->m_testCaseSettings.setSutCompLifeLineColorName(map.value(kTcSutLifeLineColorName, this->_d->m_testCaseSettings.sutCompLifeLineColorName()).toString());
  this->_d->m_testCaseSettings.setTestCompTextFontSeries(map.value(kTcTestCompTextFontName, this->_d->m_testCaseSettings.testCompTextFontSeries()).toString());
  this->_d->m_testCaseSettings.setTestCompTextFontSize(map.value(kTcTestCompTextFontSize, this->_d->m_testCaseSettings.testCompTextFontSize()).toInt());
  this->_d->m_testCaseSettings.setTestCompTextFontBold(map.value(kTcTestCompTextFontBold, this->_d->m_testCaseSettings.testCompTextFontBold()).toBool());
  this->_d->m_testCaseSettings.setTestCompTextFontItalic(map.value(kTcTestCompTextFontItalic, this->_d->m_testCaseSettings.testCompTextFontItalic()).toBool());
  this->_d->m_testCaseSettings.setTestCompTextColorName(map.value(kTcTestCompTextColorName, this->_d->m_testCaseSettings.testCompTextColorName()).toString());
  this->_d->m_testCaseSettings.setTestCompBoxWidth(map.value(kTcTestCompBoxWidth, this->_d->m_testCaseSettings.testCompBoxWidth()).toDouble());
  this->_d->m_testCaseSettings.setTestCompBoxHeight(map.value(kTcTestCompBoxHeight, this->_d->m_testCaseSettings.testCompBoxHeight()).toDouble());
  this->_d->m_testCaseSettings.setTestCompBoxColorName(map.value(kTcTestCompBoxColorName, this->_d->m_testCaseSettings.testCompBoxColorName()).toString());
  this->_d->m_testCaseSettings.setTestCompBorderWidth(map.value(kTcTestCompBorderWidth, this->_d->m_testCaseSettings.testCompBorderWidth()).toInt());
  this->_d->m_testCaseSettings.setTestCompBorderColorName(map.value(kTcTestCompBorderColorName, this->_d->m_testCaseSettings.testCompBorderColorName()).toString());
  this->_d->m_testCaseSettings.setTestCompLifeLineWidth(map.value(kTcTestLifeLineWidth, this->_d->m_testCaseSettings.testCompLifeLineWidth()).toInt());
  this->_d->m_testCaseSettings.setTestCompLifeLineColorName(map.value(kTcTestLifeLineColorName, this->_d->m_testCaseSettings.testCompLifeLineColorName()).toString());
  this->_d->m_testCaseSettings.setSequItemTextFontSeries(map.value(kTcSequItemTextFontName, this->_d->m_testCaseSettings.sequItemTextFontSeries()).toString());
  this->_d->m_testCaseSettings.setSequItemTextFontSize(map.value(kTcSequItemTextFontSize, this->_d->m_testCaseSettings.sequItemTextFontSize()).toInt());
  this->_d->m_testCaseSettings.setSequItemTextFontBold(map.value(kTcSequItemTextFontBold, this->_d->m_testCaseSettings.sequItemTextFontBold()).toBool());
  this->_d->m_testCaseSettings.setSequItemTextFontItalic(map.value(kTcSequItemTextFontItalic, this->_d->m_testCaseSettings.sequItemTextFontItalic()).toBool());
  this->_d->m_testCaseSettings.setSequItemTextColorName(map.value(kTcSequItemTextColorName, this->_d->m_testCaseSettings.sequItemTextColorName()).toString());
  this->_d->m_testCaseSettings.setSequItemLineWidth(map.value(kTcSequItemLineWidth, this->_d->m_testCaseSettings.sequItemLineWidth()).toInt());
  this->_d->m_testCaseSettings.setSequItemLineColorName(map.value(kTcSequItemLineColorName, this->_d->m_testCaseSettings.sequItemLineColorName()).toString());

  emit testCaseRenderSettingsChanged();
}

}

