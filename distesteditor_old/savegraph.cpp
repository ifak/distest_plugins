#include "savegraph.h"

#include <model/ts/tsmodel.hpp>
#include <model/ts/tssutitem.hpp>
#include <model/ts/tssutcompitem.hpp>
#include <model/ts/tstestgroupitem.hpp>
#include <model/ts/tstestcompitem.hpp>
#include <model/ts/tsportitem.hpp>

#include <view/comp/systemscene.hpp>
#include <view/comp/component.hpp>
#include <view/comp/port.hpp>
#include <view/comp/link.hpp>
#include <view/comp/sutcomponent.h>
#include <view/comp/testcomponent.h>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <memory_leak_start.hpp>

namespace distesteditor{

class SaveGraph::Private
{
    friend class SaveGraph;

    Private(model::ts::TsModel* testModel,
            view::comp::SystemScene* testScene,
                  std::ofstream &graphOutputStream)
        :   _model(testModel),
            _scene(testScene),
            _graphOutputStream(graphOutputStream)
    {}

public:
    ~Private()
    {}

private:
    model::ts::TsModel*       _model;
    view::comp::SystemScene*	_scene;
    std::ofstream&					_graphOutputStream;
};

SaveGraph::SaveGraph(model::ts::TsModel *testModel,
                     view::comp::SystemScene * testScene,
                     std::ofstream& graphOutputStream)
    : _d(new Private(testModel, testScene, graphOutputStream))
{
}

SaveGraph::~SaveGraph()
{}


void SaveGraph::sutToJson()
{
    QJsonObject jsonSut;
    QJsonArray components;
    QJsonArray sutLinks;
    QJsonObject sutComponent;
    QList<QUuid> linkList;

    foreach(view::comp::SutComponent* comp, _d->_scene->sutComponents()){
        sutComponent =
                this->setNodeData(dynamic_cast<view::graph::AbstractNode*>(comp));

        QJsonArray sutPorts;

        foreach(view::comp::Port *sutPort, comp->ports()){
            QJsonObject port =
                    this->setNodeData(dynamic_cast<view::graph::AbstractNode*>(sutPort));
            sutPorts.append(port);

            foreach (view::graph::Edge *currLink, sutPort->edges()) {
                if(!linkList.contains(currLink->uuid())){
                    QJsonObject link =
                            this->setLinkData(currLink);

                    sutLinks.append(link);
                    linkList.append(currLink->uuid());
                }
            }
        }
        sutComponent[QLatin1String("ports")] = sutPorts;
        components.append(sutComponent);
    }

    QJsonObject items;
    items[QLatin1String("components")] = components;
    items[QLatin1String("links")] = sutLinks;

    jsonSut[QLatin1String("sut")] = items;

    QJsonDocument saveSutScene(jsonSut);

    this->_d->_graphOutputStream << saveSutScene.toJson().data();

    return;
}

void SaveGraph::testGroupToJson()
{
    QJsonObject jsonTest;
    QJsonArray components;
    QJsonArray testLinks;
    QJsonObject testComponent;
    QList<QUuid> linkList;

    foreach(view::comp::TestComponent* comp, _d->_scene->testComponents()){
        testComponent =
                this->setNodeData(dynamic_cast<view::graph::AbstractNode*>(comp));

        QJsonArray testPorts;

        foreach(view::comp::Port *testPort, comp->ports()){
            QJsonObject port =
                    this->setNodeData(dynamic_cast<view::graph::AbstractNode*>(testPort));

            testPorts.append(port);

            foreach (view::graph::Edge *currLink, testPort->edges()) {
                if(!linkList.contains(currLink->uuid())){
                    QJsonObject link = this->setLinkData(currLink);

                    testLinks.append(link);
                    linkList.append(currLink->uuid());
                }
            }
        }
        testComponent[QLatin1String("ports")] = testPorts;
        components.append(testComponent);
    }

    QJsonObject items;
    items[QLatin1String("components")] = components;
    items[QLatin1String("links")] = testLinks;

    jsonTest[QLatin1String("testgroup")] = items;

    QJsonDocument saveTestScene(jsonTest);

    this->_d->_graphOutputStream << saveTestScene.toJson().data();

    return;
}

QJsonObject SaveGraph::setNodeData(view::graph::AbstractNode* currItem)
{
    QJsonObject object;
    object[QLatin1String("ID")] = currItem->uuid().toString();
    object[QLatin1String("notation")] = currItem->notation();
    object[QLatin1String("x")] = currItem->scenePos().x();
    object[QLatin1String("y")] = currItem->scenePos().y();
    object[QLatin1String("width")] = currItem->size().width();
    object[QLatin1String("height")] = currItem->size().height();
    object[QLatin1String("color")] = currItem->brush().color().name();
    object[QLatin1String("linewidth")] = currItem->pen().width();
    object[QLatin1String("fontFamily")] = currItem->notationItem()->font().family();
    object[QLatin1String("fontSize")] = currItem->notationItem()->font().pointSize();

    return object;
}

QJsonObject SaveGraph::setLinkData(view::graph::Edge* currLink)
{
    qDebug() << "setLinkData";
    QJsonObject link;
    link[QLatin1String("ID")] = currLink->uuid().toString();
    if(currLink->source())
        link[QLatin1String("sourcePort")] = currLink->source()->uuid().toString();
    else
        qDebug() << "kein source port - link kann nicht gespeichert werden!";
    //noch exception handling ergänzen, auch für target port

    if(currLink->target())
        link[QLatin1String("targetPort")] = currLink->target()->uuid().toString();
    else
        qDebug() << "kein target port - link kann nicht gespeichert werden!";

    QJsonArray json_link_points;
    foreach(const QPointF& point, currLink->controlPointFs())
    {
        QJsonObject json_point;
        json_point[QLatin1String("x")]=point.x();
        json_point[QLatin1String("y")]=point.y();
        json_link_points.push_back(json_point);
    }
    if(json_link_points.size())
        link[QLatin1String("points")]=json_link_points;

    link[QLatin1String("color")] = currLink->pen().color().name();
    link[QLatin1String("linewidth")] = currLink->pen().width();

    return link;
}

} // namespace distesteditor
