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
#ifndef DISTESTEDITOR_INTERNAL_TSMODELPROPERTY_H
#define DISTESTEDITOR_INTERNAL_TSMODELPROPERTY_H

#include <mobata/model/ts/testsuite.hpp>

namespace distesteditor{
namespace Internal{

class TsModelProperty
{
public:
  TsModelProperty(model::ts::TestSuite* tsModel = 0);
  virtual ~TsModelProperty();

public:
  void setTsModel(model::ts::TestSuite* tsModel);
  model::ts::TestSuite* tsModel();

private:
  Q_DISABLE_COPY(TsModelProperty)
  class Private;
  QScopedPointer<Private> _d;
};

} // namespace Internal
} // namespace distesteditor

#endif // DISTESTEDITOR_INTERNAL_TSMODELPROPERTY_H
