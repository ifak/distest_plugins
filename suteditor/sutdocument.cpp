#include "sutdocument.hpp"

#include "sutoutlinemodel.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace model::ts;
using namespace suteditor;

class SutDocument::Private
{
  friend class SutDocument;

  SutOutlineModel*  _sutOutlineModel;

  Private()
    : _sutOutlineModel(0)
  {}
};

SutDocument::SutDocument(QObject *parent)
  : TextEditor::BaseTextDocument(parent),
    _d(new Private)
{
  this->_d->_sutOutlineModel = new SutOutlineModel();
}

SutDocument::~SutDocument()
{
  delete this->_d->_sutOutlineModel;
  delete this->_d;
}

SutOutlineModel* SutDocument::sutOutlineModel()
{
  return this->_d->_sutOutlineModel;
}
