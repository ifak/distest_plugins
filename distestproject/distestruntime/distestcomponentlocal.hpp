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
#ifndef DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENTLOCAL_HPP
#define DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENTLOCAL_HPP

#include "../distestproject_global.hpp"

#include "distestcomponent.hpp"

class QHostAddress;
class QJsonRpcTcpServer;
class QJsonRpcSocket;
class QJsonRpcMessage;

namespace distestproject{
namespace distestruntime {

class DISTESTPROJECTSHARED_EXPORT DisTestComponentLocal
    : public DisTestComponent
{
  Q_OBJECT

public:
  explicit DisTestComponentLocal(const QString& name,
                                 const QHostAddress& ptcAddress,
                                 quint16 ptcPort,
                                 const quint16 localPort,
                                 const QString& serviceProvider = QStringLiteral("ptc"),
                                 QObject* parent = 0);
  virtual ~DisTestComponentLocal();

public:
  static void processRemoteReply(const QJsonRpcMessage& responseMessage,
                                 bool* result,
                                 QString* message);

public:
  State   remoteState() const;

public:
  virtual bool start(QString* errorString);
  virtual bool stop(QString* errorString);
  virtual bool cleanup(QString* errorString);

public:
  bool  run(QString* errorString);
  bool  isRunning() const;

public:
  void                setLocalAddressString(const QString& localAddressString);
  void                setLocalPort(const quint16 localPort);
  void                setPtcAddress(const QHostAddress& ptcAddress);
  void                setPtcPort(const quint16 ptcPort);

  const QString&      localAddressString() const;
  quint16             localPort() const;
  const QHostAddress& ptcAddress() const;
  quint16             ptcPort() const;

protected:
  bool                connectToPtc(QString* errorString);
  bool                connectToPtc(bool connectToMtc, QString* errorString);
  bool                isConnected() const;
  QJsonRpcSocket*     jsonRpcSocket() const;
  QJsonRpcTcpServer*  jsonRpcServer() const;

protected slots:
  void remoteSetuped();
  void remoteStarted();
  void remoteStopped();
  void remoteCleanuped();
  void remoteFinished(bool value,
                      QString message);
  void statusSlot();

private:
  Q_DISABLE_COPY(DisTestComponentLocal)
  class Private;
  Private* _d;
};

} // namespace distestruntime
} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENTLOCAL_HPP
