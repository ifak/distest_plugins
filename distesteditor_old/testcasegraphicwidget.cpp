#include "testcasegraphicwidget.hpp"

#include <mobata/utils/functors.hpp>
#include <mobatawidgets/ts/testcasescene.hpp>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor {

class TestCaseGraphicWidget::Private
{
  friend class TestCaseGraphicWidget;

  QToolBar* _toolBar;
};

TestCaseGraphicWidget::TestCaseGraphicWidget(QWidget *parent)
  : view::ts::TestCaseView(parent),
    _d(new Private)
{}

TestCaseGraphicWidget::~TestCaseGraphicWidget()
{
  delete this->_d;
}

view::ts::TestCaseScene* TestCaseGraphicWidget::testCaseScene()
{
  if(this->scene())
    return utils::simple_cast<view::ts::TestCaseScene*>(this->scene());

  return 0;
}

void TestCaseGraphicWidget::createToolBar()
{

  return;
}

} // namespace distesteditor

