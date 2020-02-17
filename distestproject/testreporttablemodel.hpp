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
#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QDebug>


namespace distestproject {

class TestReportTableModel : public QAbstractTableModel
{
  Q_OBJECT
public:

  enum Role: unsigned int {
    OneRole=Qt::UserRole,
    TwoRole,
    ThreeRole,
    FourRole
  };

  TestReportTableModel(int sizeY);
  TestReportTableModel();
  ~TestReportTableModel();
  int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
  int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  void pushBack(QVector<QVariant> data);
  void setSizeY(int sizeY);

  QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
signals:

public slots:
  void theDataChanged();
private:
  int m_size_y;
  QList<QVector<QVariant>> m_the_data;
};

} // distestproject
