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
#pragma once

#include "mobata/model/requirement/requirementsmodel.hpp"
#include "mobata/model/requirement/requirementitem.hpp"
#include "graphlayout/mscquickwidget.hpp"
#include <mobata/model/msc/msc.hpp>
#include <coreplugin/icore.h>

inline void previewGraph(model::msc::MscModel* model)
{
    model::msc::MscModel* mscModel = dynamic_cast<model::msc::MscModel*>(model);
    QString errorString;
    model::msc::MscComponentItem* comp1 = new model::msc::MscComponentItem("Comp1");
    mscModel->addComponent(comp1, &errorString);
    model::msc::MscComponentItem* comp2 = new model::msc::MscComponentItem("Comp2");
    mscModel->addComponent(comp2, &errorString);
    model::msc::MscSequence* seq = new model::msc::MscSequence("seq");
    seq->addMessage(comp1,comp2,"Message");
    seq->addCheck(comp1,comp2,"Checkmessage");
    model::msc::MscFragmentItem* frag = seq->addFragment(model::msc::AlternativeFragment);
    frag->addRegion("Region1");
    frag->regions().first()->addStatement(comp1,"Statement");
    frag->addRegion("Region2");
    model::msc::MscTimerItem* timer = frag->regions().last()->addTimer(comp1,"Timer");
    timer->setValue(100);
    mscModel->addSequence(seq);
}

inline void testcaseGraphLoadSettings(graphlayout::MscQuickWidget* mscQuickWidget)
{
    QSettings * settings = Core::ICore::settings();
    settings->beginGroup(QLatin1String("TestcaseEditor"));
    settings->beginGroup(QLatin1String("Background"));
    if(!settings->contains(QLatin1String("ComponentColor"))){
      settings->endGroup();
      settings->endGroup();
      return;
    }
    mscQuickWidget->setComponentColor(qvariant_cast<QColor>(settings->value(QLatin1String("ComponentColor"))));
    mscQuickWidget->setComponentTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("ComponentTextcolor"))));
    mscQuickWidget->setLifelineColor(qvariant_cast<QColor>(settings->value(QLatin1String("LifelineColor"))));
    mscQuickWidget->setBackgroundColor(qvariant_cast<QColor>(settings->value(QLatin1String("BackgroundColor"))));
    mscQuickWidget->setHighlightColor(qvariant_cast<QColor>(settings->value(QLatin1String("HighlightColor"))));
    settings->endGroup();
    settings->beginGroup(QLatin1String("Steps"));
    mscQuickWidget->setStatementColor(qvariant_cast<QColor>(settings->value(QLatin1String("StatementColor"))));
    mscQuickWidget->setStatementTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("StatementTextcolor"))));
    mscQuickWidget->setTimerColor(qvariant_cast<QColor>(settings->value(QLatin1String("TimerColor"))));
    mscQuickWidget->setTimerTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("TimerTextcolor"))));
    mscQuickWidget->setTimeoutColor(qvariant_cast<QColor>(settings->value(QLatin1String("TimeoutColor"))));
    mscQuickWidget->setTimeoutTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("TimeoutTextcolor"))));
    mscQuickWidget->setSleeptimerColor(qvariant_cast<QColor>(settings->value(QLatin1String("SleeptimerColor"))));
    mscQuickWidget->setSleeptimerTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("SleeptimerTextcolor"))));
    mscQuickWidget->setMessageColor(qvariant_cast<QColor>(settings->value(QLatin1String("MessageColor"))));
    mscQuickWidget->setMessageTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("MessageTextcolor"))));
    mscQuickWidget->setCheckmessageColor(qvariant_cast<QColor>(settings->value(QLatin1String("CheckmessageColor"))));
    mscQuickWidget->setCheckmessageTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("CheckmessageTextcolor"))));
    mscQuickWidget->setFragmentColor(qvariant_cast<QColor>(settings->value(QLatin1String("FragmentColor"))));
    mscQuickWidget->setFragmentTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("FragmentTextcolor"))));
    mscQuickWidget->setRegionColor(qvariant_cast<QColor>(settings->value(QLatin1String("RegionColor"))));
    mscQuickWidget->setRegionTextColor(qvariant_cast<QColor>(settings->value(QLatin1String("RegionTextcolor"))));
    settings->endGroup();
    settings->endGroup();
}
