#include "tsmodelproperty.hpp"

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{
namespace Internal{

class TsModelProperty::Private
{
    friend class TsModelProperty;

    Private(model::ts::TestSuite* tsModel)
        : _tsModel(tsModel)
    {
        if(!this->_tsModel)
            this->_tsModel = new model::ts::TestSuite();
    }

public:
    ~Private()
    {}

private:
    model::ts::TestSuite* _tsModel;
};

TsModelProperty::TsModelProperty(model::ts::TestSuite *tsModel)
    : _d(new Private(tsModel))
{    
}

TsModelProperty::~TsModelProperty()
{
}

void TsModelProperty::setTsModel(model::ts::TestSuite *tsModel)
{
    this->_d->_tsModel = tsModel;
    qDebug() << this->_d->_tsModel->rowCount();
    return;
}

model::ts::TestSuite* TsModelProperty::tsModel()
{
    return this->_d->_tsModel;
}

} //namespace Internal
} //namespace distesteditor
