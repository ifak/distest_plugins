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
#ifndef DISTESTPROJECT_HELPERS_HPP
#define DISTESTPROJECT_HELPERS_HPP

#include "distestproject_global.hpp"

#include <mobata/model/base/attributeitem.hpp>
#include <mobata/model/ts/ts_types.hpp>
#include "clickablelabel.hpp"

namespace ProjectExplorer
{
class Project;
class Node;
}

namespace distestproject
{

class DISTESTPROJECTSHARED_EXPORT Helpers
{
public:
  static ProjectExplorer::Project*  projectForFile(const QString& fileName);
  static ProjectExplorer::Node*     nodeForFile(const QString& fileName,
                                                ProjectExplorer::Project* project);

  static void changeLabelColor(ClickableLabel *label, const QColor &color);
  static unsigned int availableFontSettingsState(const QFont &font);

  template<class ModelType> inline
  static QString attributeValue(ModelType const* modelType,
                                const QString& attributeName,
                                bool* success,
                                QString* errorString)
  {
    Q_ASSERT(modelType);

    model::base::AttributeItem const* attributeItem = modelType->attribute(attributeName);
    if(!attributeItem)
    {
      if(success)
        *success = false;
      if(errorString)
        *errorString += QObject::tr("no attribute '%1' for object '%2' available!")
                        .arg(attributeName).arg(modelType->name());

      return QString();
    }

    return attributeItem->initValue();
  }

};

}/// end namespace distestproject

#endif // DISTESTPROJECT_HELPERS_HPP
