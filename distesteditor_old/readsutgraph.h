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
#ifndef READSUTGRAPH_H
#define READSUTGRAPH_H

#include "distesteditor_global.hpp"

#include <QByteArray>
#include <QScopedPointer>

#include <QJsonObject>

namespace view{namespace comp{class SystemScene;}}

namespace distesteditor {

class ReadSutGraph
{
public:
    ReadSutGraph( const QByteArray& graphJsonData,
                  view::comp::SystemScene* graphScene);
    virtual ~ReadSutGraph();

    void readSutSceneFromJson(QJsonObject rootObject);
    void execute();

private:
    Q_DISABLE_COPY(ReadSutGraph)
    class Private;
    QScopedPointer<Private> _d;
};

} //namespace distesteditor

#endif // READSUTGRAPH_H
