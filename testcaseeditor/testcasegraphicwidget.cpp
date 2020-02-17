#include "testcasegraphicwidget.hpp"

#include "testcasegraphiceditor.hpp"
#include "testcasepreviewgraph.hpp"

#include <mobata/utils/functors.hpp>
#include <mobata/model/ts/testcaseitem.hpp>

#include <QToolBar>

#include <mobata/memory_leak_start.hpp>

namespace testcaseeditor {

class TestCaseGraphicWidget::Private
{
  friend class TestCaseGraphicWidget;

  TestCaseGraphicEditor*  _testCaseGraphicEditor;
  QToolBar*               _toolBar;
};

TestCaseGraphicWidget::TestCaseGraphicWidget(QWidget *parent)
  : graphlayout::MscQuickWidget(parent),
    _d(new Private)
{
  this->_d->_testCaseGraphicEditor = new TestCaseGraphicEditor(this);
  this->createToolBar();
}

TestCaseGraphicWidget::~TestCaseGraphicWidget()
{
  delete this->_d->_toolBar;
  delete this->_d;
}

void TestCaseGraphicWidget::createToolBar()
{
  QAction* zoomInAction = new QAction(QIcon(QLatin1String(":/mobata/images/zoomin_dark.png")),
                                      tr("zoom in"),
                                      this);
  zoomInAction->setStatusTip(tr("zoom in"));
  zoomInAction->setToolTip(tr("zoom in"));
  zoomInAction->setCheckable(false);
  zoomInAction->setAutoRepeat(true);
  zoomInAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
  connect(zoomInAction, &QAction::triggered,
          this, &TestCaseGraphicWidget::zoomIn);

  QAction* zoomOutAction = new QAction(QIcon(QLatin1String(":/mobata/images/zoomout_dark.png")),
                                       tr("zoom out"),
                                       this);
  zoomOutAction->setStatusTip(tr("zoom out"));
  zoomOutAction->setToolTip(tr("zoom out"));
  zoomOutAction->setCheckable(false);
  zoomOutAction->setAutoRepeat(true);
  zoomOutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
  connect(zoomOutAction, &QAction::triggered,
          this, &TestCaseGraphicWidget::zoomOut);

  QAction* zoomFitInViewAction = new QAction(QIcon(QLatin1String(":/mobata/images/zoominview_dark.png")),
                                             tr("zoom fit in view"),
                                             this);
  zoomFitInViewAction->setStatusTip(tr("zoom fit in view"));
  zoomFitInViewAction->setToolTip(tr("zoom fit in view"));
  zoomFitInViewAction->setCheckable(false);
  connect(zoomFitInViewAction, &QAction::triggered,
          this, &TestCaseGraphicWidget::zoomFitAll);

  //  QAction* zoomResetAction = new QAction(QIcon(QLatin1String(":/mobata/images/zoomreset_dark.png")),
  //                                         tr("reset zoom"),
  //                                         this);
  //  zoomResetAction->setStatusTip(tr("reset zoom"));
  //  zoomResetAction->setToolTip(tr("reset zoom"));
  //  zoomResetAction->setCheckable(false);
  //  connect(zoomResetAction, &QAction::triggered,
  //          this, &TestCaseGraphicWidget::zoomReset);

  QAction* zoomFitWidthAction = new QAction(QIcon(QLatin1String(":/mobata/images/zoomwidth_dark.png")),
                                            tr("zoom fit width"),
                                            this);
  zoomFitWidthAction->setStatusTip(tr("zoom fit width"));
  zoomFitWidthAction->setToolTip(tr("zoom fit width"));
  zoomFitWidthAction->setCheckable(false);
  connect(zoomFitWidthAction, &QAction::triggered,
          this, &TestCaseGraphicWidget::zoomFitWidth);

  this->_d->_toolBar=new QToolBar;
  this->_d->_toolBar->addAction(zoomInAction);
  this->_d->_toolBar->addAction(zoomOutAction);
  this->_d->_toolBar->addAction(zoomFitInViewAction);
  //  this->_d->_toolBar->addAction(zoomResetAction);
  this->_d->_toolBar->addAction(zoomFitWidthAction);

  return;
}

QToolBar* TestCaseGraphicWidget::toolBar()
{
  return this->_d->_toolBar;
}

bool TestCaseGraphicWidget::updateTestCaseGraphic()
{
  //if(this->_d->_testCaseGraphicEditor != nullptr)
  //  return;

  QString errorString;

  qDebug()<<"TestCaseGraphicWidget::updateTestCaseGraphic";

  model::ts::TestCaseItem const* testCaseItem = this->_d->_testCaseGraphicEditor->testCaseItem();
  if(!testCaseItem)
    return false;

  testcaseGraphLoadSettings(this);
  this->setMscSequence(testCaseItem);

  if(!this->layout(&errorString,true))
  {
    utils::AddPtrString(&errorString) << "\nError during test case layouting!";
    return false;
  }

  return true;
}

void TestCaseGraphicWidget::setTestcaseGraphicEditor(TestCaseGraphicEditor* testCaseGraphicEditor) const
{
  this->_d->_testCaseGraphicEditor = testCaseGraphicEditor;
  return;
}

TestCaseGraphicEditor* TestCaseGraphicWidget::testCaseGraphicEditor() const
{
  if(this->_d->_testCaseGraphicEditor){
    return this->_d->_testCaseGraphicEditor;
  }
  return nullptr;
}

void TestCaseGraphicWidget::highlightGraphicItemByUuid(const QUuid& itemUuid,
                                                       bool highlight,
                                                       bool unhighlightOtherItems)
{
  if(unhighlightOtherItems)
    this->unhighlightAllGraphicItems();

  this->highlightItemByUuid(itemUuid, highlight);

  return;
}

void TestCaseGraphicWidget::highlightGraphicItemsByUuids(const QList<QUuid>& itemUuids,
                                                         bool highlight,
                                                         bool unhighlightOtherItems)
{
  if(unhighlightOtherItems)
    this->unhighlightAllGraphicItems();

  for(const QUuid& currItemUuid : itemUuids)
    this->highlightItemByUuid(currItemUuid, highlight);

  return;
}

void TestCaseGraphicWidget::highlightGraphicItemByName(const QString& itemName,
                                                       bool highlight,
                                                       bool unhighlightOtherItems)
{
  if(unhighlightOtherItems)
    this->unhighlightAllGraphicItems();

  this->highlightItemByName(itemName, highlight);

  return;
}

void TestCaseGraphicWidget::highlightGraphicItemsByNames(const QList<QString> &itemNames,
                                                         bool highlight,
                                                         bool unhighlightOtherItems)
{
  if(unhighlightOtherItems)
    this->unhighlightAllGraphicItems();

  for(const QString& currItemName : itemNames)
    this->highlightItemByName(currItemName, highlight);

  return;
}

} // namespace testcaseeditor

