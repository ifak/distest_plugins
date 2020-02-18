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
#ifndef DISTESTPROJECT_DISTESTRUNCONFIGURATION_HPP
#define DISTESTPROJECT_DISTESTRUNCONFIGURATION_HPP

#include "distestproject_global.hpp"

#include <projectexplorer/runconfiguration.h>

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT DisTestRunConfiguration
    : public ProjectExplorer::RunConfiguration
{
  Q_OBJECT

  friend class DisTestRunConfigurationFactory;

public:
  DisTestRunConfiguration(ProjectExplorer::Target* parent,
                          const Core::Id& id,
                          const QString& displayName);
  virtual ~DisTestRunConfiguration();

public:
  virtual QWidget*  createConfigurationWidget();
  virtual QString   title() const;
  virtual bool      isEnabled() const;

public slots:
  void setEnabled(const bool enabled);

private:
  Q_DISABLE_COPY(DisTestRunConfiguration)
  class Private;
  Private* _d;
};

} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTRUNCONFIGURATION_HPP
