#include "distestcomponent.hpp"

#include <mobata/memory_leak_start.hpp>

namespace distestproject{
namespace distestruntime {

class DisTestComponent::Private
{
  friend class DisTestComponent;

  State       _state;
  bool        _enabled;
  QStringList _errors;

  Private()
    : _state(IdleState),
      _enabled(true)
  {}
};

DisTestComponent::DisTestComponent(const QString& name, QObject* parent)
  : QObject(parent),
    prop::NameProperty(name),
    _d(new Private)
{}

DisTestComponent::~DisTestComponent()
{
  delete this->_d;
}

void DisTestComponent::reset() const
{
  this->_d->_errors.clear();
  this->_d->_state = IdleState;

  return;
}

DisTestComponent::State DisTestComponent::string2state(const QString& stateString)
{
  if(stateString.compare(QStringLiteral("Idle"), Qt::CaseInsensitive) == 0)
    return IdleState;
  else if(stateString.compare(QStringLiteral("Setuped"), Qt::CaseInsensitive) == 0)
    return SetupedState;
  else if(stateString.compare(QStringLiteral("Started"), Qt::CaseInsensitive) == 0)
    return StartedState;
  else if(stateString.compare(QStringLiteral("Stopped"), Qt::CaseInsensitive) == 0)
    return StoppedState;
  else if(stateString.compare(QStringLiteral("Finished"), Qt::CaseInsensitive) == 0)
    return FinishedState;
  else if(stateString.compare(QStringLiteral("Error"), Qt::CaseInsensitive) == 0)
    return ErrorState;

  return UnknownState;
}

QString DisTestComponent::state2string(const State state)
{
  switch (state)
  {
    case IdleState:
      return QStringLiteral("Idle");
    case SetupedState:
      return QStringLiteral("Setuped");
    case StartedState:
      return QStringLiteral("Started");
    case StoppedState:
      return QStringLiteral("Stopped");
    case FinishedState:
      return QStringLiteral("Finished");
    case ErrorState:
      return QStringLiteral("Error");
    default:
      return QStringLiteral("Unknown State");
  }
}

void DisTestComponent::setState(const State newState)
{
  this->_d->_state = newState;
}

DisTestComponent::State DisTestComponent::state() const
{
  return this->_d->_state;
}

QString DisTestComponent::stateString() const
{
  return state2string(this->_d->_state);
}

void DisTestComponent::setEnabled(bool enabled)
{
  this->_d->_enabled = enabled;
}

bool DisTestComponent::isEnabled() const
{
  return this->_d->_enabled;
}

} // namespace distestruntime
} // namespace distestproject
