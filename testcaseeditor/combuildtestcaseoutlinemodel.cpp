#include "combuildtestcaseoutlinemodel.hpp"

#include "testcaseoutlinemodel.hpp"

#include <mobata/memory_leak_start.hpp>

namespace testcaseeditor {

class ComBuildTestCaseOutlineModel::Private
{
  friend class ComBuildTestCaseOutlineModel;

  TestCaseOutlineModel*  _testCaseOutlineModel;

  Private(TestCaseOutlineModel* testcaseOutlineModel)
    : _testCaseOutlineModel(testcaseOutlineModel)
  {}
};

ComBuildTestCaseOutlineModel::ComBuildTestCaseOutlineModel(const QString& testCaseDocText,
                                                           TestCaseOutlineModel* testCaseOutlineModel,
                                                           const QString& praefix,
                                                           QObject* parent)
  : dslparser::testcase::ComBuildTestCaseModel(testCaseDocText,
                                               testCaseOutlineModel?testCaseOutlineModel->testCaseModel().data():nullptr,
                                               nullptr,
                                               praefix,
                                               false,
                                               parent),
    _d(new Private(testCaseOutlineModel))
{
  Q_ASSERT(this->_d->_testCaseOutlineModel);
  Q_ASSERT(this->_d->_testCaseOutlineModel->testCaseModel());
}

ComBuildTestCaseOutlineModel::~ComBuildTestCaseOutlineModel()
{
  delete this->_d;
}

bool ComBuildTestCaseOutlineModel::execute(QString* errorString)
{
  bool result = ComBuildTestCaseModel::execute(errorString);
  if(!result)
    return false;

  this->_d->_testCaseOutlineModel->setModelTextLocations(this->modelTextLocations());
  this->_d->_testCaseOutlineModel->setKeywordTextLocations(this->keywordTextLocations());

  return true;
}

} // namespace testcaseeditor
