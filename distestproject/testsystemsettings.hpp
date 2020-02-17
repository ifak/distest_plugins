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
#ifndef DISTESTPROJECT_DISTESTTESTSYSTEMSETTINGS_HPP
#define DISTESTPROJECT_DISTESTTESTSYSTEMSETTINGS_HPP

#include "distestproject_global.hpp"

#include <QSettings>
#include <mobatawidgets/graph/types.hpp>

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT DisTestTestSystemSettings
{
public:
    DisTestTestSystemSettings();
    DisTestTestSystemSettings(DisTestTestSystemSettings const* source);
    DisTestTestSystemSettings(const DisTestTestSystemSettings &source);

    void toSettings(const QString &category, QSettings *settings) const;
    void fromSettings(const QString &category, const QSettings *settings);

    view::graph::NodeOptions compOptionsFromSettings() const;
    view::graph::NodeOptions portOptionsFromSettings() const;
    view::graph::ArcOptions linkOptionsFromSettings() const;
    view::graph::NodeOptions testSystemBoxOptionsFromSettings() const;

    const QString& compTextFontSeries() const;
    void setCompTextFontSeries(const QString &fontName);
    const int& compTextFontSize() const;
    void setCompTextFontSize(const int fontSize);
    const bool& compTextFontBold() const;
    void setCompTextFontBold(const bool isBold);
    const bool& compTextFontItalic() const;
    void setCompTextFontItalic(const bool isItalic);
    const QString& compTextColorName() const;
    void setCompTextColorName(const QString &colorName);
    const qreal& compBoxWidth() const;
    void setCompBoxWidth(const qreal width);
    const qreal& compBoxHeight() const;
    void setCompBoxHeight(const qreal height);
    const QString& compBoxColorName() const;
    void setCompBoxColorName(const QString &colorName);
    const int& compBorderWidth() const;
    void setCompBorderWidth(const int width);
    const QString& compBorderColorName() const;
    void setCompBorderColorName(const QString &colorName);

    const qreal& portBoxWidth() const;
    void setPortBoxWidth(const qreal width);
    const qreal& portBoxHeight() const;
    void setPortBoxHeight(const qreal height);
    const QString& portBoxColorName() const;
    void setPortBoxColorName(const QString &colorName);
    const int& portBorderWidth() const;
    void setPortBorderWidth(const int width);
    const QString& portBorderColorName() const;
    void setPortBorderColorName(const QString &colorName);

    const int& linkLineWidth() const;
    void setLinkLineWidth(const int width);
    const QString& linkLineColorName() const;
    void setLinkLineColorName(const QString &colorName);

    const qreal& spaceToSutBox() const;
    void setSpaceToSutBox(const qreal margin);

    const QString& testSystemBoxTextFontSeries() const;
    void setTestSystemBoxTextFontSeries(const QString &fontName);
    const int& testSystemBoxTextFontSize() const;
    void setTestSystemBoxTextFontSize(const int fontSize);
    const bool& testSystemBoxTextFontBold() const;
    void setTestSystemBoxTextFontBold(const bool isBold);
    const bool& testSystemBoxTextFontItalic() const;
    void setTestSystemBoxTextFontItalic(const bool isItalic);
    const QString& testSystemBoxTextColorName() const;
    void setTestSystemBoxTextColorName(const QString &colorName);
    const qreal& testSystemBoxBoxWidth() const;
    void setTestSystemBoxBoxWidth(const qreal width);
    const qreal& testSystemBoxBoxHeight() const;
    void setTestSystemBoxBoxHeight(const qreal height);
    const QString& testSystemBoxBoxColorName() const;
    void setTestSystemBoxBoxColorName(const QString &colorName);
    const int& testSystemBoxBorderWidth() const;
    void setTestSystemBoxBorderWidth(const int width);
    const QString& testSystemBoxBorderColorName() const;
    void setTestSystemBoxBorderColorName(const QString &colorName);

    const qreal& testSystemBoxMargin() const;
    void setTestSystemBoxMargin(const qreal margin);
    const qreal& testSystemBoxRadius() const;
    void setTestSystemBoxRadius(const qreal radius);

private:
    QString _compTextFontSeries;
    int     _compTextFontSize;
    bool    _compTextFontBold;
    bool    _compTextFontItalic;
    QString _compTextColorName;
    qreal   _compBoxWidth;
    qreal   _compBoxHeight;
    QString _compBoxColorName;
    int     _compBorderWidth;
    QString _compBorderColorName;
    qreal   _portBoxWidth;
    qreal   _portBoxHeight;
    QString _portBoxColorName;
    int     _portBorderWidth;
    QString _portBorderColorName;
    int     _linkLineWidth;
    QString _linkLineColorName;
    qreal   _spaceToSuTBox;
    QString _testSystemBoxTextFontSeries;
    int     _testSystemBoxTextFontSize;
    bool    _testSystemBoxTextFontBold;
    bool    _testSystemBoxTextFontItalic;
    QString _testSystemBoxTextColorName;
    qreal   _testSystemBoxBoxWidth;
    qreal   _testSystemBoxBoxHeight;
    QString _testSystemBoxBoxColorName;
    int     _testSystemBoxBorderWidth;
    QString _testSystemBoxBorderColorName;
    qreal   _testSystemBoxMargin;
    qreal   _testSystemBoxRadius;
};

inline bool operator==(const DisTestTestSystemSettings &p1, const DisTestTestSystemSettings &p2)
{
    return (!p1.compTextFontSeries().compare(p2.compTextFontSeries()))
            && (p1.compTextFontSize() == p2.compTextFontSize())
            && (p1.compTextFontBold() == p2.compTextFontBold())
            && (p1.compTextFontItalic() == p2.compTextFontItalic())
            && (!p1.compTextColorName().compare(p2.compTextColorName()))
            && (p1.compBoxWidth() == p2.compBoxWidth())
            && (p1.compBoxHeight() == p2.compBoxHeight())
            && (!p1.compBoxColorName().compare(p2.compBoxColorName()))
            && (p1.compBorderWidth() == p2.compBorderWidth())
            && (!p1.compBorderColorName().compare(p2.compBorderColorName()))
            && (p1.portBoxWidth() == p2.portBoxWidth())
            && (p1.portBoxHeight() == p2.portBoxHeight())
            && (!p1.portBoxColorName().compare(p2.portBoxColorName()))
            && (p1.portBorderWidth() == p2.portBorderWidth())
            && (!p1.portBorderColorName().compare(p2.portBorderColorName()))
            && (p1.linkLineWidth() == p2.linkLineWidth())
            && (!p1.linkLineColorName().compare(p2.linkLineColorName()))
            && (p1.spaceToSutBox() == p2.spaceToSutBox())
            && (!p1.testSystemBoxTextFontSeries().compare(p2.testSystemBoxTextFontSeries()))
            && (p1.testSystemBoxTextFontSize() == p2.testSystemBoxTextFontSize())
            && (p1.testSystemBoxTextFontBold() == p2.testSystemBoxTextFontBold())
            && (p1.testSystemBoxTextFontItalic() == p2.testSystemBoxTextFontItalic())
            && (!p1.testSystemBoxTextColorName().compare(p2.testSystemBoxTextColorName()))
            && (p1.testSystemBoxBoxWidth() == p2.testSystemBoxBoxWidth())
            && (p1.testSystemBoxBoxHeight() == p2.testSystemBoxBoxHeight())
            && (!p1.testSystemBoxBoxColorName().compare(p2.testSystemBoxBoxColorName()))
            && (p1.testSystemBoxBorderWidth() == p2.testSystemBoxBorderWidth())
            && (!p1.testSystemBoxBorderColorName().compare(p2.testSystemBoxBorderColorName()))
            && (p1.testSystemBoxMargin() == p2.testSystemBoxMargin())
            && (p1.testSystemBoxRadius() == p2.testSystemBoxRadius());
}

}

#endif // DISTESTTESTSYSTEMSETTINGS_HPP
