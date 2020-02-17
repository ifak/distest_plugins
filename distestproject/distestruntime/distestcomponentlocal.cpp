#include "distestcomponentlocal.hpp"

#include "distestcomponentlocalservice.hpp"

#include <qjsonrpctcpserver.h>
#include <qjsonrpcsocket.h>
#include <qjsonrpcservicereply.h>

#include <QTimer>

#include <mobata/memory_leak_start.hpp>

namespace distestproject{
namespace distestruntime {

class DisTestComponentLocal::Private
{
  friend class DisTestComponentLocal;

  QHostAddress        _ptcAddress;
  quint16             _ptcPort;
  QString             _localAddressString;
  quint16             _localPort;
  QString             _serviceProvider;
  QTcpSocket*         _tcpSocket;
  QJsonRpcSocket*     _jsonRpcSocket;
  QJsonRpcTcpServer*  _jsonRpcServer;
  QTimer*             _statusTimer;
  quint16             _statusInterval;
  State               _remoteState;

  Private(const QHostAddress& ptcAddress,
          const quint16 ptcPort,
          const quint16 localPort,
          const QString& serviceProvider)
    : _ptcAddress(ptcAddress),
      _ptcPort(ptcPort),
      _localAddressString(QStringLiteral("127.0.0.1")),
      _localPort(localPort),
      _serviceProvider(serviceProvider),
      _statusTimer(0),
      _statusInterval(3000)
  {}
};

DisTestComponentLocal::DisTestComponentLocal(const QString& name,
                                             const QHostAddress& ptcAddress,
                                             const quint16 ptcPort,
                                             const quint16 localPort,
                                             const QString& serviceProvider,
                                             QObject* parent)
  : DisTestComponent(name, parent),
    _d(new Private(ptcAddress, ptcPort, localPort, serviceProvider))
{
  this->_d->_tcpSocket = new QTcpSocket(this);
  this->_d->_jsonRpcSocket = new QJsonRpcSocket(this->_d->_tcpSocket, this);

  this->_d->_jsonRpcServer = new QJsonRpcTcpServer(this);

  DisTestComponentLocalService* compService = new DisTestComponentLocalService(this);
  this->_d->_jsonRpcServer->addService(compService);

  connect(compService, &DisTestComponentLocalService::finishedReceived,
          this, &DisTestComponentLocal::remoteFinished);

  connect(compService, &DisTestComponentLocalService::currStepStartedReceived,
          this, &DisTestComponent::stepStarted);

  connect(compService, &DisTestComponentLocalService::currStepFinishedReceived,
          this, &DisTestComponent::stepFinished);

  this->_d->_statusTimer = new QTimer(this);
  connect(this->_d->_statusTimer, &QTimer::timeout,
          this, &DisTestComponentLocal::statusSlot);
}

DisTestComponentLocal::~DisTestComponentLocal()
{
  qDebug()<<"DisTestComponentLocal::~DisTestComponentLocal() executed!";

  this->_d->_jsonRpcServer->close();
  this->_d->_tcpSocket->close();

  delete this->_d;
}

void DisTestComponentLocal::processRemoteReply(const QJsonRpcMessage& responseMessage,
                                               bool* result,
                                               QString* message)
{
  Q_ASSERT(result);
  Q_ASSERT(message);

  *result = true;
  *message = QStringLiteral("");

  if(responseMessage.result().isArray())
  {
    QJsonArray resultArray = responseMessage.result().toArray();
    *result = resultArray.at(0).toBool();
    *message = resultArray.at(1).toString();

    return;
  }
  else if(responseMessage.result().isBool())
  {
    *result = responseMessage.result().toBool();
    *message = responseMessage.errorMessage();

    return;
  }
  else if(responseMessage.result().isDouble())
  {
    int value = responseMessage.result().toInt();
    if(value == 0)
      *result = true;
    else
      *result = false;

    *message = responseMessage.errorMessage();

    return;
  }

  *result=false;
  *message=responseMessage.errorMessage();

  return;
}

DisTestComponent::State DisTestComponentLocal::remoteState() const
{
  return this->_d->_remoteState;
}

bool DisTestComponentLocal::run(QString* errorString)
{
  Q_ASSERT(this->_d->_jsonRpcServer);

  if(!this->_d->_jsonRpcServer->isListening())
  {
    if(!this->_d->_jsonRpcServer->listen(QHostAddress::Any,
                                         this->_d->_localPort))
    {
      QString errorMessage = this->_d->_jsonRpcServer->errorString();
      if(errorString)
        *errorString += errorMessage;
      return false;
    }
  }

  return true;
}

bool DisTestComponentLocal::isRunning() const
{
  Q_ASSERT(this->_d->_jsonRpcServer);

  return this->_d->_jsonRpcServer->isListening();
}

void DisTestComponentLocal::remoteSetuped()
{
  qDebug()<<"DisTestComponentLocal::remoteSetuped() executed!";

  QJsonRpcServiceReply *reply = qobject_cast<QJsonRpcServiceReply *>(this->sender());
  Q_ASSERT(reply);

  bool result = true;
  QString message = QStringLiteral("");

  processRemoteReply(reply->response(), &result, &message);

  if(!result)
  {
    emit setuped(this, false, message);
  }
  else
  {
    emit setuped(this,
                 true,
                 tr("test component '%1' setuped...")
                 .arg(this->name()));
  }

  return;
}

bool DisTestComponentLocal::start(QString* errorString)
{
  qDebug()<<"DisTestComponentLocal::start() executed!";

  if(!this->isConnected())
  {
    if(!this->connectToPtc(errorString))
    {
      QString errorMessage = tr("test component '%1' is not connected!").arg(this->name());
      if(errorString)
        *errorString += errorMessage;

      emit started(this, false, errorMessage);
      return false;
    }
  }

  QString serviceName = this->_d->_serviceProvider + QStringLiteral(".start");
  QJsonRpcServiceReply* reply = this->jsonRpcSocket()->invokeRemoteMethod(serviceName);
  connect(reply, &QJsonRpcServiceReply::finished,
          this, &DisTestComponentLocal::remoteStarted);

  this->_d->_statusTimer->start(this->_d->_statusInterval);

  return true;
}

void DisTestComponentLocal::statusSlot()
{
  qDebug()<<"DisTestComponentLocal::statusSlot() executed!";

  if(!this->isConnected())
  {
    QString errorMessage;
    if(!this->connectToPtc(&errorMessage))
    {
      QString errorString = tr("test component '%1' is not connected!").arg(this->name());
      errorMessage += errorString;

      qDebug()<<"ERROR: DisTestComponentLocal::statusSlot() is not Connected!";
      emit errors(this, QStringList()<<errorMessage);
      return;
    }
  }

  QString serviceName = this->_d->_serviceProvider + QStringLiteral(".status");
  QJsonRpcMessage response = this->jsonRpcSocket()->invokeRemoteMethodBlocking(serviceName);

  QString remoteStateString;
  QStringList errorList;

  QJsonValue result = response.result();
  if(result.isDouble())
  {
    int value=result.toInt();
    if(value==0)
    {
      this->_d->_remoteState=FinishedState;
      emit finished(this, true, QStringLiteral(""));
    }
    else if(value == 1)
      this->_d->_remoteState=StartedState;
    else if(value == 2)
    {
      this->_d->_remoteState=ErrorState;
      errorList.append(tr("diagnosis is not active"));
    }
  }
  else if(result.isArray())
  {
    QJsonArray resultArray = response.result().toArray();
    Q_ASSERT(resultArray.count()>=2);
    Q_ASSERT(resultArray.at(0).isString());
    Q_ASSERT(resultArray.at(1).isArray());

    remoteStateString = resultArray.at(0).toString();
    this->_d->_remoteState = string2state(remoteStateString);

    foreach(const QJsonValue& errorValue,
            resultArray.at(1).toArray())
    {
      Q_ASSERT(errorValue.isString());
      errorList.append(errorValue.toString());
    }
  }

  if(errorList.count())
    emit errors(this, errorList);

  qDebug()<<"status of remote component '"<<this->name()<<"': "
         <<this->_d->_remoteState<<" errors: "<<errorList;

  return;
}

void DisTestComponentLocal::remoteStarted()
{
  qDebug()<<"DisTestComponentLocal::remoteStarted() executed!";

  QJsonRpcServiceReply *reply = qobject_cast<QJsonRpcServiceReply *>(this->sender());
  Q_ASSERT(reply);

  bool result = true;
  QString message = QStringLiteral("");

  processRemoteReply(reply->response(), &result, &message);

  if(!result)
  {
    emit started(this, false, message);
  }
  else
  {
    emit started(this,
                 true,
                 tr("test component '%1' started...")
                 .arg(this->name()));
  }

  return;
}

bool DisTestComponentLocal::stop(QString* errorString)
{
  qDebug()<<"DisTestComponentLocal::stop() executed!";

  if(!this->isConnected())
  {
    if(!this->connectToPtc(errorString))
    {
      QString errorMessage = tr("test component '%1' is not connected!").arg(this->name());
      if(errorString)
        *errorString += errorMessage;

      emit stopped(this, false, errorMessage);
      return false;
    }
  }

  QString serviceName = this->_d->_serviceProvider + QStringLiteral(".stop");
  QJsonRpcServiceReply* reply = this->jsonRpcSocket()->invokeRemoteMethod(serviceName);
  connect(reply, &QJsonRpcServiceReply::finished,
          this, &DisTestComponentLocal::remoteStopped);

  this->_d->_statusTimer->stop();

  return true;
}

void DisTestComponentLocal::remoteStopped()
{
  qDebug()<<"DisTestComponentLocal::remoteStopped() executed!";

  QJsonRpcServiceReply *reply = qobject_cast<QJsonRpcServiceReply *>(this->sender());
  Q_ASSERT(reply);

  bool result = true;
  QString message = QStringLiteral("");

  processRemoteReply(reply->response(), &result, &message);

  if(!result)
  {
    emit stopped(this, false, message);
  }
  else
  {
    emit stopped(this,
                 true,
                 tr("test component '%1' stopped...")
                 .arg(this->name()));
  }

  return;
}

bool DisTestComponentLocal::cleanup(QString* errorString)
{
  qDebug()<<"DisTestComponentLocal::cleanup() executed!";

  if(!this->isConnected())
  {
    if(!this->connectToPtc(errorString))
    {
      QString errorMessage = tr("test component '%1' is not connected!")
                             .arg(this->name());
      if(errorString)
        *errorString += errorMessage;

      qDebug()<< "DisTestComponentLocal::cleanup() is not Connected, emit cleanuped(this, false, errorMessage);";
      emit cleanuped(this, false, errorMessage);
      return false;
    }
  }

  QString serviceName = this->_d->_serviceProvider + QStringLiteral(".cleanup");
  QJsonRpcMessage response = this->jsonRpcSocket()->invokeRemoteMethodBlocking(serviceName);

  bool result = true;
  QString message = QStringLiteral("");
  processRemoteReply(response, &result, &message);

  if(!result)
  {
    if(errorString)
      *errorString += message;

    qDebug()<< "DisTestComponentLocal::cleanup() result negative send, emit cleanuped(this, false, message);";
    emit cleanuped(this, false, message);
    return false;
  }

  emit cleanuped(this,
                 true,
                 tr("test component '%1' cleanuped...")
                 .arg(this->name()));
  return true;
}

void DisTestComponentLocal::remoteCleanuped()
{
  qDebug()<<"DisTestComponentLocal::remoteCleanuped() executed!";

  QJsonRpcServiceReply *reply = qobject_cast<QJsonRpcServiceReply *>(this->sender());
  Q_ASSERT(reply);

  bool result = true;
  QString message = QStringLiteral("");

  processRemoteReply(reply->response(), &result, &message);

  if(!result)
  {
    emit cleanuped(this, false, message);
  }
  else
  {
    emit cleanuped(this,
                   true,
                   tr("remote test component '%1' clenauped...")
                   .arg(this->name()));
  }

  return;
}

void DisTestComponentLocal::remoteFinished(bool value,
                                           QString message)
{
  qDebug()<<"DisTestComponentLocal::remoteFinished() executed! name:" << this->name();

  this->_d->_statusTimer->stop();
  emit finished(this, value, message);

  return;
}

void DisTestComponentLocal::setLocalAddressString(const QString& localAddressString)
{
  this->_d->_localAddressString = localAddressString;

  return;
}

void DisTestComponentLocal::setLocalPort(const quint16 localPort)
{
  this->_d->_localPort = localPort;

  return;
}

void DisTestComponentLocal::setPtcAddress(const QHostAddress& ptcAddress)
{
  this->_d->_ptcAddress=ptcAddress;

  return;
}

void DisTestComponentLocal::setPtcPort(const quint16 ptcPort)
{
  this->_d->_ptcPort=ptcPort;

  return;
}

const QString& DisTestComponentLocal::localAddressString() const
{
  return this->_d->_localAddressString;
}

quint16 DisTestComponentLocal::localPort() const
{
  return this->_d->_localPort;
}

const QHostAddress& DisTestComponentLocal::ptcAddress() const
{
  return this->_d->_ptcAddress;
}

quint16 DisTestComponentLocal::ptcPort() const
{
  return this->_d->_ptcPort;
}

bool DisTestComponentLocal::connectToPtc(QString* errorString)
{
  return this->connectToPtc(true, errorString);
}

bool DisTestComponentLocal::connectToPtc(bool connectToMtc,
                                         QString* errorString)
{
  Q_ASSERT(this->_d->_tcpSocket);
  Q_ASSERT(this->_d->_jsonRpcSocket);

  this->_d->_tcpSocket->connectToHost(this->_d->_ptcAddress,
                                      this->_d->_ptcPort);

  if(!this->_d->_tcpSocket->waitForConnected(/*5000*/))
  {
    QString errorMessage = tr("could not connect to host '%1'"
                              "for remote test component '%2'")
                           .arg(this->_d->_ptcAddress.toString())
                           .arg(this->name());

    if(errorString)
      *errorString += errorMessage;

    return false;
  }

  if(!connectToMtc)
  {
    emit setuped(this,
                 true,
                 tr("remote test component '%1' setuped...")
                 .arg(this->name()));
    return true;
  }

  qDebug()<<tr("trying '%1.setupMtc' with mtc-address: '%2' and mtc-port: '%3'")
            .arg(this->_d->_serviceProvider)
            .arg(this->_d->_localAddressString)
            .arg(this->_d->_localPort);

  QString serviceName = this->_d->_serviceProvider + QStringLiteral(".setupMtc");
  QJsonRpcMessage response = this->jsonRpcSocket()->invokeRemoteMethodBlocking(serviceName,
                                                                               this->_d->_localAddressString,
                                                                               this->_d->_localPort);

  bool result = true;
  QString message = QStringLiteral("");

  DisTestComponentLocal::processRemoteReply(response, &result, &message);

  if(!result)
  {
    if(errorString)
      *errorString += message;

    emit setuped(this, false, message);
    return false;
  }

  emit setuped(this,
               true,
               tr("remote test component '%1' setuped...")
               .arg(this->name()));

  return true;
}

bool DisTestComponentLocal::isConnected() const
{
  return this->_d->_tcpSocket->state()==QAbstractSocket::ConnectedState;
}

QJsonRpcSocket* DisTestComponentLocal::jsonRpcSocket() const
{
  return this->_d->_jsonRpcSocket;
}

QJsonRpcTcpServer* DisTestComponentLocal::jsonRpcServer() const
{
  return this->_d->_jsonRpcServer;
}

} // namespace distestruntime
} // namespace distestproject
