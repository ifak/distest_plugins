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
#ifndef DISTESTPROJECT_DISTESTTESTCASESETTINGS_HPP
#define DISTESTPROJECT_DISTESTTESTCASESETTINGS_HPP

#include "distestproject_global.hpp"

#include <QSettings>
#include <mobatawidgets/graph/types.hpp>

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT DisTestTestCaseSettings
{
public:
    DisTestTestCaseSettings();
    DisTestTestCaseSettings(const DisTestTestCaseSettings &source);

    void toSettings(const QString &category, QSettings *settings) const;
    void fromSettings(const QString &category, const QSettings *settings);

    view::graph::NodeOptions sutCompOptionsFromSettings() const;
    view::graph::NodeOptions testCompOptionsFromSettings() const;
    view::graph::ArcOptions sequenceItemOptionsFromSettings() const;

    const QString& sutCompTextFontSeries() const;
    void setSutCompTextFontSeries(const QString &fontName);
    const int& sutCompTextFontSize() const;
    void setSutCompTextFontSize(const int fontSize);
    const bool& sutCompTextFontBold() const;
    void setSutCompTextFontBold(const bool isBold);
    const bool& sutCompTextFontItalic() const;
    void setSutCompTextFontItalic(const bool isItalic);
    const QString& sutCompTextColorName() const;
    void setSutCompTextColorName(const QString &colorName);
    const qreal& sutCompBoxWidth() const;
    void setSutCompBoxWidth(const qreal width);
    const qreal& sutCompBoxHeight() const;
    void setSutCompBoxHeight(const qreal height);
    const QString& sutCompBoxColorName() const;
    void setSutCompBoxColorName(const QString &colorName);
    const int& sutCompBorderWidth() const;
    void setSutCompBorderWidth(const int width);
    const QString& sutCompBorderColorName() const;
    void setSutCompBorderColorName(const QString &colorName);
    const QString& sutCompLifeLineColorName() const;
    void setSutCompLifeLineColorName(const QString &colorName);
    const int& sutCompLifeLineWidth() const;
    void setSutCompLifeLineWidth(const int width);

    const QString& testCompTextFontSeries() const;
    void setTestCompTextFontSeries(const QString &fontName);
    const int& testCompTextFontSize() const;
    void setTestCompTextFontSize(const int fontSize);
    const bool& testCompTextFontBold() const;
    void setTestCompTextFontBold(const bool isBold);
    const bool& testCompTextFontItalic() const;
    void setTestCompTextFontItalic(const bool isItalic);
    const QString& testCompTextColorName() const;
    void setTestCompTextColorName(const QString &colorName);
    const qreal& testCompBoxWidth() const;
    void setTestCompBoxWidth(const qreal width);
    const qreal& testCompBoxHeight() const;
    void setTestCompBoxHeight(const qreal height);
    const QString& testCompBoxColorName() const;
    void setTestCompBoxColorName(const QString &colorName);
    const int& testCompBorderWidth() const;
    void setTestCompBorderWidth(const int width);
    const QString& testCompBorderColorName() const;
    void setTestCompBorderColorName(const QString &colorName);
    const QString& testCompLifeLineColorName() const;
    void setTestCompLifeLineColorName(const QString &colorName);
    const int& testCompLifeLineWidth() const;
    void setTestCompLifeLineWidth(const int width);

    const QString& sequItemTextFontSeries() const;
    void setSequItemTextFontSeries(const QString &fontName);
    const int& sequItemTextFontSize() const;
    void setSequItemTextFontSize(const int fontSize);
    const bool& sequItemTextFontBold() const;
    void setSequItemTextFontBold(const bool isBold);
    const bool& sequItemTextFontItalic() const;
    void setSequItemTextFontItalic(const bool isItalic);
    const QString& sequItemTextColorName() const;
    void setSequItemTextColorName(const QString &colorName);
    const int& sequItemLineWidth() const;
    void setSequItemLineWidth(const int width);
    const QString& sequItemLineColorName() const;
    void setSequItemLineColorName(const QString &colorName);

private:
    QString _sutCompTextFontSeries;
    int     _sutCompTextFontSize;
    bool    _sutCompTextFontBold;
    bool    _sutCompTextFontItalic;
    QString _sutCompTextColorName;
    qreal   _sutCompBoxWidth;
    qreal   _sutCompBoxHeight;
    QString _sutCompBoxColorName;
    int     _sutCompBorderWidth;
    QString _sutCompBorderColorName;
    QString _sutCompLifeLineColorName;
    int     _sutCompLifeLineWidth;
    QString _testCompTextFontSeries;
    int     _testCompTextFontSize;
    bool    _testCompTextFontBold;
    bool    _testCompTextFontItalic;
    QString _testCompTextColorName;
    qreal   _testCompBoxWidth;
    qreal   _testCompBoxHeight;
    QString _testCompBoxColorName;
    int     _testCompBorderWidth;
    QString _testCompBorderColorName;
    QString _testCompLifeLineColorName;
    int     _testCompLifeLineWidth;
    QString _sequItemTextFontSeries;
    int     _sequItemTextFontSize;
    bool    _sequItemTextFontBold;
    bool    _sequItemTextFontItalic;
    QString _sequItemTextColorName;
    int     _sequItemLineWidth;
    QString _sequItemLineColorName;
};

inline bool operator==(const DisTestTestCaseSettings &p1, const DisTestTestCaseSettings &p2)
{
    return (!p1.sutCompTextFontSeries().compare(p2.sutCompTextFontSeries()))
            && (p1.sutCompTextFontSize() == p2.sutCompTextFontSize())
            && (p1.sutCompTextFontBold() == p2.sutCompTextFontBold())
            && (p1.sutCompTextFontItalic() == p2.sutCompTextFontItalic())
            && (!p1.sutCompTextColorName().compare(p2.sutCompTextColorName()))
            && (p1.sutCompBoxWidth() == p2.sutCompBoxWidth())
            && (p1.sutCompBoxHeight() == p2.sutCompBoxHeight())
            && (!p1.sutCompBoxColorName().compare(p2.sutCompBoxColorName()))
            && (p1.sutCompBorderWidth() == p2.sutCompBorderWidth())
            && (!p1.sutCompBorderColorName().compare(p2.sutCompBorderColorName()))
            && (!p1.sutCompLifeLineColorName().compare(p2.sutCompLifeLineColorName()))
            && (p1.sutCompLifeLineWidth() == p2.sutCompLifeLineWidth())
            && (!p1.testCompTextFontSeries().compare(p2.testCompTextFontSeries()))
            && (p1.testCompTextFontSize() == p2.testCompTextFontSize())
            && (p1.testCompTextFontBold() == p2.testCompTextFontBold())
            && (p1.testCompTextFontItalic() == p2.testCompTextFontItalic())
            && (!p1.testCompTextColorName().compare(p2.testCompTextColorName()))
            && (p1.testCompBoxWidth() == p2.testCompBoxWidth())
            && (p1.testCompBoxHeight() == p2.testCompBoxHeight())
            && (!p1.testCompBoxColorName().compare(p2.testCompBoxColorName()))
            && (p1.testCompBorderWidth() == p2.testCompBorderWidth())
            && (!p1.testCompBorderColorName().compare(p2.testCompBorderColorName()))
            && (!p1.testCompLifeLineColorName().compare(p2.testCompLifeLineColorName()))
            && (p1.testCompLifeLineWidth() == p2.testCompLifeLineWidth())
            && (!p1.sequItemTextFontSeries().compare(p2.sequItemTextFontSeries()))
            && (p1.sequItemTextFontSize() == p2.sequItemTextFontSize())
            && (p1.sequItemTextFontBold() == p2.sequItemTextFontBold())
            && (p1.sequItemTextFontItalic() == p2.sequItemTextFontItalic())
            && (!p1.sequItemTextColorName().compare(p2.sequItemTextColorName()))
            && (p1.sequItemLineWidth() == p2.sequItemLineWidth())
            && (!p1.sequItemLineColorName().compare(p2.sequItemLineColorName()));
}

}

#endif // DISTESTTESTCASESETTINGS_HPP
