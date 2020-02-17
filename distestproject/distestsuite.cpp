#include "distestsuite.hpp"

#include <mobata/model/ts/testcaseitem.hpp>

#include <QFileInfo>

namespace distestproject {

typedef QHash<QString, model::ts::TestCaseItem*>  TestCasesMap;

class DisTestSuite::Private
{
  friend class DisTestSuite;

  QString       _sutFilePath;
  QString       _testSystemFilePath;
  TestCasesMap  _testCases;

  Private() {}
};

DisTestSuite::DisTestSuite(QObject* parent)
  : model::ts::TestSuite(parent), _d(new Private)
{}

DisTestSuite::~DisTestSuite()
{}

void DisTestSuite::setSutFilePath(const QString& sutFilePath)
{
  this->_d->_sutFilePath=sutFilePath;

  return;
}

void DisTestSuite::setTestSystemFilePath(const QString& testSystemFilePath)
{
  this->_d->_testSystemFilePath=testSystemFilePath;

  return;
}

const QString& DisTestSuite::sutFilePath() const
{
  return this->_d->_sutFilePath;
}

const QString& DisTestSuite::testSystemFilePath() const
{
  return this->_d->_testSystemFilePath;
}

bool DisTestSuite::addTestCase(const QString& testCaseFilePath,
                               model::ts::TestCaseItem* testCase,
                               QString* errorString)
{
  Q_ASSERT(testCase);

  if(!QFileInfo(testCaseFilePath).exists())
  {
    utils::AddPtrString(errorString)<<tr("test case file '%1' does not exist!")
                                      .arg(testCaseFilePath);
    return false;
  }


  if(!this->_d->_testCases.isEmpty() && this->_d->_testCases.contains(testCaseFilePath))
  {
    utils::AddPtrString(errorString)<<tr("there is already a test case file '%1' available!")
                                      .arg(testCaseFilePath);
    return false;
  }

  if(!model::ts::TestSuite::addTestCase(testCase, errorString))
    return false;

  this->_d->_testCases.insert(testCaseFilePath, testCase);

  return true;
}

void DisTestSuite::removeTestCase(const QString& testCaseFilePath)
{
  model::ts::TestCaseItem* removeTestCase=this->_d->_testCases.value(testCaseFilePath);
  if(!removeTestCase)
    return;

  model::ts::TestSuite::removeTestCase(removeTestCase);
  this->_d->_testCases.remove(testCaseFilePath);

  return;
}

QList<QString> DisTestSuite::testCaseFiles() const
{
  return this->_d->_testCases.keys();
}

model::ts::TestCaseItem* DisTestSuite::testCaseModel(const QString& testCaseFile)
{
  return this->_d->_testCases.value(testCaseFile, nullptr);
}

QString DisTestSuite::testCaseFile(const model::ts::TestCaseItem* testCaseModel) const
{
  for(TestCasesMap::const_iterator tc_it=this->_d->_testCases.begin();
      tc_it!=this->_d->_testCases.end();
      ++tc_it)
  {
    if(tc_it.value()==testCaseModel)
      return tc_it.key();
  }

  return QStringLiteral("");
}

} // namespace distestproject
