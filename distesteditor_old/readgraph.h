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
#ifndef DISTESTEDITOR_READGRAPH_H
#define DISTESTEDITOR_READGRAPH_H

#include "distesteditor_global.hpp"

#include <view/graph/abstractnode.hpp>
#include <view/graph/edge.hpp>
#include <view/comp/types.hpp>


#include <QByteArray>
#include <QScopedPointer>

#include <QJsonObject>

namespace view{namespace comp{class SystemScene;}}
namespace model{namespace ts{class TsModel;}}

namespace distesteditor {

class ReadGraph
{
public:
    ReadGraph(const QByteArray& graphJsonData,
               model::ts::TsModel* testModel,
               view::comp::SystemScene* graphScene);
    virtual ~ReadGraph();

    void execute();

    void readSutSceneFromJson(QJsonObject rootObject);    
    void readTestSceneFromJson(QJsonObject rootObject);

    view::graph::NodeOptions setNodeOptions(QJsonObject object);
    void setLink(QJsonObject link);


private:
    Q_DISABLE_COPY(ReadGraph)
    class Private;
    QScopedPointer<Private> _d;
};

} //end namespace distesteditor

#endif // READSUTGRAPH_H
