#include "sutgraphiceditor.hpp"

#include "suteditorconstants.hpp"
#include "sutgraphicwidget.hpp"
#include "sutgraphicdocument.hpp"

#include <mobata/utils/functors.hpp>
#include <mobatawidgets/ts/sutscene.hpp>

#include <QToolBar>
#include <QFileInfo>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace suteditor {

class SutGraphicEditor::Private
{
  friend class SutGraphicEditor;

  Private()
    : _sutItem(0),
      _sutGraphicDocument(0)
  {}

  model::ts::SutItem const*  _sutItem;
  SutGraphicDocument*        _sutGraphicDocument;
  QString                    _displayName;
};

SutGraphicEditor::SutGraphicEditor(SutGraphicWidget* sutGraphicWidget)
  : dsleditor::DslGraphicEditor(Constants::SUTGRAPHIC_ID),
    _d(new Private)
{
  Q_ASSERT(sutGraphicWidget);

  this->_d->_sutGraphicDocument=new SutGraphicDocument(this);
  sutGraphicWidget->setScene(this->_d->_sutGraphicDocument->sutScene());
  this->setWidget(sutGraphicWidget);
}

SutGraphicEditor::~SutGraphicEditor()
{
  delete this->_d;
}

bool SutGraphicEditor::open(QString* errorString,
                                 const QString& fileName,
                                 const QString& realFileName)
{
  Q_UNUSED(errorString);
  Q_UNUSED(realFileName);

  bool result=this->_d->_sutGraphicDocument->open(errorString,
                                                       fileName,
                                                       realFileName);

  if(!result)
     return false;

  QFileInfo fileInfo(this->_d->_sutGraphicDocument->fileName());
  if(!fileInfo.exists())
    return false;

  this->setDisplayName(fileInfo.fileName());

  return true;
}

Core::IDocument*  SutGraphicEditor::document()
{
  return this->_d->_sutGraphicDocument;
}

QWidget* SutGraphicEditor::toolBar()
{
  return 0;
}

void SutGraphicEditor::setSutItem(model::ts::SutItem const* sutItem)
{
  this->_d->_sutItem=sutItem;

  return;
}

model::ts::SutItem const* SutGraphicEditor::sutItem() const
{
  return this->_d->_sutItem;
}


SutGraphicWidget* SutGraphicEditor::sutGraphicWidget()
{
  return utils::simple_cast<SutGraphicWidget*>(this->m_widget.data());
}

QString SutGraphicEditor::fileName() const
{
  return this->_d->_sutGraphicDocument->fileName();
}

} // namespace suteditor

