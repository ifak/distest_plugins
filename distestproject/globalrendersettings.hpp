/*
 * This file is part of mobata.
 *
 * mobata is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * mobata is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with mobata.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DISTESTPROJECT_GLOBALRENDERSETTINGS_HPP
#define DISTESTPROJECT_GLOBALRENDERSETTINGS_HPP

#include "distestproject_global.hpp"

#include <QObject>

namespace distestproject {

class DisTestSutSettings;
class DisTestTestSystemSettings;
class DisTestTestCaseSettings;

class DISTESTPROJECTSHARED_EXPORT GlobalRenderSettings : public QObject
{
    Q_OBJECT

public:
    ~GlobalRenderSettings();

    static GlobalRenderSettings* createGlobalRenderSettings();
    static GlobalRenderSettings* createGlobalRenderSettings(const GlobalRenderSettings &source);
    static void removeGlobalRenderSettings();

    static GlobalRenderSettings* globalInstance();

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

    GlobalRenderSettings();
    GlobalRenderSettings(const GlobalRenderSettings& source);

    static GlobalRenderSettings *_globalInstance;
};

}

#endif // GLOBALRENDERSETTINGS_HPP
