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
#ifndef DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENTLOCALSERVICE_HPP
#define DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENTLOCALSERVICE_HPP

#include "../distestproject_global.hpp"

#include <qjsonrpcservice.h>

#include <QUuid>

namespace distestproject{
namespace distestruntime {

class DISTESTPROJECTSHARED_EXPORT DisTestComponentLocalService
    : public QJsonRpcService
{
  Q_OBJECT
  Q_CLASSINFO("serviceName", "mtc")

public:
  DisTestComponentLocalService(QObject* parent = 0);
  virtual ~DisTestComponentLocalService();

signals:
  void finishedReceived(bool value, QString message);
  void messageReceived(QString message);
  void currStepStartedReceived(QUuid stepId, QString message);
  void currStepFinishedReceived(QUuid stepId, bool result, QString message);

public Q_SLOTS:
  QJsonValue ptcFinished(bool value, QString message);
  QJsonValue ptcMessage(QString message);
  QJsonValue currStepStarted(QUuid stepId);
  QJsonValue currStepFinished(QUuid stepId, bool stepResult);
};

} // namespace distestruntime
} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENTLOCALSERVICE_HPP
