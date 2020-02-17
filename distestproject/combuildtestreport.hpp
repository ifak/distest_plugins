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
#ifndef DISTESTPROJECT_COMBUILDTESTREPORT_H
#define DISTESTPROJECT_COMBUILDTESTREPORT_H

#include <QString>

namespace distestproject {

namespace distestruntime{
class DisTestRuntime;
}


class ComBuildTestReport
{
public:
  explicit ComBuildTestReport(distestruntime::DisTestRuntime* disTestRuntime);
  virtual ~ComBuildTestReport();

public:
  QString execute();

private:
  Q_DISABLE_COPY(ComBuildTestReport)
  class Private;
  Private* _d;
};

} // namespace distestproject

#endif // DISTESTPROJECT_COMBUILDTESTREPORT_H
