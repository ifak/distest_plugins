/*
 * This file is part of distest_plugins.
 *
 * distest_plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * distest_plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with distest_plugins.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DISTESTPROJECT_DISTESTRENDERSETTINGS_HPP
#define DISTESTPROJECT_DISTESTRENDERSETTINGS_HPP

#include "distestproject_global.hpp"

#include <QObject>

namespace distestproject {

class DisTestSutSettings;
class DisTestTestSystemSettings;
class DisTestTestCaseSettings;

class DISTESTPROJECTSHARED_EXPORT DisTestRenderSettings : public QObject
{
    Q_OBJECT

public:
    ~DisTestRenderSettings();

    static DisTestRenderSettings* createGlobalRenderSettings();
    static DisTestRenderSettings* createGlobalRenderSettings(const DisTestRenderSettings &source);
    static void removeGlobalRenderSettings();

    static DisTestRenderSettings* globalInstance();

    void setSutSettings(const DisTestSutSettings &sutSettings);
    const DisTestSutSettings& sutSettings() const;
    void reloadSutSettings();
    void setTestSystemSettings(const DisTestTestSystemSettings &testSystemSettings);
    const DisTestTestSystemSettings& testSystemSettings() const;
    void reloadTestSystemSettings();
    void setTestCaseSettings(const DisTestTestCaseSettings &testCaseSettings);
    const DisTestTestCaseSettings& testCaseSettings() const;
    void reloadTestCaseSettings();

protected:
    void changeSutRenderSettingsInDisTestEditor();
    void changeTestSystemRenderSettingsInDisTestEditor();
    void changeTestCaseRenderSettingsInDisTestEditor();

private:
    DisTestSutSettings*        _sutSettings;
    DisTestTestSystemSettings* _testSystemSettings;
    DisTestTestCaseSettings*   _testCaseSettings;
    bool                       _isGlobalSettings;

    DisTestRenderSettings();
    DisTestRenderSettings(const DisTestRenderSettings& source);

    static DisTestRenderSettings *_globalInstance;
};

}

#endif // DISTESTRENDERSETTINGS_HPP
