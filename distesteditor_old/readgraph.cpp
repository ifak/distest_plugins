#include "readgraph.h"

#include <view/comp/component.hpp>
#include <view/comp/port.hpp>
#include <view/comp/link.hpp>
#include <view/comp/systemscene.hpp>
#include <view/comp/sutcomponent.h>
#include <view/comp/testcomponent.h>

#include <model/ts/tsmodel.hpp>
#include <model/ts/tssutitem.hpp>
#include <model/ts/tstestgroupitem.hpp>
#include <model/ts/tssutcompitem.hpp>
#include <model/ts/tstestcompitem.hpp>
#include <model/ts/tsportitem.hpp>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

#include <QTextCursor>

#include <QDebug>

#include <stdexcept>

#include <memory_leak_start.hpp>

namespace distesteditor{

class ReadGraph::Private
{
    friend class ReadGraph;

    Private(const QByteArray &graphJsonData,
            model::ts::TsModel* testModel,
            view::comp::SystemScene* graphScene)
        : _graphJsonData(graphJsonData),
          _testModel(testModel),
          _graphScene(graphScene)
    {}
public:
    ~Private()
    {}

private:
    const QByteArray& _graphJsonData;
    model::ts::TsModel* _testModel;
    view::comp::SystemScene* _graphScene;
};

ReadGraph::ReadGraph(const QByteArray& graphJsonData,
                     model::ts::TsModel *testModel,
                     view::comp::SystemScene* graphScene)
    : _d(new Private(graphJsonData, testModel, graphScene))
{
}

ReadGraph::~ReadGraph()
{
}

void ReadGraph::readSutSceneFromJson(QJsonObject rootObject)
{
    if(!rootObject.contains(QLatin1String("sut"))){
        throw std::runtime_error(QObject::tr("Error - JSON data contains no SUT object.").toStdString());
        return;
    }

    QJsonObject sutObject = rootObject.value(QLatin1String("sut")).toObject();

    //////read Components///////
    foreach(QJsonValue sutComp, sutObject.value(QLatin1String("components")).toArray()){
        QJsonObject comp = sutComp.toObject();
        QPointF p(comp.value(QLatin1String("x")).toDouble(),
                  comp.value(QLatin1String("y")).toDouble());
        view::comp::SutComponent* viewComp = _d->_graphScene->addSutComponent(p,
                                                                              setNodeOptions(comp));
        viewComp->setUuid(comp.value(QLatin1String("ID")).toString());
        viewComp->setNotation(comp.value(QLatin1String("notation")).toString());

        //////read Ports///////
        foreach(QJsonValue compPort, comp.value(QLatin1String("ports")).toArray()){
            QJsonObject port = compPort.toObject();
            QPointF p(port.value(QLatin1String("x")).toDouble(),
                      port.value(QLatin1String("y")).toDouble());
            view::comp::Port* addedPort = _d->_graphScene->addPort(viewComp, p,
                                                                            setNodeOptions(port));
            addedPort->setUuid(port.value(QLatin1String("ID")).toString());
            addedPort->setNotation(port.value(QLatin1String("notation")).toString());
        }
    }

    //////read Links///////
    foreach(QJsonValue sutLink, sutObject.value(QLatin1String("links")).toArray()){
        QJsonObject link = sutLink.toObject();
        this->setLink(link);
    }

    return;
}

void ReadGraph::readTestSceneFromJson(QJsonObject rootObject)
{
    if(!rootObject.contains(QLatin1String("testgroup"))){
        return;
    }

    QJsonObject testObject = rootObject.value(QLatin1String("testgroup")).toObject();

    //////read Components///////
    foreach(QJsonValue testComp, testObject.value(QLatin1String("components")).toArray()){
        QJsonObject comp = testComp.toObject();
        QPointF p(comp.value(QLatin1String("x")).toDouble(),
                  comp.value(QLatin1String("y")).toDouble());
        view::comp::TestComponent* viewComp = _d->_graphScene->addTestComponent(p,
                                                                              setNodeOptions(comp));
        viewComp->setUuid(comp.value(QLatin1String("ID")).toString());
        viewComp->setNotation(comp.value(QLatin1String("notation")).toString());


        //////read Ports///////
        foreach(QJsonValue compPort, comp.value(QLatin1String("ports")).toArray()){
            QJsonObject port = compPort.toObject();
            QPointF p(port.value(QLatin1String("x")).toDouble(),
                      port.value(QLatin1String("y")).toDouble());
            view::comp::Port* addedPort = _d->_graphScene->addPort(viewComp, p,
                                                                            setNodeOptions(port));
            addedPort->setUuid(port.value(QLatin1String("ID")).toString());
            addedPort->setNotation(port.value(QLatin1String("notation")).toString());
        }
    }

    //////read Links///////
    foreach(QJsonValue testLink, testObject.value(QLatin1String("links")).toArray()){
        QJsonObject link = testLink.toObject();

        if(!_d->_graphScene->port(link.value(QLatin1String("sourcePort")).toString()) ||
                !_d->_graphScene->port(link.value(QLatin1String("targetPort")).toString())){
            qDebug() << "Error - Testgroup's links doesn't match SUT";
            //TODO
            //Ausgabe in DisTestCreator in "Ausgabe der Anwendung"
        }

        this->setLink(link);
    }
    return;
}

view::graph::NodeOptions ReadGraph::setNodeOptions(QJsonObject object)
{
    view::graph::NodeOptions options;

    QSizeF s(object.value(QLatin1String("width")).toDouble(),
             object.value(QLatin1String("height")).toDouble());
    options.setSize(s);

    options.setColor(QColor(object.value(QLatin1String("color")).toString()));

    QPen pen(Qt::SolidLine);
    pen.setWidthF(object.value(QLatin1String("linewidth")).toDouble());
    options.setPen(pen);

    QFont font(object.value(QLatin1String("fontFamily")).toString());
    font.setPointSizeF(object.value(QLatin1String("fontSize")).toDouble());

    options.setTextFont(font);

    return options;
}

void ReadGraph::setLink(QJsonObject link)
{
    view::comp::Component *sourceHelpComp = 0;
    view::comp::Component *targetHelpComp = 0;
    QPainterPath path;

    //build PainterPath
    foreach(QJsonValue pointVal, link.value(QLatin1String("points")).toArray()){
        QJsonObject pointObj = pointVal.toObject();
        if(pointVal == link.value(QLatin1String("points")).toArray().first()){
            path.moveTo(pointObj.value(QLatin1String("x")).toDouble(),
                        pointObj.value(QLatin1String("y")).toDouble());
        } else{
            path.lineTo(QPointF(pointObj.value(QLatin1String("x")).toDouble(),
                                pointObj.value(QLatin1String("y")).toDouble()));
        }
    }

    view::graph::ArcOptions options;
    QPen pen(Qt::SolidLine);
    pen.setColor(QColor(link.value(QLatin1String("color")).toString()));
    pen.setWidthF(link.value(QLatin1String("linewidth")).toDouble());
    options.setPen(pen);

    view::comp::Port* sourcePort = _d->_graphScene->port(link.value(QLatin1String("sourcePort")).toString());
    view::comp::Port* targetPort = _d->_graphScene->port(link.value(QLatin1String("targetPort")).toString());

    if(!sourcePort)
    {
        QPointF p = path.elementAt(0);
        sourceHelpComp = _d->_graphScene->addComponent(p, QUuid::createUuid());
        sourcePort = _d->_graphScene->addPort(sourceHelpComp, p, QUuid::createUuid());

    }
    if(!targetPort)
    {
        QPointF p = path.elementAt(path.elementCount()-1);
        targetHelpComp = _d->_graphScene->addComponent(p, QUuid::createUuid());
        targetPort = _d->_graphScene->addPort(targetHelpComp, p, QUuid::createUuid());
    }
    view::comp::Link* addedLink = _d->_graphScene->addLink(sourcePort, targetPort, path,options);
    addedLink->setUuid(link.value(QLatin1String("linkID")).toString());

    if(sourceHelpComp)
    {
        sourcePort->removeEdge(addedLink);
        addedLink->setSource(0);
        _d->_graphScene->removeComponent(sourceHelpComp);
    }
    if(targetHelpComp)
    {
        targetPort->removeEdge(addedLink);
        addedLink->setTarget(0);
        _d->_graphScene->removeComponent(targetHelpComp);
    }

    return;
}


void ReadGraph::execute()
{
    if(!this->_d->_graphScene)
        return;

    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(this->_d->_graphJsonData,
                                                     &parseError);
    //TODO
//  if(parseError.error != QJsonParseError::NoError)
//    throw std::runtime_error(QObject::tr("Parser error: %1")
//                             .arg(parseError.errorString())
//                             .toStdString());

//  if(jsonDocument.isArray()
//     || jsonDocument.isEmpty()
//     || jsonDocument.isNull())
//    throw std::runtime_error(QObject::tr("Graph json file should be an object!")
//                             .toStdString());

    QJsonObject rootObject = jsonDocument.object();
    if(rootObject.contains(QLatin1String("sut"))){
        this->readSutSceneFromJson(rootObject);
    } else if(rootObject.contains(QLatin1String("testgroup"))){
        this->readTestSceneFromJson(rootObject);
    }

  return;
}

}
