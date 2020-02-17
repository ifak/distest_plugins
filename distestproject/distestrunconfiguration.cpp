#include "distestrunconfiguration.hpp"


#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

///DisTestRunConfiguration//////////

class DisTestRunConfiguration::Private
{
  friend class DisTestRunConfiguration;

  bool _enabled;

  Private()
    : _enabled(true)
  {}
};

DisTestRunConfiguration::DisTestRunConfiguration(ProjectExplorer::Target* parent,
                                                 const Core::Id& id,
                                                 const QString& displayName)
  : ProjectExplorer::RunConfiguration(parent, id),
    _d(new Private)
{
  Q_ASSERT(parent);

  this->setDisplayName(displayName);
}

DisTestRunConfiguration::~DisTestRunConfiguration()
{
  delete this->_d;
}

QWidget* DisTestRunConfiguration::createConfigurationWidget()
{
  return 0;
}

QString DisTestRunConfiguration::title() const
{
  return this->displayName();
}

void DisTestRunConfiguration::setEnabled(const bool enabled)
{
  if(this->_d->_enabled == enabled)
    return;

  this->_d->_enabled=enabled;
  emit enabledChanged();

  return;
}

bool DisTestRunConfiguration::isEnabled() const
{
  return this->_d->_enabled;
}

} // namespace distestproject

