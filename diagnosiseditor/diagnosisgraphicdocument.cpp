#include "diagnosisgraphicdocument.hpp"

#include "diagnosiseditorconstants.hpp"

//#include <mobatawidgediagnosis/diagnosis/diagnosisscene.hpp>

#include <utils/qtcassert.h>

#include <mobata/memory_leak_start.hpp>

namespace diagnosiseditor {

class DiagnosisGraphicDocument::Private
{
  friend class DiagnosisGraphicDocument;

//  view::diagnosis::DiagnosisScene*  _diagnosisScene;
  QString                   _fileName;

  Private()
//    : _diagnosisScene(0)
  {}
};

DiagnosisGraphicDocument::DiagnosisGraphicDocument(QObject* parent)
  : Core::IDocument(parent),
    _d(new Private)
{
//  this->_d->_diagnosisScene=new view::diagnosis::DiagnosisScene(this);
}

DiagnosisGraphicDocument::~DiagnosisGraphicDocument()
{
  delete this->_d;
}
/*
view::diagnosis::DiagnosisScene* DiagnosisGraphicDocument::diagnosisScene()
{
  return this->_d->_diagnosisScene;
}*/

bool DiagnosisGraphicDocument::open(QString* errorString,
                                   const QString& fileName,
                                   const QString& realFileName)
{
  Q_UNUSED(realFileName);
  QTC_ASSERT(errorString, return false);

  this->_d->_fileName=fileName;

  return true;
}

bool DiagnosisGraphicDocument::save(QString *errorString,
                                   const QString &fileName,
                                   bool autoSave)
{
  Q_UNUSED(errorString);
  Q_UNUSED(autoSave);

  this->_d->_fileName=fileName;

  return true;
}

QString DiagnosisGraphicDocument::fileName() const
{
  return this->_d->_fileName;
}

bool DiagnosisGraphicDocument::isFileReadOnly() const
{
  return true;
}

QString DiagnosisGraphicDocument::defaultPath() const
{
  return QStringLiteral("");
}

QString DiagnosisGraphicDocument::suggestedFileName() const
{
  return QStringLiteral("");
}

QString DiagnosisGraphicDocument::mimeType() const
{
  return QLatin1String(Constants::DIAGNOSISGRAPHIC_MIME_TYPE);
}

bool DiagnosisGraphicDocument::shouldAutoSave() const
{
  return false;
}

bool DiagnosisGraphicDocument::isModified() const
{
  return false;
}

bool DiagnosisGraphicDocument::isSaveAsAllowed() const
{
  return false;
}

bool DiagnosisGraphicDocument::reload(QString *errorString,
                                     ReloadFlag flag,
                                     ChangeType type)
{
  Q_UNUSED(errorString);
  Q_UNUSED(flag);
  Q_UNUSED(type);

  return true;
}

void DiagnosisGraphicDocument::rename(const QString &newName)
{
  Q_UNUSED(newName);

  return;
}

} // namespace diagnosiseditor

