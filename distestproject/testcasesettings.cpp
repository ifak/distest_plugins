#include "testcasesettings.hpp"

#include <mobatawidgets/ts/comrendertestcase.hpp>

static const char sutCompTextFontNameKey[] = "SutCompTextFontSeries";
static const char sutCompTextFontSizeKey[] = "SutCompTextFontSize";
static const char sutCompTextFontBoldKey[] = "SutCompTextFontBold";
static const char sutCompTextFontItalicKey[] = "SutCompTextFontItalic";
static const char sutCompTextColorKey[] = "SutCompTextFontColorName";
static const char sutCompBoxWidthKey[] = "SutCompBoxWidth";
static const char sutCompBoxHeightKey[] = "SutCompBoxHeight";
static const char sutCompBoxColorKey[] = "SutCompBoxColorName";
static const char sutCompBorderWidthKey[] = "SutCompBorderWidth";
static const char sutCompBorderColorKey[] = "SutCompBorderColorName";
static const char sutCompLifeLineColorKey[] = "SutCompLifeLineColorName";
static const char sutCompLifeLineWidthKey[] = "SutCompLifeLineWidthName";
static const char testCompTextFontNameKey[] = "TestCompTextFontSeries";
static const char testCompTextFontSizeKey[] = "TestCompTextFontSize";
static const char testCompTextFontBoldKey[] = "TestCompTextFontBold";
static const char testCompTextFontItalicKey[] = "TestCompTextFontItalic";
static const char testCompTextColorKey[] = "TestCompTextFontColorName";
static const char testCompBoxWidthKey[] = "TestCompBoxWidth";
static const char testCompBoxHeightKey[] = "TestCompBoxHeight";
static const char testCompBoxColorKey[] = "TestCompBoxColorName";
static const char testCompBorderWidthKey[] = "TestCompBorderWidth";
static const char testCompBorderColorKey[] = "TestCompBorderColorName";
static const char testCompLifeLineColorKey[] = "TestCompLifeLineColorName";
static const char testCompLifeLineWidthKey[] = "TestCompLifeLineWidthName";
static const char sequItemTextFontNameKey[] = "SequItemTextFontSeries";
static const char sequItemTextFontSizeKey[] = "SequItemTextFontSize";
static const char sequItemTextFontBoldKey[] = "SequItemTextFontBold";
static const char sequItemTextFontItalicKey[] = "SequItemTextFontItalic";
static const char sequItemTextColorKey[] = "SequItemTextFontColorName";
static const char sequItemLineWidthKey[] = "SequItemLineWidth";
static const char sequItemLineColorKey[] = "SequItemLineColorName";
static const char groupPostfix[] = "TestCaseSettings";

namespace distestproject {

DisTestTestCaseSettings::DisTestTestCaseSettings()
    : _sutCompTextFontSeries(view::ts::ComRenderTestCase::defaultSutCompOptions().textFont().family()),
      _sutCompTextFontSize(view::ts::ComRenderTestCase::defaultSutCompOptions().textFont().pointSize()),
      _sutCompTextFontBold(view::ts::ComRenderTestCase::defaultSutCompOptions().textFont().bold()),
      _sutCompTextFontItalic(view::ts::ComRenderTestCase::defaultSutCompOptions().textFont().italic()),
      _sutCompTextColorName(view::ts::ComRenderTestCase::defaultSutCompOptions().textColor().name()),
      _sutCompBoxWidth(view::ts::ComRenderTestCase::defaultSutCompOptions().size().width()),
      _sutCompBoxHeight(view::ts::ComRenderTestCase::defaultSutCompOptions().size().height()),
      _sutCompBoxColorName(view::ts::ComRenderTestCase::defaultSutCompOptions().getColor().name()),
      _sutCompBorderWidth(view::ts::ComRenderTestCase::defaultSutCompOptions().pen().width()),
      _sutCompBorderColorName(view::ts::ComRenderTestCase::defaultSutCompOptions().pen().color().name()),
      _sutCompLifeLineColorName(view::ts::ComRenderTestCase::defaultSutLifeLineColor().name()),
      _sutCompLifeLineWidth(view::ts::ComRenderTestCase::defaultSutLifeLineWidth()),
      _testCompTextFontSeries(view::ts::ComRenderTestCase::defaultTestCompOptions().textFont().family()),
      _testCompTextFontSize(view::ts::ComRenderTestCase::defaultTestCompOptions().textFont().pointSize()),
      _testCompTextFontBold(view::ts::ComRenderTestCase::defaultTestCompOptions().textFont().bold()),
      _testCompTextFontItalic(view::ts::ComRenderTestCase::defaultTestCompOptions().textFont().italic()),
      _testCompTextColorName(view::ts::ComRenderTestCase::defaultTestCompOptions().textColor().name()),
      _testCompBoxWidth(view::ts::ComRenderTestCase::defaultTestCompOptions().size().width()),
      _testCompBoxHeight(view::ts::ComRenderTestCase::defaultTestCompOptions().size().height()),
      _testCompBoxColorName(view::ts::ComRenderTestCase::defaultTestCompOptions().getColor().name()),
      _testCompBorderWidth(view::ts::ComRenderTestCase::defaultTestCompOptions().pen().width()),
      _testCompBorderColorName(view::ts::ComRenderTestCase::defaultTestCompOptions().pen().color().name()),
      _testCompLifeLineColorName(view::ts::ComRenderTestCase::defaultTestLifeLineColor().name()),
      _testCompLifeLineWidth(view::ts::ComRenderTestCase::defaultTestLifeLineWidth()),
      _sequItemTextFontSeries(view::ts::ComRenderTestCase::defaultArcOptions().textFont().family()),
      _sequItemTextFontSize(view::ts::ComRenderTestCase::defaultArcOptions().textFont().pointSize()),
      _sequItemTextFontBold(view::ts::ComRenderTestCase::defaultArcOptions().textFont().bold()),
      _sequItemTextFontItalic(view::ts::ComRenderTestCase::defaultArcOptions().textFont().italic()),
      _sequItemTextColorName(view::ts::ComRenderTestCase::defaultArcOptions().textColor().name()),
      _sequItemLineWidth(view::ts::ComRenderTestCase::defaultArcOptions().pen().width()),
      _sequItemLineColorName(view::ts::ComRenderTestCase::defaultArcOptions().pen().color().name())
{
    // Do nothing
}

DisTestTestCaseSettings::DisTestTestCaseSettings(const DisTestTestCaseSettings &source)
    : _sutCompTextFontSeries(source._sutCompTextFontSeries),
      _sutCompTextFontSize(source._sutCompTextFontSize),
      _sutCompTextFontBold(source._sutCompTextFontBold),
      _sutCompTextFontItalic(source._sutCompTextFontItalic),
      _sutCompTextColorName(source._sutCompTextColorName),
      _sutCompBoxWidth(source._sutCompBoxWidth),
      _sutCompBoxHeight(source._sutCompBoxHeight),
      _sutCompBoxColorName(source._sutCompBoxColorName),
      _sutCompBorderWidth(source._sutCompBorderWidth),
      _sutCompBorderColorName(source._sutCompBorderColorName),
      _sutCompLifeLineColorName(source._sutCompLifeLineColorName),
      _sutCompLifeLineWidth(source._sutCompLifeLineWidth),
      _testCompTextFontSeries(source._testCompTextFontSeries),
      _testCompTextFontSize(source._testCompTextFontSize),
      _testCompTextFontBold(source._testCompTextFontBold),
      _testCompTextFontItalic(source._testCompTextFontItalic),
      _testCompTextColorName(source._testCompTextColorName),
      _testCompBoxWidth(source._testCompBoxWidth),
      _testCompBoxHeight(source._testCompBoxHeight),
      _testCompBoxColorName(source._testCompBoxColorName),
      _testCompBorderWidth(source._testCompBorderWidth),
      _testCompBorderColorName(source._testCompBorderColorName),
      _testCompLifeLineColorName(source._testCompLifeLineColorName),
      _testCompLifeLineWidth(source._testCompLifeLineWidth),
      _sequItemTextFontSeries(source._sequItemTextFontSeries),
      _sequItemTextFontSize(source._sequItemTextFontSize),
      _sequItemTextFontBold(source._sequItemTextFontBold),
      _sequItemTextFontItalic(source._sequItemTextFontItalic),
      _sequItemTextColorName(source._sequItemTextColorName),
      _sequItemLineWidth(source._sequItemLineWidth),
      _sequItemLineColorName(source._sequItemLineColorName)
{
    // Do nothing
}

void DisTestTestCaseSettings::toSettings(const QString &category, QSettings *settings) const
{
    QString group(QString::fromLatin1(groupPostfix));
    if (!category.isEmpty())
    {
        group.prepend(category);
    }

    settings->beginGroup(group);
    settings->setValue(QString::fromLatin1(sutCompTextFontNameKey), _sutCompTextFontSeries);
    settings->setValue(QString::fromLatin1(sutCompTextFontSizeKey), _sutCompTextFontSize);
    settings->setValue(QString::fromLatin1(sutCompTextFontBoldKey), _sutCompTextFontBold);
    settings->setValue(QString::fromLatin1(sutCompTextFontItalicKey), _sutCompTextFontItalic);
    settings->setValue(QString::fromLatin1(sutCompTextColorKey), _sutCompTextColorName);
    settings->setValue(QString::fromLatin1(sutCompBoxWidthKey), _sutCompBoxWidth);
    settings->setValue(QString::fromLatin1(sutCompBoxHeightKey), _sutCompBoxHeight);
    settings->setValue(QString::fromLatin1(sutCompBoxColorKey), _sutCompBoxColorName);
    settings->setValue(QString::fromLatin1(sutCompBorderWidthKey), _sutCompBorderWidth);
    settings->setValue(QString::fromLatin1(sutCompBorderColorKey), _sutCompBorderColorName);
    settings->setValue(QString::fromLatin1(sutCompLifeLineColorKey), _sutCompLifeLineColorName);
    settings->setValue(QString::fromLatin1(sutCompLifeLineWidthKey), _sutCompLifeLineWidth);
    settings->setValue(QString::fromLatin1(testCompTextFontNameKey), _testCompTextFontSeries);
    settings->setValue(QString::fromLatin1(testCompTextFontSizeKey), _testCompTextFontSize);
    settings->setValue(QString::fromLatin1(testCompTextFontBoldKey), _testCompTextFontBold);
    settings->setValue(QString::fromLatin1(testCompTextFontItalicKey), _testCompTextFontItalic);
    settings->setValue(QString::fromLatin1(testCompTextColorKey), _testCompTextColorName);
    settings->setValue(QString::fromLatin1(testCompBoxWidthKey), _testCompBoxWidth);
    settings->setValue(QString::fromLatin1(testCompBoxHeightKey), _testCompBoxHeight);
    settings->setValue(QString::fromLatin1(testCompBoxColorKey), _testCompBoxColorName);
    settings->setValue(QString::fromLatin1(testCompBorderWidthKey), _testCompBorderWidth);
    settings->setValue(QString::fromLatin1(testCompBorderColorKey), _testCompBorderColorName);
    settings->setValue(QString::fromLatin1(testCompLifeLineColorKey), _testCompLifeLineColorName);
    settings->setValue(QString::fromLatin1(testCompLifeLineWidthKey), _testCompLifeLineWidth);
    settings->setValue(QString::fromLatin1(sequItemTextFontNameKey), _sequItemTextFontSeries);
    settings->setValue(QString::fromLatin1(sequItemTextFontSizeKey), _sequItemTextFontSize);
    settings->setValue(QString::fromLatin1(sequItemTextFontBoldKey), _sequItemTextFontBold);
    settings->setValue(QString::fromLatin1(sequItemTextFontItalicKey), _sequItemTextFontItalic);
    settings->setValue(QString::fromLatin1(sequItemTextColorKey), _sequItemTextColorName);
    settings->setValue(QString::fromLatin1(sequItemLineWidthKey), _sequItemLineWidth);
    settings->setValue(QString::fromLatin1(sequItemLineColorKey), _sequItemLineColorName);
    settings->endGroup();
}

void DisTestTestCaseSettings::fromSettings(const QString &category, const QSettings *settings)
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
    _sutCompTextFontSeries = settings->value(group + QString::fromLatin1(sutCompTextFontNameKey), _sutCompTextFontSeries).toString();
    _sutCompTextFontSize = settings->value(group + QString::fromLatin1(sutCompTextFontSizeKey), _sutCompTextFontSize).toInt();
    _sutCompTextFontBold = settings->value(group + QString::fromLatin1(sutCompTextFontBoldKey), _sutCompTextFontBold).toBool();
    _sutCompTextFontItalic = settings->value(group + QString::fromLatin1(sutCompTextFontItalicKey), _sutCompTextFontItalic).toBool();
    _sutCompTextColorName = settings->value(group + QString::fromLatin1(sutCompTextColorKey), _sutCompTextColorName).toString();
    _sutCompBoxWidth = settings->value(group + QString::fromLatin1(sutCompBoxWidthKey), _sutCompBoxWidth).toDouble();
    _sutCompBoxHeight = settings->value(group + QString::fromLatin1(sutCompBoxHeightKey), _sutCompBoxHeight).toDouble();
    _sutCompBoxColorName = settings->value(group + QString::fromLatin1(sutCompBoxColorKey), _sutCompBoxColorName).toString();
    _sutCompBorderWidth = settings->value(group + QString::fromLatin1(sutCompBorderWidthKey), _sutCompBorderWidth).toInt();
    _sutCompBorderColorName = settings->value(group + QString::fromLatin1(sutCompBorderColorKey), _sutCompBorderColorName).toString();
    _sutCompLifeLineColorName = settings->value(group + QString::fromLatin1(sutCompLifeLineColorKey), _sutCompLifeLineColorName).toString();
    _sutCompLifeLineWidth = settings->value(group + QString::fromLatin1(sutCompLifeLineWidthKey), _sutCompLifeLineWidth).toInt();
    _testCompTextFontSeries = settings->value(group + QString::fromLatin1(testCompTextFontNameKey), _testCompTextFontSeries).toString();
    _testCompTextFontSize = settings->value(group + QString::fromLatin1(testCompTextFontSizeKey), _testCompTextFontSize).toInt();
    _testCompTextFontBold = settings->value(group + QString::fromLatin1(testCompTextFontBoldKey), _testCompTextFontBold).toBool();
    _testCompTextFontItalic = settings->value(group + QString::fromLatin1(testCompTextFontItalicKey), _testCompTextFontItalic).toBool();
    _testCompTextColorName = settings->value(group + QString::fromLatin1(testCompTextColorKey), _testCompTextColorName).toString();
    _testCompBoxWidth = settings->value(group + QString::fromLatin1(testCompBoxWidthKey), _testCompBoxWidth).toDouble();
    _testCompBoxHeight = settings->value(group + QString::fromLatin1(testCompBoxHeightKey), _testCompBoxHeight).toDouble();
    _testCompBoxColorName = settings->value(group + QString::fromLatin1(testCompBoxColorKey), _testCompBoxColorName).toString();
    _testCompBorderWidth = settings->value(group + QString::fromLatin1(testCompBorderWidthKey), _testCompBorderWidth).toInt();
    _testCompBorderColorName = settings->value(group + QString::fromLatin1(testCompBorderColorKey), _testCompBorderColorName).toString();
    _testCompLifeLineColorName = settings->value(group + QString::fromLatin1(testCompLifeLineColorKey), _testCompLifeLineColorName).toString();
    _testCompLifeLineWidth = settings->value(group + QString::fromLatin1(testCompLifeLineWidthKey), _testCompLifeLineWidth).toInt();
    _sequItemTextFontSeries = settings->value(group + QString::fromLatin1(sequItemTextFontNameKey), _sequItemTextFontSeries).toString();
    _sequItemTextFontSize = settings->value(group + QString::fromLatin1(sequItemTextFontSizeKey), _sequItemTextFontSize).toInt();
    _sequItemTextFontBold = settings->value(group + QString::fromLatin1(sequItemTextFontBoldKey), _sequItemTextFontBold).toBool();
    _sequItemTextFontItalic = settings->value(group + QString::fromLatin1(sequItemTextFontItalicKey), _sequItemTextFontItalic).toBool();
    _sequItemTextColorName = settings->value(group + QString::fromLatin1(sequItemTextColorKey), _sequItemTextColorName).toString();
    _sequItemLineWidth = settings->value(group + QString::fromLatin1(sequItemLineWidthKey), _sequItemLineWidth).toInt();
    _sequItemLineColorName = settings->value(group + QString::fromLatin1(sequItemLineColorKey), _sequItemLineColorName).toString();
}

view::graph::NodeOptions DisTestTestCaseSettings::sutCompOptionsFromSettings() const
{
    QFont sutCompTextFont(_sutCompTextFontSeries, _sutCompTextFontSize);
    sutCompTextFont.setBold(_sutCompTextFontBold);
    sutCompTextFont.setItalic(_sutCompTextFontItalic);

    view::graph::NodeOptions sutCompOptions;
    sutCompOptions.setTextFont(sutCompTextFont);
    sutCompOptions.setTextColor(QColor(_sutCompTextColorName));
    sutCompOptions.setSize(_sutCompBoxWidth, _sutCompBoxHeight);
    sutCompOptions.setColor(QColor(_sutCompBoxColorName));
    sutCompOptions.setPen(QPen(QColor(_sutCompBorderColorName), _sutCompBorderWidth));

    return sutCompOptions;
}

view::graph::NodeOptions DisTestTestCaseSettings::testCompOptionsFromSettings() const
{
    QFont testCompTextFont(_testCompTextFontSeries, _testCompTextFontSize);
    testCompTextFont.setBold(_testCompTextFontBold);
    testCompTextFont.setItalic(_testCompTextFontItalic);

    view::graph::NodeOptions testCompOptions;
    testCompOptions.setTextFont(testCompTextFont);
    testCompOptions.setTextColor(QColor(_testCompTextColorName));
    testCompOptions.setSize(_testCompBoxWidth, _testCompBoxHeight);
    testCompOptions.setColor(QColor(_testCompBoxColorName));
    testCompOptions.setPen(QPen(QColor(_testCompBorderColorName), _testCompBorderWidth));

    return testCompOptions;
}

view::graph::ArcOptions DisTestTestCaseSettings::sequenceItemOptionsFromSettings() const
{
    QFont sequItemTextFont(_sequItemTextFontSeries, _sequItemTextFontSize);
    sequItemTextFont.setBold(_sequItemTextFontBold);
    sequItemTextFont.setItalic(_sequItemTextFontItalic);

    view::graph::ArcOptions arcOptions;
    arcOptions.setTextFont(sequItemTextFont);
    arcOptions.setTextColor(QColor(_sequItemTextColorName));
    arcOptions.setPen(QPen(QColor(_sequItemLineColorName), _sequItemLineWidth));

    return arcOptions;
}

const QString &DisTestTestCaseSettings::sutCompTextFontSeries() const
{
    return _sutCompTextFontSeries;
}

void DisTestTestCaseSettings::setSutCompTextFontSeries(const QString &fontName)
{
    _sutCompTextFontSeries = fontName;
}

const int &DisTestTestCaseSettings::sutCompTextFontSize() const
{
    return _sutCompTextFontSize;
}

void DisTestTestCaseSettings::setSutCompTextFontSize(const int fontSize)
{
    _sutCompTextFontSize = fontSize;
}

const bool &DisTestTestCaseSettings::sutCompTextFontBold() const
{
    return _sutCompTextFontBold;
}

void DisTestTestCaseSettings::setSutCompTextFontBold(const bool isBold)
{
    _sutCompTextFontBold = isBold;
}

const bool &DisTestTestCaseSettings::sutCompTextFontItalic() const
{
    return _sutCompTextFontItalic;
}

void DisTestTestCaseSettings::setSutCompTextFontItalic(const bool isItalic)
{
    _sutCompTextFontItalic = isItalic;
}

const QString &DisTestTestCaseSettings::sutCompTextColorName() const
{
    return _sutCompTextColorName;
}

void DisTestTestCaseSettings::setSutCompTextColorName(const QString &colorName)
{
    _sutCompTextColorName = colorName;
}

const qreal &DisTestTestCaseSettings::sutCompBoxWidth() const
{
    return _sutCompBoxWidth;
}

void DisTestTestCaseSettings::setSutCompBoxWidth(const qreal width)
{
    _sutCompBoxWidth = width;
}

const qreal &DisTestTestCaseSettings::sutCompBoxHeight() const
{
    return _sutCompBoxHeight;
}

void DisTestTestCaseSettings::setSutCompBoxHeight(const qreal height)
{
    _sutCompBoxHeight = height;
}

const QString &DisTestTestCaseSettings::sutCompBoxColorName() const
{
    return _sutCompBoxColorName;
}

void DisTestTestCaseSettings::setSutCompBoxColorName(const QString &colorName)
{
    _sutCompBoxColorName = colorName;
}

const int &DisTestTestCaseSettings::sutCompBorderWidth() const
{
    return _sutCompBorderWidth;
}

void DisTestTestCaseSettings::setSutCompBorderWidth(const int width)
{
    _sutCompBorderWidth = width;
}

const QString &DisTestTestCaseSettings::sutCompBorderColorName() const
{
    return _sutCompBorderColorName;
}

void DisTestTestCaseSettings::setSutCompBorderColorName(const QString &colorName)
{
    _sutCompBorderColorName = colorName;
}

const QString &DisTestTestCaseSettings::sutCompLifeLineColorName() const
{
    return _sutCompLifeLineColorName;
}

void DisTestTestCaseSettings::setSutCompLifeLineColorName(const QString &colorName)
{
    _sutCompLifeLineColorName = colorName;
}

const int &DisTestTestCaseSettings::sutCompLifeLineWidth() const
{
    return _sutCompLifeLineWidth;
}

void DisTestTestCaseSettings::setSutCompLifeLineWidth(const int width)
{
    _sutCompLifeLineWidth = width;
}

const QString &DisTestTestCaseSettings::testCompTextFontSeries() const
{
    return _testCompTextFontSeries;
}

void DisTestTestCaseSettings::setTestCompTextFontSeries(const QString &fontName)
{
    _testCompTextFontSeries = fontName;
}

const int &DisTestTestCaseSettings::testCompTextFontSize() const
{
    return _testCompTextFontSize;
}

void DisTestTestCaseSettings::setTestCompTextFontSize(const int fontSize)
{
    _testCompTextFontSize = fontSize;
}

const bool &DisTestTestCaseSettings::testCompTextFontBold() const
{
    return _testCompTextFontBold;
}

void DisTestTestCaseSettings::setTestCompTextFontBold(const bool isBold)
{
    _testCompTextFontBold = isBold;
}

const bool &DisTestTestCaseSettings::testCompTextFontItalic() const
{
    return _testCompTextFontItalic;
}

void DisTestTestCaseSettings::setTestCompTextFontItalic(const bool isItalic)
{
    _testCompTextFontItalic = isItalic;
}

const QString &DisTestTestCaseSettings::testCompTextColorName() const
{
    return _testCompTextColorName;
}

void DisTestTestCaseSettings::setTestCompTextColorName(const QString &colorName)
{
    _testCompTextColorName = colorName;
}

const qreal &DisTestTestCaseSettings::testCompBoxWidth() const
{
    return _testCompBoxWidth;
}

void DisTestTestCaseSettings::setTestCompBoxWidth(const qreal width)
{
    _testCompBoxWidth = width;
}

const qreal &DisTestTestCaseSettings::testCompBoxHeight() const
{
    return _testCompBoxHeight;
}

void DisTestTestCaseSettings::setTestCompBoxHeight(const qreal height)
{
    _testCompBoxHeight = height;
}

const QString &DisTestTestCaseSettings::testCompBoxColorName() const
{
    return _testCompBoxColorName;
}

void DisTestTestCaseSettings::setTestCompBoxColorName(const QString &colorName)
{
    _testCompBoxColorName = colorName;
}

const int &DisTestTestCaseSettings::testCompBorderWidth() const
{
    return _testCompBorderWidth;
}

void DisTestTestCaseSettings::setTestCompBorderWidth(const int width)
{
    _testCompBorderWidth = width;
}

const QString &DisTestTestCaseSettings::testCompBorderColorName() const
{
    return _testCompBorderColorName;
}

void DisTestTestCaseSettings::setTestCompBorderColorName(const QString &colorName)
{
    _testCompBorderColorName = colorName;
}

const QString &DisTestTestCaseSettings::testCompLifeLineColorName() const
{
    return _testCompLifeLineColorName;
}

void DisTestTestCaseSettings::setTestCompLifeLineColorName(const QString &colorName)
{
    _testCompLifeLineColorName = colorName;
}

const int &DisTestTestCaseSettings::testCompLifeLineWidth() const
{
    return _testCompLifeLineWidth;
}

void DisTestTestCaseSettings::setTestCompLifeLineWidth(const int width)
{
    _testCompLifeLineWidth = width;
}

const QString &DisTestTestCaseSettings::sequItemTextFontSeries() const
{
    return _sequItemTextFontSeries;
}

void DisTestTestCaseSettings::setSequItemTextFontSeries(const QString &fontName)
{
    _sequItemTextFontSeries = fontName;
}

const int &DisTestTestCaseSettings::sequItemTextFontSize() const
{
    return _sequItemTextFontSize;
}

void DisTestTestCaseSettings::setSequItemTextFontSize(const int fontSize)
{
    _sequItemTextFontSize = fontSize;
}

const bool &DisTestTestCaseSettings::sequItemTextFontBold() const
{
    return _sequItemTextFontBold;
}

void DisTestTestCaseSettings::setSequItemTextFontBold(const bool isBold)
{
    _sequItemTextFontBold = isBold;
}

const bool &DisTestTestCaseSettings::sequItemTextFontItalic() const
{
    return _sequItemTextFontItalic;
}

void DisTestTestCaseSettings::setSequItemTextFontItalic(const bool isItalic)
{
    _sequItemTextFontItalic = isItalic;
}

const QString &DisTestTestCaseSettings::sequItemTextColorName() const
{
    return _sequItemTextColorName;
}

void DisTestTestCaseSettings::setSequItemTextColorName(const QString &colorName)
{
    _sequItemTextColorName = colorName;
}

const int &DisTestTestCaseSettings::sequItemLineWidth() const
{
    return _sequItemLineWidth;
}

void DisTestTestCaseSettings::setSequItemLineWidth(const int width)
{
    _sequItemLineWidth = width;
}

const QString &DisTestTestCaseSettings::sequItemLineColorName() const
{
    return _sequItemLineColorName;
}

void DisTestTestCaseSettings::setSequItemLineColorName(const QString &colorName)
{
    _sequItemLineColorName = colorName;
}

}



