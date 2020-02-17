#include "distestrendersettings.hpp"

#include <mobatawidgets/ts/comrendersut.hpp>
#include <mobatawidgets/ts/comrendertestsystem.hpp>
#include <mobatawidgets/ts/comrendertestcase.hpp>

namespace distesteditor {

DisTestRenderSettings::DisTestRenderSettings()
    : QObject(),
      _sutCompOptions(view::ts::ComRenderSut::defaultComponentOptions()),
      _sutPortOptions(view::ts::ComRenderSut::defaultPortOptions()),
      _sutLinkOptions(view::ts::ComRenderSut::defaultLinkOptions()),
      _sutBoxBrush(view::ts::ComRenderSut::defaultSutBoxBrushOption()),
      _sutBoxCompMargin(view::ts::ComRenderSut::defaultCompMarginSpace()),
      _sutBoxMargin(view::ts::ComRenderSut::defaultSutBoxMarginSpace()),
      _sutBoxRadius(view::ts::ComRenderSut::defaultSutBoxRadius()),
      _testSystemCompOptions(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions()),
      _testSystemPortOptions(view::ts::ComRenderTestSystem::defaultTestSystemPortOptions()),
      _testSystemLinkOptions(view::ts::ComRenderTestSystem::defaultTestSystemLinkOptions()),
      _testSystemSpaceToSutBox(view::ts::ComRenderTestSystem::defaultSpaceToSutBox()),
      _testSystemBoxOptions(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions()),
      _testSystemBoxMargin(view::ts::ComRenderTestSystem::defaultTestSystemBoxMarginSpace()),
      _testSystemBoxRadius(view::ts::ComRenderTestSystem::defaultTestSystemBoxRadius()),
      _testCaseSutCompOptions(view::ts::ComRenderTestCase::defaultSutCompOptions()),
      _testCaseSutCompLifeLineColor(view::ts::ComRenderTestCase::defaultSutLifeLineColor()),
      _testCaseSutCompLifeLineWidth(view::ts::ComRenderTestCase::defaultSutLifeLineWidth()),
      _testCaseTestCompOptions(view::ts::ComRenderTestCase::defaultTestCompOptions()),
      _testCaseTestCompLifeLineColor(view::ts::ComRenderTestCase::defaultTestLifeLineColor()),
      _testCaseTestCompLifeLineWidth(view::ts::ComRenderTestCase::defaultTestLifeLineWidth()),
      _testCaseSequItemOptions(view::ts::ComRenderTestCase::defaultArcOptions())
{
    // Do nothing
}

DisTestRenderSettings::DisTestRenderSettings(const DisTestRenderSettings &source)
    : QObject(),
      _sutCompOptions(source._sutCompOptions),
      _sutPortOptions(source._sutPortOptions),
      _sutLinkOptions(source._sutLinkOptions),
      _sutBoxBrush(source._sutBoxBrush),
      _sutBoxCompMargin(source._sutBoxCompMargin),
      _sutBoxMargin(source._sutBoxMargin),
      _sutBoxRadius(source._sutBoxRadius),
      _testSystemCompOptions(source._testSystemCompOptions),
      _testSystemPortOptions(source._testSystemPortOptions),
      _testSystemLinkOptions(source._testSystemLinkOptions),
      _testSystemSpaceToSutBox(source._testSystemSpaceToSutBox),
      _testSystemBoxOptions(source._testSystemBoxOptions),
      _testSystemBoxMargin(source._testSystemBoxMargin),
      _testSystemBoxRadius(source._testSystemBoxRadius),
      _testCaseSutCompOptions(source._testCaseSutCompOptions),
      _testCaseSutCompLifeLineColor(source._testCaseSutCompLifeLineColor),
      _testCaseSutCompLifeLineWidth(source._testCaseSutCompLifeLineWidth),
      _testCaseTestCompOptions(source._testCaseTestCompOptions),
      _testCaseTestCompLifeLineColor(source._testCaseTestCompLifeLineColor),
      _testCaseTestCompLifeLineWidth(source._testCaseTestCompLifeLineWidth),
      _testCaseSequItemOptions(source._testCaseSequItemOptions)
{
    // Do nothing
}

const view::graph::NodeOptions &DisTestRenderSettings::sutCompOptions() const
{
    return _sutCompOptions;
}

void DisTestRenderSettings::setSutCompOptions(const view::graph::NodeOptions &sutCompOptions)
{
    _sutCompOptions = sutCompOptions;
}

const view::graph::NodeOptions &DisTestRenderSettings::sutPortOptions() const
{
    return _sutPortOptions;
}

void DisTestRenderSettings::setSutPortOptions(const view::graph::NodeOptions &sutPortOptions)
{
    _sutPortOptions = sutPortOptions;
}

const view::graph::ArcOptions &DisTestRenderSettings::sutLinkOptions() const
{
    return _sutLinkOptions;
}

void DisTestRenderSettings::setSutLinkOptions(const view::graph::ArcOptions &sutLinkOptions)
{
    _sutLinkOptions = sutLinkOptions;
}

const QBrush &DisTestRenderSettings::sutBoxBrush() const
{
    return _sutBoxBrush;
}

void DisTestRenderSettings::setSutBoxBrush(const QBrush &sutBoxBrush)
{
    _sutBoxBrush = sutBoxBrush;
}

const qreal &DisTestRenderSettings::sutBoxCompMargin() const
{
    return _sutBoxCompMargin;
}

void DisTestRenderSettings::setSutBoxCompMargin(const qreal sutBoxCompMargin)
{
    _sutBoxCompMargin = sutBoxCompMargin;
}

const qreal &DisTestRenderSettings::sutBoxMargin() const
{
    return _sutBoxMargin;
}

void DisTestRenderSettings::setSutBoxMargin(const qreal sutBoxMargin)
{
    _sutBoxMargin = sutBoxMargin;
}

const qreal &DisTestRenderSettings::sutBoxRadius() const
{
    return _sutBoxRadius;
}

void DisTestRenderSettings::setSutBoxRadius(const qreal sutBoxRadius)
{
    _sutBoxRadius = sutBoxRadius;
}

const view::graph::NodeOptions &DisTestRenderSettings::testSystemCompOptions() const
{
    return _testSystemCompOptions;
}

void DisTestRenderSettings::setTestSystemCompOptions(const view::graph::NodeOptions &testSystemCompOptions)
{
    _testSystemCompOptions = testSystemCompOptions;
}

const view::graph::NodeOptions &DisTestRenderSettings::testSystemPortOptions() const
{
    return _testSystemPortOptions;
}

void DisTestRenderSettings::setTestSystemPortOptions(const view::graph::NodeOptions &testSystemPortOptions)
{
    _testSystemPortOptions = testSystemPortOptions;
}

const view::graph::ArcOptions &DisTestRenderSettings::testSystemLinkOptions() const
{
    return _testSystemLinkOptions;
}

void DisTestRenderSettings::setTestSystemLinkOptions(const view::graph::ArcOptions &testSystemLinkOptions)
{
    _testSystemLinkOptions = testSystemLinkOptions;
}

const qreal &DisTestRenderSettings::testSystemSpaceToSutBox() const
{
    return _testSystemSpaceToSutBox;
}

void DisTestRenderSettings::setTestSystemSpaceToSutBox(const qreal testSystemSpaceToSutBox)
{
    _testSystemSpaceToSutBox = testSystemSpaceToSutBox;
}

const view::graph::NodeOptions &DisTestRenderSettings::testSystemBoxOptions() const
{
    return _testSystemBoxOptions;
}

void DisTestRenderSettings::setTestSystemBoxOptions(const view::graph::NodeOptions &testSystemBoxOptions)
{
    _testSystemBoxOptions = testSystemBoxOptions;
}

const qreal &DisTestRenderSettings::testSystemBoxMargin() const
{
    return _testSystemBoxMargin;
}

void DisTestRenderSettings::setTestSystemBoxMargin(const qreal testSystemBoxMargin)
{
    _testSystemBoxMargin = testSystemBoxMargin;
}

const qreal &DisTestRenderSettings::testSystemBoxRadius() const
{
    return _testSystemBoxRadius;
}

void DisTestRenderSettings::setTestSystemBoxRadius(const qreal testSystemBoxRadius)
{
    _testSystemBoxRadius = testSystemBoxRadius;
}

const view::graph::NodeOptions &DisTestRenderSettings::testCaseSutCompOptions() const
{
    return _testCaseSutCompOptions;
}

void DisTestRenderSettings::setTestCaseSutCompOptions(const view::graph::NodeOptions &sutCompOptions)
{
    _testCaseSutCompOptions = sutCompOptions;
}

const QColor &DisTestRenderSettings::testCaseSutCompLifeLineColor() const
{
    return _testCaseSutCompLifeLineColor;
}

void DisTestRenderSettings::setTestCaseSutCompLifeLineColor(const QColor &sutCompLifeLineColor)
{
    _testCaseSutCompLifeLineColor = sutCompLifeLineColor;
}

const int &DisTestRenderSettings::testCaseSutCompLifeLineWidth() const
{
    return _testCaseSutCompLifeLineWidth;
}

void DisTestRenderSettings::setTestCaseSutCompLifeLineWidth(const int sutCompLifeLineWidth)
{
    _testCaseSutCompLifeLineWidth = sutCompLifeLineWidth;
}

const view::graph::NodeOptions &DisTestRenderSettings::testCaseTestCompOptions() const
{
    return _testCaseTestCompOptions;
}

void DisTestRenderSettings::setTestCaseTestCompOptions(const view::graph::NodeOptions &testCompOptions)
{
    _testCaseTestCompOptions = testCompOptions;
}

const QColor &DisTestRenderSettings::testCaseTestCompLifeLineColor() const
{
    return _testCaseTestCompLifeLineColor;
}
void DisTestRenderSettings::setTestCaseTestCompLifeLineColor(const QColor &testCompLifeLineColor)
{
    _testCaseTestCompLifeLineColor = testCompLifeLineColor;
}

const int &DisTestRenderSettings::testCaseTestCompLifeLineWidth() const
{
    return _testCaseTestCompLifeLineWidth;
}

void DisTestRenderSettings::setTestCaseTestCompLifeLineWidth(const int testCompLifeLineWidth)
{
    _testCaseTestCompLifeLineWidth = testCompLifeLineWidth;
}

const view::graph::ArcOptions &DisTestRenderSettings::testCaseSequItemOptions() const
{
    return _testCaseSequItemOptions;
}

void DisTestRenderSettings::setTestCaseSequItemOptions(const view::graph::ArcOptions &sequItemOptions)
{
    _testCaseSequItemOptions = sequItemOptions;
}

void DisTestRenderSettings::changeSutSettings(const view::graph::NodeOptions &sutCompOptions,
                                              const view::graph::NodeOptions &sutPortOptions,
                                              const view::graph::ArcOptions &sutLinkOptions,
                                              const QBrush &sutBoxBrush,
                                              const qreal sutBoxCompMargin,
                                              const qreal sutBoxMargin,
                                              const qreal sutBoxRadius)
{
    setSutCompOptions(sutCompOptions);
    setSutPortOptions(sutPortOptions);
    setSutLinkOptions(sutLinkOptions);
    setSutBoxBrush(sutBoxBrush);
    setSutBoxCompMargin(sutBoxCompMargin);
    setSutBoxMargin(sutBoxMargin);
    setSutBoxRadius(sutBoxRadius);

    emit sutSettingsChanged(this);
}

void DisTestRenderSettings::changeTestSystemSettings(const view::graph::NodeOptions &testSystemCompOptions,
                                                     const view::graph::NodeOptions &testSystemPortOptions,
                                                     const view::graph::ArcOptions &testSystemLinkOptions,
                                                     const qreal testSystemSpaceToSutBox,
                                                     const view::graph::NodeOptions &testSystemBoxOptions,
                                                     const qreal testSystemBoxMargin,
                                                     const qreal testSystemBoxRadius)
{
    setTestSystemCompOptions(testSystemCompOptions);
    setTestSystemPortOptions(testSystemPortOptions);
    setTestSystemLinkOptions(testSystemLinkOptions);
    setTestSystemSpaceToSutBox(testSystemSpaceToSutBox);
    setTestSystemBoxOptions(testSystemBoxOptions);
    setTestSystemBoxMargin(testSystemBoxMargin);
    setTestSystemBoxRadius(testSystemBoxRadius);

    emit testSystemSettingsChanged(this);
}

void DisTestRenderSettings::changeTestCaseSettings(const view::graph::NodeOptions &sutCompOptions,
                                                   const QColor &sutCompLifeLineColor,
                                                   const int sutCompLifeLineWidth,
                                                   const view::graph::NodeOptions &testCompOptions,
                                                   const QColor &testCompLifeLineColor,
                                                   const int testCompLifeLineWidth,
                                                   const view::graph::ArcOptions &sequItemOptions)
{
    setTestCaseSutCompOptions(sutCompOptions);
    setTestCaseSutCompLifeLineColor(sutCompLifeLineColor);
    setTestCaseSutCompLifeLineWidth(sutCompLifeLineWidth);
    setTestCaseTestCompOptions(testCompOptions);
    setTestCaseTestCompLifeLineColor(testCompLifeLineColor);
    setTestCaseTestCompLifeLineWidth(testCompLifeLineWidth);
    setTestCaseSequItemOptions(sequItemOptions);

    emit testCaseSettingsChanged(this);
}

}

