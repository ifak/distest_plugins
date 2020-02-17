#include "testsystemgraphicwidget.hpp"

#include <mobata/utils/functors.hpp>
#include <mobatawidgets/ts/testsystemscene.hpp>

#include <mobata/memory_leak_start.hpp>

namespace testsystemeditor {

class TestSystemGraphicWidget::Private
{
  friend class TestSystemGraphicWidget;

  QToolBar* _toolBar;
};

TestSystemGraphicWidget::TestSystemGraphicWidget(QWidget *parent)
  : view::ts::TestSystemView(parent),
    _d(new Private)
{}

TestSystemGraphicWidget::~TestSystemGraphicWidget()
{
  delete this->_d;
}

view::ts::TestSystemScene* TestSystemGraphicWidget::testSystemScene()
{
  if(this->scene())
    return utils::simple_cast<view::ts::TestSystemScene*>(this->scene());

  return 0;
}

void TestSystemGraphicWidget::createToolBar()
{

  return;
}

} // namespace testsystemeditor

