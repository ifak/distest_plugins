#include "sutgraphicwidget.hpp"

#include <mobata/utils/functors.hpp>
#include <mobatawidgets/ts/sutscene.hpp>

#include <mobata/memory_leak_start.hpp>

namespace suteditor {

class SutGraphicWidget::Private
{
  friend class SutGraphicWidget;

  QToolBar* _toolBar;
};

SutGraphicWidget::SutGraphicWidget(QWidget *parent)
  : view::ts::SutView(parent),
    _d(new Private)
{}

SutGraphicWidget::~SutGraphicWidget()
{
  delete this->_d;
}

view::ts::SutScene* SutGraphicWidget::sutScene()
{
  if(this->scene())
    return utils::simple_cast<view::ts::SutScene*>(this->scene());

  return 0;
}

void SutGraphicWidget::createToolBar()
{

  return;
}

} // namespace suteditor

