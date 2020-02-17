#include "decleditorwidget.hpp"
#include "decldocument.hpp"

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{

class DeclEditorWidget::Private
{
  friend class DeclEditorWidget;

  Private()
    : _declEditor(0)
  {}

public:
  ~Private()
  {}

private:
  DeclEditor* _declEditor;
};

DeclEditorWidget::DeclEditorWidget(QWidget *parent)
  : dsleditor::DslEditorWidget(parent), _d(new Private())
{
  this->setBaseTextDocument(QSharedPointer<DeclDocument>(new DeclDocument()));
  this->_d->_declEditor=new DeclEditor(this);
}

DeclEditorWidget::~DeclEditorWidget()
{
  delete this->_d;
}

DeclEditor *DeclEditorWidget::createEditor()
{
  qDebug()<<"DeclTextEditorWidget::createEditor() executed!";

  return this->_d->_declEditor;
}

} //end namespace distesteditor
