#include "testsystemsettings.hpp"

#include <mobatawidgets/ts/comrendertestsystem.hpp>

static const char compTextFontNameKey[] = "CompTextFontSeries";
static const char compTextFontSizeKey[] = "CompTextFontSize";
static const char compTextFontBoldKey[] = "CompTextFontBold";
static const char compTextFontItalicKey[] = "CompTextFontItalic";
static const char compTextColorKey[] = "CompTextFontColorName";
static const char compBoxWidthKey[] = "CompBoxWidth";
static const char compBoxHeightKey[] = "CompBoxHeight";
static const char compBoxColorKey[] = "CompBoxColorName";
static const char compBorderWidthKey[] = "CompBorderWidth";
static const char compBorderColorKey[] = "CompBorderColorName";
static const char portBoxWidthKey[] = "PortBoxWidth";
static const char portBoxHeightKey[] = "PortBoxHeight";
static const char portBoxColorKey[] = "PortBoxColorName";
static const char portBorderWidthKey[] = "PortBorderWidth";
static const char portBorderColorKey[] = "PortBorderColorName";
static const char linkLineWidthKey[] = "LinkLineWidth";
static const char linkLineColorKey[] = "LinkLineColorName";
static const char spaceToSutBoxKey[] = "SpaceToSutBox";
static const char tsBoxTextFontNameKey[] = "TestsystemBoxTextFontSeries";
static const char tsBoxTextFontSizeKey[] = "TestsystemBoxTextFontSize";
static const char tsBoxTextFontBoldKey[] = "TestsystemBoxTextFontBold";
static const char tsBoxTextFontItalicKey[] = "TestsystemBoxTextFontItalic";
static const char tsBoxTextColorKey[] = "TestsystemBoxTextFontColorName";
static const char tsBoxBoxWidthKey[] = "TestsystemBoxBoxWidth";
static const char tsBoxBoxHeightKey[] = "TestsystemBoxBoxHeight";
static const char tsBoxBoxColorKey[] = "TestsystemBoxBoxColorName";
static const char tsBoxBorderWidthKey[] = "TestsystemBoxBorderWidth";
static const char tsBoxBorderColorKey[] = "TestsystemBoxBorderColorName";
static const char tsBoxMarginKey[] = "TestsystemBoxMargin";
static const char tsBoxRadiusKey[] = "TestsystemBoxRadius";
static const char groupPostfix[] = "TestsystemSettings";

namespace distestproject {

DisTestTestSystemSettings::DisTestTestSystemSettings()
    : _compTextFontSeries(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textFont().family()),
      _compTextFontSize(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textFont().pointSize()),
      _compTextFontBold(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textFont().bold()),
      _compTextFontItalic(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textFont().italic()),
      _compTextColorName(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textColor().name()),
      _compBoxWidth(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().size().width()),
      _compBoxHeight(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().size().height()),
      _compBoxColorName(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().getColor().name()),
      _compBorderWidth(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().pen().width()),
      _compBorderColorName(view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().pen().color().name()),
      _portBoxWidth(view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().size().width()),
      _portBoxHeight(view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().size().height()),
      _portBoxColorName(view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().getColor().name()),
      _portBorderWidth(view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().pen().width()),
      _portBorderColorName(view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().pen().color().name()),
      _linkLineWidth(view::ts::ComRenderTestSystem::defaultTestSystemLinkOptions().pen().width()),
      _linkLineColorName(view::ts::ComRenderTestSystem::defaultTestSystemLinkOptions().pen().color().name()),
      _spaceToSuTBox(view::ts::ComRenderTestSystem::defaultSpaceToSutBox()),
      _testSystemBoxTextFontSeries(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textFont().family()),
      _testSystemBoxTextFontSize(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textFont().pointSize()),
      _testSystemBoxTextFontBold(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textFont().bold()),
      _testSystemBoxTextFontItalic(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textFont().italic()),
      _testSystemBoxTextColorName(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textColor().name()),
      _testSystemBoxBoxWidth(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().size().width()),
      _testSystemBoxBoxHeight(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().size().height()),
      _testSystemBoxBoxColorName(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().getColor().name()),
      _testSystemBoxBorderWidth(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().pen().width()),
      _testSystemBoxBorderColorName(view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().pen().color().name()),
      _testSystemBoxMargin(view::ts::ComRenderTestSystem::defaultTestSystemBoxMarginSpace()),
      _testSystemBoxRadius(view::ts::ComRenderTestSystem::defaultTestSystemBoxRadius())
{
  // Do nothing
}

DisTestTestSystemSettings::DisTestTestSystemSettings(DisTestTestSystemSettings const* source)
  : _compTextFontSeries(source ? source->_compTextFontSeries : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textFont().family()),
    _compTextFontSize(source ? source->_compTextFontSize : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textFont().pointSize()),
    _compTextFontBold(source ? source->_compTextFontBold : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textFont().bold()),
    _compTextFontItalic(source ? source->_compTextFontItalic : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textFont().italic()),
    _compTextColorName(source ? source->_compTextColorName : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().textColor().name()),
    _compBoxWidth(source ? source->_compBoxWidth : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().size().width()),
    _compBoxHeight(source ? source->_compBoxHeight : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().size().height()),
    _compBoxColorName(source ? source->_compBoxColorName : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().getColor().name()),
    _compBorderWidth(source ? source->_compBorderWidth : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().pen().width()),
    _compBorderColorName(source ? source->_compBorderColorName : view::ts::ComRenderTestSystem::defaultTestSystemCompOptions().pen().color().name()),
    _portBoxWidth(source ? source->_portBoxWidth : view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().size().width()),
    _portBoxHeight(source ? source->_portBoxHeight : view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().size().height()),
    _portBoxColorName(source ? source->_portBoxColorName : view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().getColor().name()),
    _portBorderWidth(source ? source->_portBorderWidth : view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().pen().width()),
    _portBorderColorName(source ? source->_portBorderColorName : view::ts::ComRenderTestSystem::defaultTestSystemPortOptions().pen().color().name()),
    _linkLineWidth(source ? source->_linkLineWidth : view::ts::ComRenderTestSystem::defaultTestSystemLinkOptions().pen().width()),
    _linkLineColorName(source ? source->_linkLineColorName : view::ts::ComRenderTestSystem::defaultTestSystemLinkOptions().pen().color().name()),
    _spaceToSuTBox(source ? source->_spaceToSuTBox : view::ts::ComRenderTestSystem::defaultSpaceToSutBox()),
    _testSystemBoxTextFontSeries(source ? source->_testSystemBoxTextFontSeries : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textFont().family()),
    _testSystemBoxTextFontSize(source ? source->_testSystemBoxTextFontSize : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textFont().pointSize()),
    _testSystemBoxTextFontBold(source ? source->_testSystemBoxTextFontBold : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textFont().bold()),
    _testSystemBoxTextFontItalic(source ? source->_testSystemBoxTextFontItalic : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textFont().italic()),
    _testSystemBoxTextColorName(source ? source->_testSystemBoxTextColorName : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().textColor().name()),
    _testSystemBoxBoxWidth(source ? source->_testSystemBoxBoxWidth : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().size().width()),
    _testSystemBoxBoxHeight(source ? source->_testSystemBoxBoxHeight : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().size().height()),
    _testSystemBoxBoxColorName(source ? source->_testSystemBoxBoxColorName : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().getColor().name()),
    _testSystemBoxBorderWidth(source ? source->_testSystemBoxBorderWidth : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().pen().width()),
    _testSystemBoxBorderColorName(source ? source->_testSystemBoxBorderColorName : view::ts::ComRenderTestSystem::defaultTestSystemBoxOptions().pen().color().name()),
    _testSystemBoxMargin(source ? source->_testSystemBoxMargin : view::ts::ComRenderTestSystem::defaultTestSystemBoxMarginSpace()),
    _testSystemBoxRadius(source ? source->_testSystemBoxRadius : view::ts::ComRenderTestSystem::defaultTestSystemBoxRadius())
{}

DisTestTestSystemSettings::DisTestTestSystemSettings(const DisTestTestSystemSettings &source)
    : _compTextFontSeries(source._compTextFontSeries),
      _compTextFontSize(source._compTextFontSize),
      _compTextFontBold(source._compTextFontBold),
      _compTextFontItalic(source._compTextFontItalic),
      _compTextColorName(source._compTextColorName),
      _compBoxWidth(source._compBoxWidth),
      _compBoxHeight(source._compBoxHeight),
      _compBoxColorName(source._compBoxColorName),
      _compBorderWidth(source._compBorderWidth),
      _compBorderColorName(source._compBorderColorName),
      _portBoxWidth(source._portBoxWidth),
      _portBoxHeight(source._portBoxHeight),
      _portBoxColorName(source._portBoxColorName),
      _portBorderWidth(source._portBorderWidth),
      _portBorderColorName(source._portBorderColorName),
      _linkLineWidth(source._linkLineWidth),
      _linkLineColorName(source._linkLineColorName),
      _spaceToSuTBox(source._spaceToSuTBox),
      _testSystemBoxTextFontSeries(source._testSystemBoxTextFontSeries),
      _testSystemBoxTextFontSize(source._testSystemBoxTextFontSize),
      _testSystemBoxTextFontBold(source._testSystemBoxTextFontBold),
      _testSystemBoxTextFontItalic(source._testSystemBoxTextFontItalic),
      _testSystemBoxTextColorName(source._testSystemBoxTextColorName),
      _testSystemBoxBoxWidth(source._testSystemBoxBoxWidth),
      _testSystemBoxBoxHeight(source._testSystemBoxBoxHeight),
      _testSystemBoxBoxColorName(source._testSystemBoxBoxColorName),
      _testSystemBoxBorderWidth(source._testSystemBoxBorderWidth),
      _testSystemBoxBorderColorName(source._testSystemBoxBorderColorName),
      _testSystemBoxMargin(source._testSystemBoxMargin),
      _testSystemBoxRadius(source._testSystemBoxRadius)
{
    // Do nothing
}

void DisTestTestSystemSettings::toSettings(const QString &category, QSettings *settings) const
{
    QString group(QString::fromLatin1(groupPostfix));
    if (!category.isEmpty())
    {
        group.prepend(category);
    }

    settings->beginGroup(group);
    settings->setValue(QString::fromLatin1(compTextFontNameKey), _compTextFontSeries);
    settings->setValue(QString::fromLatin1(compTextFontSizeKey), _compTextFontSize);
    settings->setValue(QString::fromLatin1(compTextFontBoldKey), _compTextFontBold);
    settings->setValue(QString::fromLatin1(compTextFontItalicKey), _compTextFontItalic);
    settings->setValue(QString::fromLatin1(compTextColorKey), _compTextColorName);
    settings->setValue(QString::fromLatin1(compBoxWidthKey), _compBoxWidth);
    settings->setValue(QString::fromLatin1(compBoxHeightKey), _compBoxHeight);
    settings->setValue(QString::fromLatin1(compBoxColorKey), _compBoxColorName);
    settings->setValue(QString::fromLatin1(compBorderWidthKey), _compBorderWidth);
    settings->setValue(QString::fromLatin1(compBorderColorKey), _compBorderColorName);
    settings->setValue(QString::fromLatin1(portBoxWidthKey), _portBoxWidth);
    settings->setValue(QString::fromLatin1(portBoxHeightKey), _portBoxHeight);
    settings->setValue(QString::fromLatin1(portBoxColorKey), _portBoxColorName);
    settings->setValue(QString::fromLatin1(portBorderWidthKey), _portBorderWidth);
    settings->setValue(QString::fromLatin1(portBorderColorKey), _portBorderColorName);
    settings->setValue(QString::fromLatin1(linkLineWidthKey), _linkLineWidth);
    settings->setValue(QString::fromLatin1(linkLineColorKey), _linkLineColorName);
    settings->setValue(QString::fromLatin1(spaceToSutBoxKey), _spaceToSuTBox);
    settings->setValue(QString::fromLatin1(tsBoxTextFontNameKey), _testSystemBoxTextFontSeries);
    settings->setValue(QString::fromLatin1(tsBoxTextFontSizeKey), _testSystemBoxTextFontSize);
    settings->setValue(QString::fromLatin1(tsBoxTextFontBoldKey), _testSystemBoxTextFontBold);
    settings->setValue(QString::fromLatin1(tsBoxTextFontItalicKey), _testSystemBoxTextFontItalic);
    settings->setValue(QString::fromLatin1(tsBoxTextColorKey), _testSystemBoxTextColorName);
    settings->setValue(QString::fromLatin1(tsBoxBoxWidthKey), _testSystemBoxBoxWidth);
    settings->setValue(QString::fromLatin1(tsBoxBoxHeightKey), _testSystemBoxBoxHeight);
    settings->setValue(QString::fromLatin1(tsBoxBoxColorKey), _testSystemBoxBoxColorName);
    settings->setValue(QString::fromLatin1(tsBoxBorderWidthKey), _testSystemBoxBorderWidth);
    settings->setValue(QString::fromLatin1(tsBoxBorderColorKey), _testSystemBoxBorderColorName);
    settings->setValue(QString::fromLatin1(tsBoxMarginKey), _testSystemBoxMargin);
    settings->setValue(QString::fromLatin1(tsBoxRadiusKey), _testSystemBoxRadius);
    settings->endGroup();
}

void DisTestTestSystemSettings::fromSettings(const QString &category, const QSettings *settings)
{
    QString group(QString::fromLatin1(groupPostfix));
    if (!category.isEmpty())
    {
        group.prepend(category);
    }

    if (!settings->childGroups().contains(group))
    {
        return;
    }

    group.append(QChar::fromLatin1('/'));
    _compTextFontSeries = settings->value(group + QString::fromLatin1(compTextFontNameKey), _compTextFontSeries).toString();
    _compTextFontSize = settings->value(group + QString::fromLatin1(compTextFontSizeKey), _compTextFontSize).toInt();
    _compTextFontBold = settings->value(group + QString::fromLatin1(compTextFontBoldKey), _compTextFontBold).toBool();
    _compTextFontItalic = settings->value(group + QString::fromLatin1(compTextFontItalicKey), _compTextFontItalic).toBool();
    _compTextColorName = settings->value(group + QString::fromLatin1(compTextColorKey), _compTextColorName).toString();
    _compBoxWidth = settings->value(group + QString::fromLatin1(compBoxWidthKey), _compBoxWidth).toDouble();
    _compBoxHeight = settings->value(group + QString::fromLatin1(compBoxHeightKey), _compBoxHeight).toDouble();
    _compBoxColorName = settings->value(group + QString::fromLatin1(compBoxColorKey), _compBoxColorName).toString();
    _compBorderWidth = settings->value(group + QString::fromLatin1(compBorderWidthKey), _compBorderWidth).toInt();
    _compBorderColorName = settings->value(group + QString::fromLatin1(compBorderColorKey), _compBorderColorName).toString();
    _portBoxWidth = settings->value(group + QString::fromLatin1(portBoxWidthKey), _portBoxWidth).toDouble();
    _portBoxHeight = settings->value(group + QString::fromLatin1(portBoxHeightKey), _portBoxHeight).toDouble();
    _portBoxColorName = settings->value(group + QString::fromLatin1(portBoxColorKey), _portBoxColorName).toString();
    _portBorderWidth = settings->value(group + QString::fromLatin1(portBorderWidthKey), _portBorderWidth).toInt();
    _portBorderColorName = settings->value(group + QString::fromLatin1(portBorderColorKey), _portBorderColorName).toString();
    _linkLineWidth = settings->value(group + QString::fromLatin1(linkLineWidthKey), _linkLineWidth).toInt();
    _linkLineColorName = settings->value(group + QString::fromLatin1(linkLineColorKey), _linkLineColorName).toString();
    _spaceToSuTBox = settings->value(group + QString::fromLatin1(spaceToSutBoxKey), _spaceToSuTBox).toDouble();
    _testSystemBoxTextFontSeries = settings->value(group + QString::fromLatin1(tsBoxTextFontNameKey), _testSystemBoxTextFontSeries).toString();
    _testSystemBoxTextFontSize = settings->value(group + QString::fromLatin1(tsBoxTextFontSizeKey), _testSystemBoxTextFontSize).toInt();
    _testSystemBoxTextFontBold = settings->value(group + QString::fromLatin1(tsBoxTextFontBoldKey), _testSystemBoxTextFontBold).toBool();
    _testSystemBoxTextFontItalic = settings->value(group + QString::fromLatin1(tsBoxTextFontItalicKey), _testSystemBoxTextFontItalic).toBool();
    _testSystemBoxTextColorName = settings->value(group + QString::fromLatin1(tsBoxTextColorKey), _testSystemBoxTextColorName).toString();
    _testSystemBoxBoxWidth = settings->value(group + QString::fromLatin1(tsBoxBoxWidthKey), _testSystemBoxBoxWidth).toDouble();
    _testSystemBoxBoxHeight = settings->value(group + QString::fromLatin1(tsBoxBoxHeightKey), _testSystemBoxBoxHeight).toDouble();
    _testSystemBoxBoxColorName = settings->value(group + QString::fromLatin1(tsBoxBoxColorKey), _testSystemBoxBoxColorName).toString();
    _testSystemBoxBorderWidth = settings->value(group + QString::fromLatin1(tsBoxBorderWidthKey), _testSystemBoxBorderWidth).toInt();
    _testSystemBoxBorderColorName = settings->value(group + QString::fromLatin1(tsBoxBorderColorKey), _testSystemBoxBorderColorName).toString();
    _testSystemBoxMargin = settings->value(group + QString::fromLatin1(tsBoxMarginKey), _testSystemBoxMargin).toDouble();
    _testSystemBoxRadius = settings->value(group + QString::fromLatin1(tsBoxRadiusKey), _testSystemBoxRadius).toDouble();
}

view::graph::NodeOptions DisTestTestSystemSettings::compOptionsFromSettings() const
{
    QFont compTextFont(_compTextFontSeries, _compTextFontSize);
    compTextFont.setBold(_compTextFontBold);
    compTextFont.setItalic(_compTextFontItalic);

    view::graph::NodeOptions compOptions;
    compOptions.setTextFont(compTextFont);
    compOptions.setTextColor(QColor(_compTextColorName));
    compOptions.setSize(_compBoxWidth, _compBoxHeight);
    compOptions.setColor(QColor(_compBoxColorName));
    compOptions.setPen(QPen(QColor(_compBorderColorName), _compBorderWidth));

    return compOptions;
}

view::graph::NodeOptions DisTestTestSystemSettings::portOptionsFromSettings() const
{
    view::graph::NodeOptions portOptions;
    portOptions.setSize(_portBoxWidth, _portBoxHeight);
    portOptions.setColor(QColor(_portBoxColorName));
    portOptions.setPen(QPen(QColor(_portBorderColorName), _portBorderWidth));

    return portOptions;
}

view::graph::ArcOptions DisTestTestSystemSettings::linkOptionsFromSettings() const
{
    view::graph::ArcOptions linkOptions;
    linkOptions.setPen(QPen(QColor(_linkLineColorName), _linkLineWidth));

    return linkOptions;
}

view::graph::NodeOptions DisTestTestSystemSettings::testSystemBoxOptionsFromSettings() const
{
    QFont testSystemBoxTextFont(_testSystemBoxTextFontSeries, _testSystemBoxTextFontSize);
    testSystemBoxTextFont.setBold(_testSystemBoxTextFontBold);
    testSystemBoxTextFont.setItalic(_testSystemBoxTextFontItalic);

    view::graph::NodeOptions testSystemBoxOptions;
    testSystemBoxOptions.setTextFont(testSystemBoxTextFont);
    testSystemBoxOptions.setTextColor(QColor(_testSystemBoxTextColorName));
    testSystemBoxOptions.setSize(_testSystemBoxBoxWidth, _testSystemBoxBoxHeight);
    testSystemBoxOptions.setColor(QColor(_testSystemBoxBoxColorName));
    testSystemBoxOptions.setPen(QPen(QColor(_testSystemBoxBorderColorName), _testSystemBoxBorderWidth));

    return testSystemBoxOptions;
}

const QString &DisTestTestSystemSettings::compTextFontSeries() const
{
    return _compTextFontSeries;
}

void DisTestTestSystemSettings::setCompTextFontSeries(const QString &fontName)
{
    _compTextFontSeries = fontName;
}

const int &DisTestTestSystemSettings::compTextFontSize() const
{
    return _compTextFontSize;
}

void DisTestTestSystemSettings::setCompTextFontSize(const int fontSize)
{
    _compTextFontSize = fontSize;
}

const bool &DisTestTestSystemSettings::compTextFontBold() const
{
    return _compTextFontBold;
}

void DisTestTestSystemSettings::setCompTextFontBold(const bool isBold)
{
    _compTextFontBold = isBold;
}

const bool &DisTestTestSystemSettings::compTextFontItalic() const
{
    return _compTextFontItalic;
}

void DisTestTestSystemSettings::setCompTextFontItalic(const bool isItalic)
{
    _compTextFontItalic = isItalic;
}

const QString &DisTestTestSystemSettings::compTextColorName() const
{
    return _compTextColorName;
}

void DisTestTestSystemSettings::setCompTextColorName(const QString &colorName)
{
    _compTextColorName = colorName;
}

const qreal &DisTestTestSystemSettings::compBoxWidth() const
{
    return _compBoxWidth;
}

void DisTestTestSystemSettings::setCompBoxWidth(const qreal width)
{
    _compBoxWidth = width;
}

const qreal &DisTestTestSystemSettings::compBoxHeight() const
{
    return _compBoxHeight;
}

void DisTestTestSystemSettings::setCompBoxHeight(const qreal height)
{
    _compBoxHeight = height;
}

const QString &DisTestTestSystemSettings::compBoxColorName() const
{
    return _compBoxColorName;
}

void DisTestTestSystemSettings::setCompBoxColorName(const QString &colorName)
{
    _compBoxColorName = colorName;
}

const int &DisTestTestSystemSettings::compBorderWidth() const
{
    return _compBorderWidth;
}

void DisTestTestSystemSettings::setCompBorderWidth(const int width)
{
    _compBorderWidth = width;
}

const QString &DisTestTestSystemSettings::compBorderColorName() const
{
    return _compBorderColorName;
}

void DisTestTestSystemSettings::setCompBorderColorName(const QString &colorName)
{
    _compBorderColorName = colorName;
}

const qreal &DisTestTestSystemSettings::portBoxWidth() const
{
    return _portBoxWidth;
}

void DisTestTestSystemSettings::setPortBoxWidth(const qreal width)
{
    _portBoxWidth = width;
}

const qreal &DisTestTestSystemSettings::portBoxHeight() const
{
    return _portBoxHeight;
}

void DisTestTestSystemSettings::setPortBoxHeight(const qreal height)
{
    _portBoxHeight = height;
}

const QString &DisTestTestSystemSettings::portBoxColorName() const
{
    return _portBoxColorName;
}

void DisTestTestSystemSettings::setPortBoxColorName(const QString &colorName)
{
    _portBoxColorName = colorName;
}

const int &DisTestTestSystemSettings::portBorderWidth() const
{
    return _portBorderWidth;
}

void DisTestTestSystemSettings::setPortBorderWidth(const int width)
{
    _portBorderWidth = width;
}

const QString &DisTestTestSystemSettings::portBorderColorName() const
{
    return _portBorderColorName;
}

void DisTestTestSystemSettings::setPortBorderColorName(const QString &colorName)
{
    _portBorderColorName = colorName;
}

const int &DisTestTestSystemSettings::linkLineWidth() const
{
    return _linkLineWidth;
}

void DisTestTestSystemSettings::setLinkLineWidth(const int width)
{
    _linkLineWidth = width;
}

const QString &DisTestTestSystemSettings::linkLineColorName() const
{
    return _linkLineColorName;
}

void DisTestTestSystemSettings::setLinkLineColorName(const QString &colorName)
{
    _linkLineColorName = colorName;
}

const qreal &DisTestTestSystemSettings::spaceToSutBox() const
{
    return _spaceToSuTBox;
}

void DisTestTestSystemSettings::setSpaceToSutBox(const qreal margin)
{
    _spaceToSuTBox = margin;
}

const QString &DisTestTestSystemSettings::testSystemBoxTextFontSeries() const
{
    return _testSystemBoxTextFontSeries;
}

void DisTestTestSystemSettings::setTestSystemBoxTextFontSeries(const QString &fontName)
{
    _testSystemBoxTextFontSeries = fontName;
}

const int &DisTestTestSystemSettings::testSystemBoxTextFontSize() const
{
    return _testSystemBoxTextFontSize;
}

void DisTestTestSystemSettings::setTestSystemBoxTextFontSize(const int fontSize)
{
    _testSystemBoxTextFontSize = fontSize;
}

const bool &DisTestTestSystemSettings::testSystemBoxTextFontBold() const
{
    return _testSystemBoxTextFontBold;
}

void DisTestTestSystemSettings::setTestSystemBoxTextFontBold(const bool isBold)
{
    _testSystemBoxTextFontBold = isBold;
}

const bool &DisTestTestSystemSettings::testSystemBoxTextFontItalic() const
{
    return _testSystemBoxTextFontItalic;
}

void DisTestTestSystemSettings::setTestSystemBoxTextFontItalic(const bool isItalic)
{
    _testSystemBoxTextFontItalic = isItalic;
}

const QString &DisTestTestSystemSettings::testSystemBoxTextColorName() const
{
    return _testSystemBoxTextColorName;
}

void DisTestTestSystemSettings::setTestSystemBoxTextColorName(const QString &colorName)
{
    _testSystemBoxTextColorName = colorName;
}

const qreal &DisTestTestSystemSettings::testSystemBoxBoxWidth() const
{
    return _testSystemBoxBoxWidth;
}

void DisTestTestSystemSettings::setTestSystemBoxBoxWidth(const qreal width)
{
    _testSystemBoxBoxWidth = width;
}

const qreal &DisTestTestSystemSettings::testSystemBoxBoxHeight() const
{
    return _testSystemBoxBoxHeight;
}

void DisTestTestSystemSettings::setTestSystemBoxBoxHeight(const qreal height)
{
    _testSystemBoxBoxHeight = height;
}

const QString &DisTestTestSystemSettings::testSystemBoxBoxColorName() const
{
    return _testSystemBoxBoxColorName;
}

void DisTestTestSystemSettings::setTestSystemBoxBoxColorName(const QString &colorName)
{
    _testSystemBoxBoxColorName = colorName;
}

const int &DisTestTestSystemSettings::testSystemBoxBorderWidth() const
{
    return _testSystemBoxBorderWidth;
}

void DisTestTestSystemSettings::setTestSystemBoxBorderWidth(const int width)
{
    _testSystemBoxBorderWidth = width;
}

const QString &DisTestTestSystemSettings::testSystemBoxBorderColorName() const
{
    return _testSystemBoxBorderColorName;
}

void DisTestTestSystemSettings::setTestSystemBoxBorderColorName(const QString &colorName)
{
    _testSystemBoxBorderColorName = colorName;
}

const qreal &DisTestTestSystemSettings::testSystemBoxMargin() const
{
    return _testSystemBoxMargin;
}

void DisTestTestSystemSettings::setTestSystemBoxMargin(const qreal margin)
{
    _testSystemBoxMargin = margin;
}

const qreal &DisTestTestSystemSettings::testSystemBoxRadius() const
{
    return _testSystemBoxRadius;
}

void DisTestTestSystemSettings::setTestSystemBoxRadius(const qreal radius)
{
    _testSystemBoxRadius = radius;
}

}

