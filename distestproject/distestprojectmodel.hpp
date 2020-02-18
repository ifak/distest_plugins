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
#pragma once

#include "distestproject_global.hpp"

#include <QStandardItemModel>

namespace distestproject {

class DisTestSuite;

class DISTESTPROJECTSHARED_EXPORT DisTestProjectModel
    : public QStandardItemModel
{
  Q_OBJECT
public:
  explicit DisTestProjectModel(QObject* parent = nullptr);
  virtual ~DisTestProjectModel();

public:
  void reset();

public:
  void                  addDisTestSuite(DisTestSuite* disTestSuite);
  void                  updateDisTestSuite(DisTestSuite* disTestSuite);
  DisTestSuite*         disTestSuite(const QString& testSystemFilePath);
  QList<DisTestSuite*>  disTestSuites() const;

protected:
  Qt::DropActions supportedDropActions() const;

private slots:
  void handleItemChange(QStandardItem* item);

private:
  Q_DISABLE_COPY(DisTestProjectModel)
  class Private;
  Private*  _d;
};

} // namespace distestproject
