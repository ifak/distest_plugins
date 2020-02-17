#include "sutoutlinemodel.hpp"

#include <mobata/model/ts/sutitem.hpp>

#include <mobata/memory_leak_start.hpp>

using namespace dslparser;

namespace suteditor {

class SutOutlineModel::Private
{
  friend class SutOutlineModel;

  model::ts::SutItem* _sutModel;
};

SutOutlineModel::SutOutlineModel(QObject* parent)
  : dsleditor::DslOutlineModel(parent),
    _d(new Private)
{
  this->_d->_sutModel = new model::ts::SutItem;
  this->invisibleRootItem()->appendRow(this->_d->_sutModel);
}

SutOutlineModel::~SutOutlineModel()
{
  delete this->_d;
}

model::ts::SutItem* SutOutlineModel::sutModel()
{
  return this->_d->_sutModel;
}

void SutOutlineModel::reset()
{
  this->_d->_sutModel->reset();

  return dsleditor::DslOutlineModel::reset();
}

} // namespace suteditor
