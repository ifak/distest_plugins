#include "combuildsutoutlinemodel.hpp"

#include "sutoutlinemodel.hpp"

#include <mobata/memory_leak_start.hpp>

namespace suteditor {

class ComBuildSutOutlineModel::Private
{
  friend class ComBuildSutOutlineModel;

  SutOutlineModel*  _sutOutlineModel;

  Private(SutOutlineModel* sutOutlineModel)
    : _sutOutlineModel(sutOutlineModel)
  {}
};

ComBuildSutOutlineModel::ComBuildSutOutlineModel(const QString& sutDocText,
                                                 SutOutlineModel* sutOutlineModel,
                                                 QObject* parent)
  : dslparser::sut::ComBuildSutModel(sutDocText,
                                     sutOutlineModel?sutOutlineModel->sutModel():0,
                                     false,
                                     parent),
    _d(new Private(sutOutlineModel))
{
  Q_ASSERT(this->_d->_sutOutlineModel);
  Q_ASSERT(this->_d->_sutOutlineModel->sutModel());
}

ComBuildSutOutlineModel::~ComBuildSutOutlineModel()
{
  delete this->_d;
}

bool ComBuildSutOutlineModel::execute(QString* errorString)
{
  bool result = ComBuildSutModel::execute(errorString);
  if(!result)
    return false;

  this->_d->_sutOutlineModel->setModelTextLocations(this->modelTextLocations());
  this->_d->_sutOutlineModel->setKeywordTextLocations(this->keywordTextLocations());

  return true;
}

} // namespace suteditor
