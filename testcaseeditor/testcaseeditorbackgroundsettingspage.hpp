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
#pragma once

#include "ui_testcaseeditorbackgroundsettings.h"
#include "testcaseeditorconstants.hpp"
#include "graphlayout/mscquickwidget.hpp"
#include "mobata/model/msc/msc.hpp"

#include <coreplugin/dialogs/ioptionspage.h>
#include <coreplugin/icore.h>

#include <QWidget>
#include <QFileDialog>
#include <QPointer>
#include <QUuid>
#include <QDebug>
#include <QTimer>

namespace testcaseeditor {

namespace Internal {

class TestcaseEditorBackgroundSettingsWidget
        : public QWidget
{
    Q_OBJECT

public:
    explicit TestcaseEditorBackgroundSettingsWidget(QWidget *parent = 0);
    ~TestcaseEditorBackgroundSettingsWidget();

private:
    class Private;
    Private* _d;
};

class TestcaseEditorBackgroundSettingsPage
        : public Core::IOptionsPage
{
    Q_OBJECT

public:
    TestcaseEditorBackgroundSettingsPage();
    ~TestcaseEditorBackgroundSettingsPage();

public slots:
    void refreshPreview(){
        _refreshPreview();
    }

public:
    QWidget*  createPage(QWidget *parent);
    void apply();
    void finish();
    bool matches(const QString& s) const;

signals:
    void appliedSettings();
private:
    void _refreshPreview();
    void _initGraph();

    Ui::TestcaseEditorBackgroundSettings _ui;
    QString _searchKeywords;
    QPointer<TestcaseEditorBackgroundSettingsWidget> _widget;
    model::msc::MscModel* _model = new model::msc::MscModel();
    graphlayout::MscQuickWidget* _mscQuickWidget = nullptr;
};

}// namespace Internal
}// namespace testcaseeditor
