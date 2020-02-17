#include "globalrendersettings.hpp"
#include "distestprojectconstants.hpp"

#include "sutsettings.hpp"
#include "testsystemsettings.hpp"
#include "testcasesettings.hpp"

#include <coreplugin/icore.h>

#include "distestrendermanager.hpp"
#include "distestrendersettings.hpp"

namespace distestproject {

GlobalRenderSettings *GlobalRenderSettings::_globalInstance = 0;

GlobalRenderSettings::GlobalRenderSettings()
    : QObject(),
      _sutSettings(new DisTestSutSettings()),
      _testSystemSettings(new DisTestTestSystemSettings()),
      _testCaseSettings(new DisTestTestCaseSettings())
{
#ifdef Q_OS_WIN
    _sutSettings->setCompTextFontSeries(QString::fromLatin1("MS Sans Serif"));
    _testSystemSettings->setCompTextFontSeries(QString::fromLatin1("MS Sans Serif"));
    _testSystemSettings->setTestSystemBoxTextFontSeries(QString::fromLatin1("MS Sans Serif"));
    _testCaseSettings->setSutCompTextFontSeries(QString::fromLatin1("MS Sans Serif"));
    _testCaseSettings->setTestCompTextFontSeries(QString::fromLatin1("MS Sans Serif"));
    _testCaseSettings->setSequItemTextFontSeries(QString::fromLatin1("MS Sans Serif"));
#else
    _sutSettings->setCompTextFontSeries(QString::fromLatin1("Sans Serif"));
    _testSystemSettings->setCompTextFontSeries(QString::fromLatin1("Sans Serif"));
    _testSystemSettings->setTestSystemBoxTextFontSeries(QString::fromLatin1("Sans Serif"));
    _testCaseSettings->setSutCompTextFontSeries(QString::fromLatin1("Sans Serif"));
    _testCaseSettings->setTestCompTextFontSeries(QString::fromLatin1("Sans Serif"));
    _testCaseSettings->setSequItemTextFontSeries(QString::fromLatin1("Sans Serif"));
#endif

    _sutSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeSutRenderSettingsInDisTestEditor();
    _testSystemSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeTestSystemRenderSettingsInDisTestEditor();
    _testCaseSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeTestCaseRenderSettingsInDisTestEditor();

    _globalInstance = this;
}

GlobalRenderSettings::GlobalRenderSettings(const GlobalRenderSettings& source)
    : QObject(),
      _sutSettings(new DisTestSutSettings(source.sutSettings())),
      _testSystemSettings(new DisTestTestSystemSettings(source.testSystemSettings())),
      _testCaseSettings(new DisTestTestCaseSettings(source.testCaseSettings()))
{
    _sutSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeSutRenderSettingsInDisTestEditor();
    _testSystemSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeTestSystemRenderSettingsInDisTestEditor();
    _testCaseSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeTestCaseRenderSettingsInDisTestEditor();

    _globalInstance = this;
}

GlobalRenderSettings::~GlobalRenderSettings()
{
    delete _testCaseSettings;
    delete _testSystemSettings;
    delete _sutSettings;
}

GlobalRenderSettings *GlobalRenderSettings::createGlobalRenderSettings()
{
    if (!_globalInstance)
    {
        new GlobalRenderSettings();
    }

    return _globalInstance;
}

GlobalRenderSettings *GlobalRenderSettings::createGlobalRenderSettings(const GlobalRenderSettings &source)
{
    if (!_globalInstance)
    {
        new GlobalRenderSettings(source);
    }

    return _globalInstance;
}

void GlobalRenderSettings::removeGlobalRenderSettings()
{
    if (_globalInstance)
    {
        delete _globalInstance;
    }
}

GlobalRenderSettings *GlobalRenderSettings::globalInstance()
{
    return _globalInstance;
}

void GlobalRenderSettings::setSutSettings(const DisTestSutSettings &sutSettings)
{
    DisTestSutSettings *oldSutSettings = _sutSettings;
    _sutSettings = new DisTestSutSettings(sutSettings);
    delete oldSutSettings;

    changeSutRenderSettingsInDisTestEditor();
}

const DisTestSutSettings &GlobalRenderSettings::sutSettings() const
{
    return *_sutSettings;
}

void GlobalRenderSettings::reloadSutSettings()
{
    _sutSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
}

void GlobalRenderSettings::setTestSystemSettings(const DisTestTestSystemSettings &testSystemSettings)
{
    DisTestTestSystemSettings *oldTestSystemSettings = _testSystemSettings;
    _testSystemSettings = new DisTestTestSystemSettings(testSystemSettings);
    delete oldTestSystemSettings;

    changeTestSystemRenderSettingsInDisTestEditor();
}

const DisTestTestSystemSettings &GlobalRenderSettings::testSystemSettings() const
{
    return *_testSystemSettings;
}

void GlobalRenderSettings::reloadTestSystemSettings()
{
    _testSystemSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
}

void GlobalRenderSettings::setTestCaseSettings(const DisTestTestCaseSettings &testCaseSettings)
{
    DisTestTestCaseSettings *oldTestCaseSettings = _testCaseSettings;
    _testCaseSettings = new DisTestTestCaseSettings(testCaseSettings);
    delete oldTestCaseSettings;

    changeTestCaseRenderSettingsInDisTestEditor();
}

const DisTestTestCaseSettings &GlobalRenderSettings::testCaseSettings() const
{
    return *_testCaseSettings;
}

void GlobalRenderSettings::reloadTestCaseSettings()
{
    _testCaseSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
}

void GlobalRenderSettings::changeSutRenderSettingsInDisTestEditor()
{
    DisTestRenderManager::instance()->globalRenderSettings()->changeSutSettings(_sutSettings->compOptionsFromSettings(),
                                                                                               _sutSettings->portOptionsFromSettings(),
                                                                                               _sutSettings->linkOptionsFromSettings(),
                                                                                               QBrush(QColor(_sutSettings->sutBoxColorName())),
                                                                                               _sutSettings->sutBoxCompMargin(),
                                                                                               _sutSettings->sutBoxMargin(),
                                                                                               _sutSettings->sutBoxRadius());
}

void GlobalRenderSettings::changeTestSystemRenderSettingsInDisTestEditor()
{
    DisTestRenderManager::instance()->globalRenderSettings()->changeTestSystemSettings(_testSystemSettings->compOptionsFromSettings(),
                                                                                                       _testSystemSettings->portOptionsFromSettings(),
                                                                                                       _testSystemSettings->linkOptionsFromSettings(),
                                                                                                       _testSystemSettings->spaceToSutBox(),
                                                                                                       _testSystemSettings->testSystemBoxOptionsFromSettings(),
                                                                                                       _testSystemSettings->testSystemBoxMargin(),
                                                                                                       _testSystemSettings->testSystemBoxRadius());
}

void GlobalRenderSettings::changeTestCaseRenderSettingsInDisTestEditor()
{
    DisTestRenderManager::instance()->globalRenderSettings()->changeTestCaseSettings(_testCaseSettings->sutCompOptionsFromSettings(),
                                                                                                     QColor(_testCaseSettings->sutCompLifeLineColorName()),
                                                                                                     _testCaseSettings->sutCompLifeLineWidth(),
                                                                                                     _testCaseSettings->testCompOptionsFromSettings(),
                                                                                                     QColor(_testCaseSettings->testCompLifeLineColorName()),
                                                                                                     _testCaseSettings->testCompLifeLineWidth(),
                                                                                                     _testCaseSettings->sequenceItemOptionsFromSettings());
}

}

