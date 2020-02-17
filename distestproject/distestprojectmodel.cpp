#include "distestprojectmodel.hpp"

#include "distestsuite.hpp"

#include <mobata/model/ts/sutitem.hpp>
#include <mobata/model/ts/testsystemitem.hpp>
#include <mobata/model/ts/testcaseitem.hpp>

#include <QDebug>

namespace distestproject {

class DisTestProjectModel::Private
{
  friend class DisTestProjectModel;

  typedef QHash<DisTestSuite*, QStandardItem*>  TestSuiteSet;

  TestSuiteSet  _testSuites;

  Private()
  {}
};

DisTestProjectModel::DisTestProjectModel(QObject *parent)
  : QStandardItemModel(parent), _d(new Private)
{
  this->setColumnCount(1);
  this->setHeaderData(0, Qt::Horizontal,
                      tr("Test Execution Settings"),
                      Qt::DisplayRole);

  connect(this, &DisTestProjectModel::itemChanged,
          this, &DisTestProjectModel::handleItemChange);
}

DisTestProjectModel::~DisTestProjectModel()
{
  delete this->_d;
}

void DisTestProjectModel::reset()
{
  this->invisibleRootItem()->removeRows(0, this->invisibleRootItem()->rowCount());
  qDeleteAll(this->_d->_testSuites.keys());
  this->_d->_testSuites.clear();

  return;
}

void DisTestProjectModel::addDisTestSuite(DisTestSuite* disTestSuite)
{
  if(!disTestSuite)
    return;

  if(this->_d->_testSuites.find(disTestSuite)!=this->_d->_testSuites.end())
    return;

  QStandardItem* newTestSuiteItem = new QStandardItem(disTestSuite->name());
  newTestSuiteItem->setIcon(QIcon(QStringLiteral(":/mobata/images/ts/testsuite.png")));
  newTestSuiteItem->setFlags(newTestSuiteItem->flags() & ~Qt::ItemIsEditable);
  newTestSuiteItem->setCheckable(true);
  newTestSuiteItem->setData(DisTestSuite::TestSuiteType, DisTestSuite::DisTestTypeRole);
  this->invisibleRootItem()->appendRow(newTestSuiteItem);

  this->_d->_testSuites.insert(disTestSuite, newTestSuiteItem);

  this->updateDisTestSuite(disTestSuite);

  return;
}

void DisTestProjectModel::updateDisTestSuite(DisTestSuite* disTestSuite)
{
  if(!disTestSuite)
    return;

  Private::TestSuiteSet::iterator find_it = this->_d->_testSuites.find(disTestSuite);

  if(find_it==this->_d->_testSuites.end())
    return;

  QStandardItem* testSuiteItem = find_it.value();
  Q_ASSERT(testSuiteItem);
  testSuiteItem->setText(disTestSuite->name());
  testSuiteItem->removeRows(0, testSuiteItem->rowCount());

  QStandardItem* sutItem = new QStandardItem(disTestSuite->sutItem()->name());
  sutItem->setIcon(QIcon(QStringLiteral(":/mobata/images/ts/sut.png")));
  sutItem->setFlags(sutItem->flags()
                    & ~Qt::ItemIsEditable
                    & ~Qt::ItemIsDropEnabled
                    & ~Qt::ItemIsDragEnabled);
  sutItem->setData(DisTestSuite::SutType, DisTestSuite::DisTestTypeRole);
  sutItem->setData(disTestSuite->sutFilePath(), DisTestSuite::FileNameRole);
  testSuiteItem->appendRow(sutItem);

  QStandardItem* testSystemItem = new QStandardItem(disTestSuite->testSystemItem()->name());
  testSystemItem->setIcon(QIcon(QStringLiteral(":/mobata/images/ts/testsystem.png")));
  testSystemItem->setFlags(testSystemItem->flags()
                           & ~Qt::ItemIsEditable
                           & ~Qt::ItemIsDropEnabled
                           & ~Qt::ItemIsDragEnabled);
  testSystemItem->setData(DisTestSuite::TestSystemType, DisTestSuite::DisTestTypeRole);
  testSystemItem->setData(disTestSuite->testSystemFilePath(), DisTestSuite::FileNameRole);
  testSuiteItem->appendRow(testSystemItem);

  for(const QString& testCaseFile : disTestSuite->testCaseFiles())
  {
    model::ts::TestCaseItem* testCaseModel = disTestSuite->testCaseModel(testCaseFile);
    Q_ASSERT(testCaseModel);

    QStandardItem* newTestCaseItem = new QStandardItem(testCaseModel->name());
    newTestCaseItem->setIcon(QIcon(QStringLiteral(":/mobata/images/ts/testcase.png")));
    newTestCaseItem->setFlags(newTestCaseItem->flags() & ~Qt::ItemIsEditable);
    newTestCaseItem->setCheckable(true);
    if(testCaseModel->isEnabled()){
      newTestCaseItem->setCheckState(Qt::CheckState::Checked);
    }else {
      newTestCaseItem->setCheckState(Qt::CheckState::Unchecked);
    }
    newTestCaseItem->setData(DisTestSuite::TestCaseType, DisTestSuite::DisTestTypeRole);
    newTestCaseItem->setData(testCaseFile, DisTestSuite::FileNameRole);
    testSuiteItem->appendRow(newTestCaseItem);
  }

  return;
}

DisTestSuite* DisTestProjectModel::disTestSuite(const QString& testSystemFilePath)
{
  for(DisTestSuite* disTestSuite : this->_d->_testSuites.keys())
  {
    if(disTestSuite->testSystemFilePath() == testSystemFilePath)
      return disTestSuite;
  }

  return 0;
}

QList<DisTestSuite*> DisTestProjectModel::disTestSuites() const
{
  return this->_d->_testSuites.keys();
}

Qt::DropActions DisTestProjectModel::supportedDropActions() const
{
  return Qt::MoveAction;
}

void DisTestProjectModel::handleItemChange(QStandardItem* item)
{
  if(!item)
    return;

  if(item->isCheckable() && item->data(DisTestSuite::DisTestTypeRole) == DisTestSuite::TestSuiteType){
    int rowCount = item->rowCount();
    for(int i = 0; i<rowCount; ++i)
    {
      QStandardItem* childItem = item->child(i);
      if(!childItem->isCheckable())
        continue;

      if(item->checkState()==Qt::Checked)
        childItem->setCheckState(Qt::Checked);
      else if(item->checkState()==Qt::Unchecked)
        childItem->setCheckState(Qt::Unchecked);
    }
  }else if(item->isCheckable() && item->data(DisTestSuite::DisTestTypeRole) == DisTestSuite::TestCaseType){
    for(DisTestSuite* suite : this->_d->_testSuites.keys()){
      if (this->_d->_testSuites.value(suite) == item->parent()){
        for(QString filename : suite->testCaseFiles()){
          model::ts::TestCaseItem* tc = suite->testCaseModel(filename);
          if(tc->name() == item->text()){
            QFile file(filename);
            file.open(QIODevice::ReadWrite);
            QString data = file.readAll();
            file.close();
            file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
            QStringList dataList = data.split("\n");
            data = "";
            for(QString line : dataList){
              if(line.contains("enabled:")){
                if(item->checkState()==Qt::Checked){
                  tc->setEnabled(true);
                  line = "    enabled: true;";
                }else if(item->checkState()==Qt::Unchecked){
                  tc->setEnabled(false);
                  line = "    enabled: false;";
                }
              }
              data += line + "\n";
            }
            file.write(data.toUtf8());
            file.close();
          }
        }
      }
    }
  }

  return;
}

} // namespace distestproject
