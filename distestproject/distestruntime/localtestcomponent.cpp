#include "localtestcomponent.hpp"

#include <mobata/memory_leak_start.hpp>

namespace distestproject{
namespace distestruntime {

class LocalTestComponent::Private
{
  friend class LocalTestComponent;

  Private() {}
};

LocalTestComponent::LocalTestComponent(const QString& compName,
                                       QObject* parent)
  : DisTestComponent(compName, parent),
    _d(new Private)
{}

LocalTestComponent::~LocalTestComponent()
{
  delete this->_d;
}

} // namespace distestruntime
} // namespace distestproject
