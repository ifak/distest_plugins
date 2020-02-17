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
#ifndef SAVEGRAPH_H
#define SAVEGRAPH_H

#include "distesteditor_global.hpp"

#include <view/graph/abstractnode.hpp>
#include <view/graph/edge.hpp>

#include <fstream>
#include <QScopedPointer>

namespace view{ namespace comp{ class SystemScene;}}
namespace model{ namespace ts{ class TsModel;}}

namespace distesteditor{

class SaveGraph
{
public:
    SaveGraph(model::ts::TsModel* testModel,
                view::comp::SystemScene *testScene,
                std::ofstream& graphOutputStream);
    virtual ~SaveGraph();

    void sutToJson();
    void testGroupToJson();
    QJsonObject setNodeData(view::graph::AbstractNode* currItem);
    QJsonObject setLinkData(view::graph::Edge* currLink);

private:
    Q_DISABLE_COPY(SaveGraph)
    class Private;
    QScopedPointer<Private> _d;
};

} //namespace distesteditor

#endif // SAVEGRAPH_H
