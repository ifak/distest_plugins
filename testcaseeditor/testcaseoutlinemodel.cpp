#include "testcaseoutlinemodel.hpp"

#include <mobata/model/ts/sutitem.hpp>
#include <mobata/model/ts/testsystemitem.hpp>
#include <mobata/model/ts/testcaseitem.hpp>

#include <mobata/memory_leak_start.hpp>

using namespace model::ts;
using namespace dslparser;

namespace testcaseeditor {

class TestCaseOutlineModel::Private
{
  friend class TestCaseOutlineModel;

  SutItemPtr        _sutModel = nullptr;
  TestSystemItemPtr _testSystemModel = nullptr;
  TestCaseItemPtr   _testCaseModel = nullptr;
};

TestCaseOutlineModel::TestCaseOutlineModel(QObject* parent)
  : dsleditor::DslOutlineModel(parent),
    _d(new Private)
{
  this->_d->_sutModel = SutItemPtr(new model::ts::SutItem());
  this->_d->_testSystemModel = TestSystemItemPtr(new model::ts::TestSystemItem(this->_d->_sutModel.data()));
  this->_d->_testCaseModel = TestCaseItemPtr(new model::ts::TestCaseItem());

  this->invisibleRootItem()->appendRow(this->_d->_testCaseModel.data());
}

TestCaseOutlineModel::~TestCaseOutlineModel()
{
  delete this->_d;
}

const SutItemPtr& TestCaseOutlineModel::sutModel() const
{
  return this->_d->_sutModel;
}

const TestSystemItemPtr& TestCaseOutlineModel::testSystemModel() const
{
  return this->_d->_testSystemModel;
}

const TestCaseItemPtr& TestCaseOutlineModel::testCaseModel() const
{
  return this->_d->_testCaseModel;
}

void TestCaseOutlineModel::reset()
{
  this->_d->_sutModel->reset();
  this->_d->_testSystemModel->reset();
  this->_d->_testCaseModel->reset();

  return dsleditor::DslOutlineModel::reset();
}

} // namespace testcaseeditor
