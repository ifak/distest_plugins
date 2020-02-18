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
#ifndef DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENT_HPP
#define DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENT_HPP

#include "../distestproject_global.hpp"

#include <QObject>
#include <mobata/prop/nameproperty.hpp>

#include <QUuid>

namespace distestproject{
namespace distestruntime {

class DISTESTPROJECTSHARED_EXPORT DisTestComponent
    : public QObject,
    public prop::NameProperty
{
  Q_OBJECT

public:
  enum State
  {
    IdleState,
    SetupedState,
    StartedState,
    StoppedState,
    FinishedState,
    ErrorState,
    UnknownState
  };

  enum MessageType
  {
    Info,
    Warning,
    Error,
    Fatal,
    UserMessageType
  };

public:
  DisTestComponent(const QString& name,
                   QObject* parent = nullptr);
  virtual ~DisTestComponent();

protected:
  virtual void reset() const;

public:
  static QString state2string(const State state);
  static State   string2state(const QString& stateString);

public:
  void    setState(const State newState);
  State   state() const;
  QString stateString() const;
  void    setEnabled(bool enabled);
  bool    isEnabled() const;

public:
  virtual bool setup(QString* errorString) = 0;
  virtual bool start(QString* errorString) = 0;
  virtual bool stop(QString* errorString) = 0;
  virtual bool cleanup(QString* errorString) = 0;

signals:
  void setuped(DisTestComponent* disTestComponent,
               bool value,
               QString message);
  void started(DisTestComponent* disTestComponent,
               bool value,
               QString message);
  void stopped(DisTestComponent* disTestComponent,
               bool value,
               QString message);
  void cleanuped(DisTestComponent* disTestComponent,
                 bool value,
                 QString message);
  void finished(DisTestComponent* disTestComponent,
                bool value,
                QString message);
  void errors(DisTestComponent* disTestComponent,
              QStringList errors);

  void message(DisTestComponent* disTestComponent,
               int messageType,
               QString message);

  void stepStarted(QUuid stepId,
                   QString message);
  void stepFinished(QUuid stepId,
                    bool result,
                    QString message);

private:
  Q_DISABLE_COPY(DisTestComponent)
  class Private;
  Private* _d;
};

} // namespace distestruntime
} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTRUNTIME_DISTESTCOMPONENT_HPP
