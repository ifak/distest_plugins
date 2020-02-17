#include "readsutgraph.h"

#include <view/comp/component.hpp>
#include <view/comp/port.hpp>
#include <view/comp/link.hpp>
#include <view/comp/systemscene.hpp>
#include <view/graph/edge.hpp>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

#include <QDebug>

#include <stdexcept>

#include <memory_leak_start.hpp>

namespace distesteditor{

class ReadSutGraph::Private
{
    friend class ReadSutGraph;

    Private(const QByteArray &graphJsonData,
            view::comp::SystemScene* graphScene)
        : _graphJsonData(graphJsonData),
          _graphScene(graphScene)
    {}
public:
    ~Private()
    {}

private:
    const QByteArray& _graphJsonData;
    view::comp::SystemScene* _graphScene;
};

ReadSutGraph::ReadSutGraph(const QByteArray& graphJsonData,
                           view::comp::SystemScene* graphScene)
    : _d(new Private(graphJsonData, graphScene))
{
}

ReadSutGraph::~ReadSutGraph()
{
}

void ReadSutGraph::readSutSceneFromJson(QJsonObject rootObject)
{
    if(!rootObject.contains(QLatin1String("sut"))){
//        throw std::runtime_error(QObject::tr(QLatin1String("Error - JSON data contains no SUT object."))
//                                 .toString());
        return;
    }

    QJsonObject sutObject = rootObject.value(QLatin1String("sut")).toObject();

    //////read Components///////
    foreach(QJsonValue sutComp, sutObject.value(QLatin1String("components")).toArray()){
        QJsonObject comp = sutComp.toObject();

        QJsonObject pos = comp.value(QLatin1String("position")).toObject();
        QPointF p(pos.value(QLatin1String("x")).toDouble(), pos.value(QLatin1String("y")).toDouble());

        QJsonObject size = comp.value(QLatin1String("size")).toObject();
        QSizeF s(size.value(QLatin1String("width")).toDouble(), size.value(QLatin1String("height")).toDouble());

        view::comp::Component* viewComp = _d->_graphScene->addComponent(p,
                                                          comp.value(QLatin1String("componentID")).toString());
        //viewComp->prepareGeometryChange();

        viewComp->setSize(s);
        //viewComp->itemChange(QGraphicsItem::ItemScaleHasChanged, s);
        viewComp->setBrush(Qt::blue);
        viewComp->setNotation(comp.value(QLatin1String("notation")).toString());

        foreach(QJsonValue compPort, comp.value(QLatin1String("ports")).toArray()){
            QJsonObject port = compPort.toObject();
            QJsonObject portPos = port.value(QLatin1String("position")).toObject();
            QPointF p(portPos.value(QLatin1String("x")).toDouble(), portPos.value(QLatin1String("y")).toDouble());

            view::comp::Port* addedPort = _d->_graphScene->addComponentPort(viewComp, p,
                                                                          port.value(QLatin1String("portID")).toString());
            addedPort->setNotation(port.value(QLatin1String("notation")).toString());
        }

    }
    //////read Links///////
    foreach(QJsonValue sutLink, sutObject.value(QLatin1String("links")).toArray()){
        QJsonObject link = sutLink.toObject();
        QPainterPath path;

        //build PainterPath
        foreach(QJsonValue pointVal, link.value(QLatin1String("points")).toArray()){
            QJsonObject pointObj = pointVal.toObject();
            //qDebug() << path.isEmpty();
            if(pointVal == link.value(QLatin1String("points")).toArray().first())
                path.moveTo(pointObj.value(QLatin1String("x")).toDouble(), pointObj.value(QLatin1String("y")).toDouble());
            else
                path.lineTo(QPointF(pointObj.value(QLatin1String("x")).toDouble(), pointObj.value(QLatin1String("y")).toDouble()));
        }

        view::comp::Port* sourcePort = _d->_graphScene->getPort(link.value(QLatin1String("sourcePort")).toString());
        view::comp::Port* targetPort = _d->_graphScene->getPort(link.value(QLatin1String("targetPort")).toString());

        view::comp::Link* addedLink = _d->_graphScene->addLink(sourcePort, targetPort, path);
        addedLink->setUuid(link.value(QLatin1String("linkID")).toString());
    }

    return;
}

void ReadSutGraph::execute()
{
    if(!this->_d->_graphScene)
        return;

  QJsonParseError parseError;
  QJsonDocument jsonDocument = QJsonDocument::fromJson(this->_d->_graphJsonData,
                                                     &parseError);

  if(parseError.error != QJsonParseError::NoError)
    throw std::runtime_error(QObject::tr("Parser error: %1")
                             .arg(parseError.errorString())
                             .toStdString());

  if(jsonDocument.isArray()
     || jsonDocument.isEmpty()
     || jsonDocument.isNull())
    throw std::runtime_error(QObject::tr("Graph json file should be an object!")
                             .toStdString());

  QJsonObject rootObject = jsonDocument.object();
  this->readSutSceneFromJson(rootObject);

  return;
}


}
