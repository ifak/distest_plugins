#include "testreporttablemodel.hpp"

namespace distestproject{


TestReportTableModel::TestReportTableModel(int sizeY) : QAbstractTableModel(0)
{
    m_size_y = sizeY;
}

TestReportTableModel::~TestReportTableModel(){

}

void TestReportTableModel::pushBack(QVector<QVariant> data){
    m_the_data.append(data);
}

int TestReportTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_the_data.size();
}

int TestReportTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_size_y;
}

QVariant TestReportTableModel::data(const QModelIndex &index, int role) const
{
  switch(role)
  {
      case OneRole:
          return m_the_data[index.row()][0];
      case TwoRole:
          return m_the_data[index.row()][1];
      case ThreeRole:
          return m_the_data[index.row()][2];
  }
    return QVariant();
}

QHash<int, QByteArray> TestReportTableModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[OneRole] = "one";
  roles[TwoRole] = "two";
  roles[ThreeRole] = "three";
  roles[FourRole] = "four";
  return roles;
}

/**
 * for compatibility the data is needs to be deletet, be aware
 */
void TestReportTableModel::setSizeY(int sizeY){
    this->m_size_y = sizeY;
    this->m_the_data.clear();
}

void TestReportTableModel::theDataChanged()
{
    //TODO
}

}
