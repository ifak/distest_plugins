#include "diagnosisgraphicwidget.hpp"

#include <mobata/utils/functors.hpp>

#include <QToolBar>

#include <mobata/memory_leak_start.hpp>

namespace diagnosiseditor {

class DiagnosisGraphicWidget::Private
{
  friend class DiagnosisGraphicWidget;

  QToolBar* _toolBar;
};

DiagnosisGraphicWidget::DiagnosisGraphicWidget(QWidget *parent)
  : graphlayout::GraphQuickWidget(nullptr,
                                  graphlayout::Dot,
                                  parent),
    _d(new Private)
{}

DiagnosisGraphicWidget::~DiagnosisGraphicWidget()
{
  delete this->_d->_toolBar;
  delete this->_d;
}

void DiagnosisGraphicWidget::createToolBar()
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
          this, &DiagnosisGraphicWidget::zoomIn);

  QAction* zoomOutAction = new QAction(QIcon(QLatin1String(":/mobata/images/zoomout_dark.png")),
                                       tr("zoom out"),
                                       this);
  zoomOutAction->setStatusTip(tr("zoom out"));
  zoomOutAction->setToolTip(tr("zoom out"));
  zoomOutAction->setCheckable(false);
  zoomOutAction->setAutoRepeat(true);
  zoomOutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
  connect(zoomOutAction, &QAction::triggered,
          this, &DiagnosisGraphicWidget::zoomOut);

  QAction* zoomFitInViewAction = new QAction(QIcon(QLatin1String(":/mobata/images/zoominview_dark.png")),
                                             tr("zoom fit in view"),
                                             this);
  zoomFitInViewAction->setStatusTip(tr("zoom fit in view"));
  zoomFitInViewAction->setToolTip(tr("zoom fit in view"));
  zoomFitInViewAction->setCheckable(false);
  connect(zoomFitInViewAction, &QAction::triggered,
          this, &DiagnosisGraphicWidget::zoomFull);

  QAction* zoomResetAction = new QAction(QIcon(QLatin1String(":/mobata/images/zoomreset_dark.png")),
                                         tr("reset zoom"),
                                         this);
  zoomResetAction->setStatusTip(tr("reset zoom"));
  zoomResetAction->setToolTip(tr("reset zoom"));
  zoomResetAction->setCheckable(false);
  connect(zoomResetAction, &QAction::triggered,
          this, &DiagnosisGraphicWidget::zoomReset);

  this->_d->_toolBar=new QToolBar;
  this->_d->_toolBar->addAction(zoomInAction);
  this->_d->_toolBar->addAction(zoomOutAction);
  this->_d->_toolBar->addAction(zoomFitInViewAction);
  this->_d->_toolBar->addAction(zoomResetAction);

  return;
}

QToolBar* DiagnosisGraphicWidget::toolBar()
{
  return this->_d->_toolBar;
}

} // namespace diagnosiseditor

