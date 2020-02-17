#include "distestcomponentlocalservice.hpp"

#include <QJsonValue>

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distestproject{
namespace distestruntime {

DisTestComponentLocalService::DisTestComponentLocalService(QObject* parent)
  : QJsonRpcService(parent)
{}

DisTestComponentLocalService::~DisTestComponentLocalService()
{}

QJsonValue DisTestComponentLocalService::ptcFinished(bool value,
                                                     QString message)
{
  qDebug()<<"DisTestComponentLocalService::ptcFinished() executed!";

  emit finishedReceived(value, message);

  QJsonArray response;
  response.append(true);
  response.append(QStringLiteral(""));

  return response;
}

QJsonValue DisTestComponentLocalService::ptcMessage(QString message)
{
  qDebug()<<"DisTestComponentLocalService::ptcMessage() executed!";

  emit messageReceived(message);

  QJsonArray response;
  response.append(true);
  response.append(QStringLiteral(""));

  return response;
}

QJsonValue DisTestComponentLocalService::currStepStarted(QUuid stepId)
{
  qDebug()<< "DisTestComponentLocalService::currStepStarted";
  emit currStepStartedReceived(stepId, QLatin1String(""));

  QJsonArray response;
  response.append(true);
  response.append(QStringLiteral(""));

  return response;
}

QJsonValue DisTestComponentLocalService::currStepFinished(QUuid stepId, bool stepResult)
{
  qDebug()<< "DisTestComponentLocalService::currStepFinished";
  emit currStepFinishedReceived(stepId, stepResult, QLatin1String(""));

  QJsonArray response;
  response.append(true);
  response.append(QStringLiteral(""));

  return response;
}

} // namespace distestruntime
} // namespace distestproject
