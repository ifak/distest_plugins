#include "diagnosisgraphiceditor.hpp"

#include "diagnosiseditorconstants.hpp"
#include "diagnosisgraphicwidget.hpp"
#include "diagnosisgraphicdocument.hpp"

#include <QToolBar>
#include <QFileInfo>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace diagnosiseditor {

class DiagnosisGraphicEditor::Private
{
  friend class DiagnosisGraphicEditor;

  Private()
    : _diagnosisItem(0),
      _diagnosisGraphicDocument(0)
  {}

  model::diagnosis::DiagnosisItem const*  _diagnosisItem;
  DiagnosisGraphicDocument*               _diagnosisGraphicDocument;
};

DiagnosisGraphicEditor::DiagnosisGraphicEditor(DiagnosisGraphicWidget* diagnosisGraphicWidget)
  : dsleditor::DslGraphicEditor(Constants::DIAGNOSISGRAPHIC_ID),
    _d(new Private)
{
  Q_ASSERT(diagnosisGraphicWidget);

  this->_d->_diagnosisGraphicDocument=new DiagnosisGraphicDocument(this);
  this->setWidget(diagnosisGraphicWidget);
}

DiagnosisGraphicEditor::~DiagnosisGraphicEditor()
{
  delete this->_d;
}

bool DiagnosisGraphicEditor::open(QString* errorString,
                                 const QString& fileName,
                                 const QString& realFileName)
{
  Q_UNUSED(errorString);
  Q_UNUSED(realFileName);

  bool result=this->_d->_diagnosisGraphicDocument->open(errorString,
                                                       fileName,
                                                       realFileName);

  if(!result)
     return false;

  QFileInfo fileInfo(this->_d->_diagnosisGraphicDocument->fileName());
  if(!fileInfo.exists())
    return false;

  this->setDisplayName(fileInfo.fileName());

  return true;
}

Core::IDocument*  DiagnosisGraphicEditor::document()
{
  return this->_d->_diagnosisGraphicDocument;
}

void DiagnosisGraphicEditor::setDiagnosisItem(model::diagnosis::DiagnosisItem const* diagnosisItem)
{
  this->_d->_diagnosisItem=diagnosisItem;

  return;
}

model::diagnosis::DiagnosisItem const* DiagnosisGraphicEditor::diagnosisItem() const
{
  return this->_d->_diagnosisItem;
}


DiagnosisGraphicWidget* DiagnosisGraphicEditor::diagnosisGraphicWidget()
{
  DiagnosisGraphicWidget* diagnosisGraphicWidget = qobject_cast<DiagnosisGraphicWidget*>(this->m_widget);

  return diagnosisGraphicWidget;
}

QString DiagnosisGraphicEditor::fileName() const
{
  return this->_d->_diagnosisGraphicDocument->fileName();
}

} // namespace diagnosiseditor
