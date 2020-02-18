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
#ifndef DISTESTPROJECT_COMSAVEDISTESTOBJECTASQML_HPP
#define DISTESTPROJECT_COMSAVEDISTESTOBJECTASQML_HPP

#include "distestproject_global.hpp"

#include <mobata/utils/comsaveobjectasqml.hpp>

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT  ComSaveDisTestObjectAsQml
    : public ComSaveObjectAsQml
{
public:
  ComSaveDisTestObjectAsQml(QObject* object,
                            const QString& qmlTypeName,
                            const QString& filePath);
};

}/// end namespace distestproject

#endif // DISTESTPROJECT_COMSAVEDISTESTOBJECTASQML_HPP
