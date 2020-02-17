#include "rendersettings.hpp"
#include "distestprojectconstants.hpp"

#include "sutsettings.hpp"
#include "testsystemsettings.hpp"
#include "testcasesettings.hpp"

#include <coreplugin/icore.h>

#include <distesteditor/distestrendermanager.hpp>
#include <distesteditor/distestrendersettings.hpp>

namespace distestproject {

DisTestRenderSettings *DisTestRenderSettings::_globalInstance = 0;

DisTestRenderSettings::DisTestRenderSettings()
    : _sutSettings(new DisTestSutSettings()),
      _testSystemSettings(new DisTestTestSystemSettings()),
      _testCaseSettings(new DisTestTestCaseSettings()),
      _isGlobalSettings(true)
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

DisTestRenderSettings::DisTestRenderSettings(const DisTestRenderSettings& source)
    : _sutSettings(new DisTestSutSettings(source.sutSettings())),
      _testSystemSettings(new DisTestTestSystemSettings(source.testSystemSettings())),
      _testCaseSettings(new DisTestTestCaseSettings(source.testCaseSettings())),
      _isGlobalSettings(true)
{
    _sutSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeSutRenderSettingsInDisTestEditor();
    _testSystemSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeTestSystemRenderSettingsInDisTestEditor();
    _testCaseSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
    changeTestCaseRenderSettingsInDisTestEditor();

    _globalInstance = this;
}

DisTestRenderSettings::~DisTestRenderSettings()
{
    delete _testCaseSettings;
    delete _testSystemSettings;
    delete _sutSettings;
}

DisTestRenderSettings *DisTestRenderSettings::createGlobalRenderSettings()
{
    if (!_globalInstance)
    {
        new DisTestRenderSettings();
    }

    return _globalInstance;
}

DisTestRenderSettings *DisTestRenderSettings::createGlobalRenderSettings(const DisTestRenderSettings &source)
{
    if (!_globalInstance)
    {
        new DisTestRenderSettings(source);
    }

    return _globalInstance;
}

void DisTestRenderSettings::removeGlobalRenderSettings()
{
    if (_globalInstance)
    {
        delete _globalInstance;
    }
}

DisTestRenderSettings *DisTestRenderSettings::globalInstance()
{
    return _globalInstance;
}

void DisTestRenderSettings::setSutSettings(const DisTestSutSettings &sutSettings)
{
    DisTestSutSettings *oldSutSettings = _sutSettings;
    _sutSettings = new DisTestSutSettings(sutSettings);
    delete oldSutSettings;

    changeSutRenderSettingsInDisTestEditor();
}

const DisTestSutSettings &DisTestRenderSettings::sutSettings() const
{
    return *_sutSettings;
}

void DisTestRenderSettings::reloadSutSettings()
{
    _sutSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
}

void DisTestRenderSettings::setTestSystemSettings(const DisTestTestSystemSettings &testSystemSettings)
{
    DisTestTestSystemSettings *oldTestSystemSettings = _testSystemSettings;
    _testSystemSettings = new DisTestTestSystemSettings(testSystemSettings);
    delete oldTestSystemSettings;

    changeTestSystemRenderSettingsInDisTestEditor();
}

const DisTestTestSystemSettings &DisTestRenderSettings::testSystemSettings() const
{
    return *_testSystemSettings;
}

void DisTestRenderSettings::reloadTestSystemSettings()
{
    _testSystemSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
}

void DisTestRenderSettings::setTestCaseSettings(const DisTestTestCaseSettings &testCaseSettings)
{
    DisTestTestCaseSettings *oldTestCaseSettings = _testCaseSettings;
    _testCaseSettings = new DisTestTestCaseSettings(testCaseSettings);
    delete oldTestCaseSettings;

    changeTestCaseRenderSettingsInDisTestEditor();
}

const DisTestTestCaseSettings &DisTestRenderSettings::testCaseSettings() const
{
    return *_testCaseSettings;
}

void DisTestRenderSettings::reloadTestCaseSettings()
{
    _testCaseSettings->fromSettings(QString::fromLatin1(distestproject::Constants::DISTEST_SETTINGS_PREFIX), Core::ICore::settings());
}

void DisTestRenderSettings::changeSutRenderSettingsInDisTestEditor()
{
    distesteditor::DisTestRenderManager::instance()->globalRenderSettings()->changeSutSettings(_sutSettings->compOptionsFromSettings(),
                                                                                               _sutSettings->portOptionsFromSettings(),
                                                                                               _sutSettings->linkOptionsFromSettings(),
                                                                                               QBrush(QColor(_sutSettings->sutBoxColorName())),
                                                                                               _sutSettings->sutBoxCompMargin(),
                                                                                               _sutSettings->sutBoxMargin(),
                                                                                               _sutSettings->sutBoxRadius());
}

void DisTestRenderSettings::changeTestSystemRenderSettingsInDisTestEditor()
{
    distesteditor::DisTestRenderManager::instance()->globalRenderSettings()->changeTestSystemSettings(_testSystemSettings->compOptionsFromSettings(),
                                                                                                       _testSystemSettings->portOptionsFromSettings(),
                                                                                                       _testSystemSettings->linkOptionsFromSettings(),
                                                                                                       _testSystemSettings->spaceToSutBox(),
                                                                                                       _testSystemSettings->testSystemBoxOptionsFromSettings(),
                                                                                                       _testSystemSettings->testSystemBoxMargin(),
                                                                                                       _testSystemSettings->testSystemBoxRadius());
}

void DisTestRenderSettings::changeTestCaseRenderSettingsInDisTestEditor()
{
    distesteditor::DisTestRenderManager::instance()->globalRenderSettings()->changeTestCaseSettings(_testCaseSettings->sutCompOptionsFromSettings(),
                                                                                                     QColor(_testCaseSettings->sutCompLifeLineColorName()),
                                                                                                     _testCaseSettings->sutCompLifeLineWidth(),
                                                                                                     _testCaseSettings->testCompOptionsFromSettings(),
                                                                                                     QColor(_testCaseSettings->testCompLifeLineColorName()),
                                                                                                     _testCaseSettings->testCompLifeLineWidth(),
                                                                                                     _testCaseSettings->sequenceItemOptionsFromSettings());
}


}

