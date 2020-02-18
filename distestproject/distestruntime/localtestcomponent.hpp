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
#ifndef DISTESTPROJECT_DISTESTRUNTIME_LOCALTESTCOMPONENT_HPP
#define DISTESTPROJECT_DISTESTRUNTIME_LOCALTESTCOMPONENT_HPP

#include "distestcomponent.hpp"

namespace distestproject{
namespace distestruntime {

class DISTESTPROJECTSHARED_EXPORT LocalTestComponent
    : public DisTestComponent
{
  Q_OBJECT

public:
  LocalTestComponent(const QString& name,
                        QObject* parent = 0);
  virtual ~LocalTestComponent();

private:
  Q_DISABLE_COPY(LocalTestComponent)
  class Private;
  Private* _d;
};

} // namespace distestruntime
} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTRUNTIME_LOCALTESTCOMPONENT_HPP
