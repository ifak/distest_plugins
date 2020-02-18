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
#ifndef DISTESTPROJECT_DISTESTCONFIGURATION_HPP
#define DISTESTPROJECT_DISTESTCONFIGURATION_HPP

#include "distestproject_global.hpp"

#include "sutsettings.hpp"
#include "testsystemsettings.hpp"
#include "testcasesettings.hpp"

#include <QObject>
#include <QVariantMap>

namespace distestproject
{

class DisTestProject;
struct DisTestConfigurationPrivate;

class DISTESTPROJECTSHARED_EXPORT DisTestConfiguration : public QObject
{
    Q_OBJECT
public:
    DisTestConfiguration(DisTestProject *project);
    ~DisTestConfiguration();

    void setUseGlobalSettings(bool use);
    bool useGlobalSettings() const;
    void cloneGlobalSettings();

    const DisTestSutSettings& sutSettings() const;
    const DisTestTestSystemSettings& testSystemSettings() const;
    const DisTestTestCaseSettings& testCaseSettings() const;

    QVariantMap toMap() const;
    void fromMap(const QVariantMap &map);

signals:
    void sutRenderSettingsChanged();
    void testSystemRenderSettingsChanged();
    void testCaseRenderSettingsChanged();

public slots:
    void changeSutCompTextFont(const QFont font);
    void changeSutCompTextFontSize(int size);
    void changeSutCompTextColor(QString colorName);
    void changeSutCompBoxWidth(qreal width);
    void changeSutCompBoxHeight(qreal height);
    void changeSutCompBoxColor(QString colorName);
    void changeSutCompBorderWidth(int width);
    void changeSutCompBorderColor(QString colorName);
    void changeSutPortBoxWidth(qreal width);
    void changeSutPortBoxHeight(qreal height);
    void changeSutPortBoxColor(QString colorName);
    void changeSutPortBorderWidth(int width);
    void changeSutPortBorderColor(QString colorName);
    void changeSutLinkLineWidth(int width);
    void changeSutLinkLineColor(QString colorName);
    void changeSutBoxColor(QString colorName);
    void changeSutBoxCompMargin(qreal margin);
    void changeSutBoxMargin(qreal margin);
    void changeSutBoxRadius(qreal radius);

    void changeTsCompTextFontName(const QFont font);
    void changeTsCompTextFontSize(int size);
    void changeTsCompTextColor(QString colorName);
    void changeTsCompBoxWidth(qreal width);
    void changeTsCompBoxHeight(qreal height);
    void changeTsCompBoxColor(QString colorName);
    void changeTsCompBorderWidth(int width);
    void changeTsCompBorderColor(QString colorName);
    void changeTsPortBoxWidth(qreal width);
    void changeTsPortBoxHeight(qreal height);
    void changeTsPortBoxColor(QString colorName);
    void changeTsPortBorderWidth(int width);
    void changeTsPortBorderColor(QString colorName);
    void changeTsLinkLineWidth(int width);
    void changeTsLinkLineColor(QString colorName);
    void changeSpaceToSutBox(qreal margin);
    void changeTsBoxTextFontName(const QFont font);
    void changeTsBoxTextFontSize(int size);
    void changeTsBoxTextColor(QString colorName);
    void changeTsBoxBoxWidth(qreal width);
    void changeTsBoxBoxHeight(qreal height);
    void changeTsBoxBoxColor(QString colorName);
    void changeTsBoxBorderWidth(int width);
    void changeTsBoxBorderColor(QString colorName);
    void changeTsBoxMargin(qreal margin);
    void changeTsBoxRadius(qreal radius);

    void changeTcSutCompTextFontName(const QFont font);
    void changeTcSutCompTextFontSize(int size);
    void changeTcSutCompTextColor(QString colorName);
    void changeTcSutCompBoxWidth(qreal width);
    void changeTcSutCompBoxHeight(qreal height);
    void changeTcSutCompBoxColor(QString colorName);
    void changeTcSutCompBorderWidth(int width);
    void changeTcSutCompBorderColor(QString colorName);
    void changeTcSutCompLifeLineWidth(int width);
    void changeTcSutCompLifeLineColor(QString colorName);
    void changeTcTestCompTextFontName(const QFont font);
    void changeTcTestCompTextFontSize(int size);
    void changeTcTestCompTextColor(QString colorName);
    void changeTcTestCompBoxWidth(qreal width);
    void changeTcTestCompBoxHeight(qreal height);
    void changeTcTestCompBoxColor(QString colorName);
    void changeTcTestCompBorderWidth(int width);
    void changeTcTestCompBorderColor(QString colorName);
    void changeTcTestCompLifeLineWidth(int width);
    void changeTcTestCompLifeLineColor(QString colorName);
    void changeTcSequItemTextFontName(const QFont font);
    void changeTcSequItemTextFontSize(int size);
    void changeTcSequItemTextColor(QString colorName);
    void changeTcSequItemLineWidth(int width);
    void changeTcSequItemLineColor(QString colorName);

private slots:
    void changeCustomSutRenderSettingsInDisTestEditor() const;
    void changeCustomTestSystemRenderSettingsInDisTestEditor() const;
    void changeCustomTestCaseRenderSettingsInDisTestEditor() const;

private:
    DisTestConfigurationPrivate *_d;
};

}

#endif // DISTESTPROJECT_DISTESTCONFIGURATION_HPP
