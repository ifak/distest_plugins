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
#ifndef DISTESTEDITOR_DISTESTRENDERSETTINGS_HPP
#define DISTESTEDITOR_DISTESTRENDERSETTINGS_HPP

#include "distesteditor_global.hpp"

#include <mobatawidgets/graph/types.hpp>

namespace distesteditor {

class DISTESTEDITOR_EXPORT DisTestRenderSettings : public QObject
{
    Q_OBJECT

public:
    DisTestRenderSettings();
    DisTestRenderSettings(const DisTestRenderSettings &source);

    const view::graph::NodeOptions& sutCompOptions() const;
    void setSutCompOptions(const view::graph::NodeOptions &sutCompOptions);
    const view::graph::NodeOptions& sutPortOptions() const;
    void setSutPortOptions(const view::graph::NodeOptions &sutPortOptions);
    const view::graph::ArcOptions& sutLinkOptions() const;
    void setSutLinkOptions(const view::graph::ArcOptions &sutLinkOptions);
    const QBrush& sutBoxBrush() const;
    void setSutBoxBrush(const QBrush &sutBoxBrush);
    const qreal& sutBoxCompMargin() const;
    void setSutBoxCompMargin(const qreal sutBoxCompMargin);
    const qreal& sutBoxMargin() const;
    void setSutBoxMargin(const qreal sutBoxMargin);
    const qreal& sutBoxRadius() const;
    void setSutBoxRadius(const qreal sutBoxRadius);

    const view::graph::NodeOptions& testSystemCompOptions() const;
    void setTestSystemCompOptions(const view::graph::NodeOptions &testSystemCompOptions);
    const view::graph::NodeOptions& testSystemPortOptions() const;
    void setTestSystemPortOptions(const view::graph::NodeOptions &testSystemPortOptions);
    const view::graph::ArcOptions& testSystemLinkOptions() const;
    void setTestSystemLinkOptions(const view::graph::ArcOptions &testSystemLinkOptions);
    const qreal& testSystemSpaceToSutBox() const;
    void setTestSystemSpaceToSutBox(const qreal testSystemSpaceToSutBox);
    const view::graph::NodeOptions& testSystemBoxOptions() const;
    void setTestSystemBoxOptions(const view::graph::NodeOptions &testSystemBoxOptions);
    const qreal& testSystemBoxMargin() const;
    void setTestSystemBoxMargin(const qreal testSystemBoxMargin);
    const qreal& testSystemBoxRadius() const;
    void setTestSystemBoxRadius(const qreal testSystemBoxRadius);

    const view::graph::NodeOptions& testCaseSutCompOptions() const;
    void setTestCaseSutCompOptions(const view::graph::NodeOptions &sutCompOptions);
    const QColor& testCaseSutCompLifeLineColor() const;
    void setTestCaseSutCompLifeLineColor(const QColor &sutCompLifeLineColor);
    const int& testCaseSutCompLifeLineWidth() const;
    void setTestCaseSutCompLifeLineWidth(const int sutCompLifeLineWidth);
    const view::graph::NodeOptions& testCaseTestCompOptions() const;
    void setTestCaseTestCompOptions(const view::graph::NodeOptions &testCompOptions);
    const QColor& testCaseTestCompLifeLineColor() const;
    void setTestCaseTestCompLifeLineColor(const QColor &testCompLifeLineColor);
    const int& testCaseTestCompLifeLineWidth() const;
    void setTestCaseTestCompLifeLineWidth(const int testCompLifeLineWidth);
    const view::graph::ArcOptions& testCaseSequItemOptions() const;
    void setTestCaseSequItemOptions(const view::graph::ArcOptions &sequItemOptions);

    void changeSutSettings(const view::graph::NodeOptions &sutCompOptions,
                           const view::graph::NodeOptions &sutPortOptions,
                           const view::graph::ArcOptions &sutLinkOptions,
                           const QBrush &sutBoxBrush,
                           const qreal sutBoxCompMargin,
                           const qreal sutBoxMargin,
                           const qreal sutBoxRadius);
    void changeTestSystemSettings(const view::graph::NodeOptions &testSystemCompOptions,
                                  const view::graph::NodeOptions &testSystemPortOptions,
                                  const view::graph::ArcOptions &testSystemLinkOptions,
                                  const qreal testSystemSpaceToSutBox,
                                  const view::graph::NodeOptions &testSystemBoxOptions,
                                  const qreal testSystemBoxMargin,
                                  const qreal testSystemBoxRadius);
    void changeTestCaseSettings(const view::graph::NodeOptions &sutCompOptions,
                                const QColor &sutCompLifeLineColor,
                                const int sutCompLifeLineWidth,
                                const view::graph::NodeOptions &testCompOptions,
                                const QColor &testCompLifeLineColor,
                                const int testCompLifeLineWidth,
                                const view::graph::ArcOptions &sequItemOptions);

signals:
    void sutSettingsChanged(DisTestRenderSettings *renderSettings);
    void testSystemSettingsChanged(DisTestRenderSettings *renderSettings);
    void testCaseSettingsChanged(DisTestRenderSettings *renderSettings);

private:
    view::graph::NodeOptions _sutCompOptions;
    view::graph::NodeOptions _sutPortOptions;
    view::graph::ArcOptions _sutLinkOptions;
    QBrush _sutBoxBrush;
    qreal _sutBoxCompMargin;
    qreal _sutBoxMargin;
    qreal _sutBoxRadius;

    view::graph::NodeOptions _testSystemCompOptions;
    view::graph::NodeOptions _testSystemPortOptions;
    view::graph::ArcOptions _testSystemLinkOptions;
    qreal _testSystemSpaceToSutBox;
    view::graph::NodeOptions _testSystemBoxOptions;
    qreal _testSystemBoxMargin;
    qreal _testSystemBoxRadius;

    view::graph::NodeOptions _testCaseSutCompOptions;
    QColor _testCaseSutCompLifeLineColor;
    int _testCaseSutCompLifeLineWidth;
    view::graph::NodeOptions _testCaseTestCompOptions;
    QColor _testCaseTestCompLifeLineColor;
    int _testCaseTestCompLifeLineWidth;
    view::graph::ArcOptions _testCaseSequItemOptions;
};

}

#endif // DISTESTRENDERSETTINGS_HPP
