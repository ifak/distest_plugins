#include "sutgraphicdocument.hpp"

#include "suteditorconstants.hpp"

#include <mobatawidgets/ts/sutscene.hpp>

#include <utils/qtcassert.h>

#include <mobata/memory_leak_start.hpp>

namespace suteditor {

class SutGraphicDocument::Private
{
  friend class SutGraphicDocument;

  view::ts::SutScene* _sutScene;
  QString             _fileName;

  Private()
    : _sutScene(0)
  {}
};

SutGraphicDocument::SutGraphicDocument(QObject* parent)
  : Core::IDocument(parent),
    _d(new Private)
{
  this->_d->_sutScene=new view::ts::SutScene(this);
}

SutGraphicDocument::~SutGraphicDocument()
{
  delete this->_d;
}

view::ts::SutScene* SutGraphicDocument::sutScene()
{
  return this->_d->_sutScene;
}

bool SutGraphicDocument::open(QString* errorString,
                              const QString& fileName,
                              const QString& realFileName)
{
  Q_UNUSED(realFileName);
  QTC_ASSERT(errorString, return false);

  this->_d->_fileName=fileName;

  return true;
}

bool SutGraphicDocument::save(QString *errorString,
                              const QString &fileName,
                              bool autoSave)
{
  Q_UNUSED(errorString);
  Q_UNUSED(autoSave);

  this->_d->_fileName=fileName;

  return true;
}

QString SutGraphicDocument::fileName() const
{
  return this->_d->_fileName;
}

bool SutGraphicDocument::isFileReadOnly() const
{
  return true;
}

QString SutGraphicDocument::defaultPath() const
{
  return QStringLiteral("");
}

QString SutGraphicDocument::suggestedFileName() const
{
  return QStringLiteral("");
}

QString SutGraphicDocument::mimeType() const
{
  return QLatin1String(Constants::SUTGRAPHIC_MIME_TYPE);
}

bool SutGraphicDocument::shouldAutoSave() const
{
  return false;
}

bool SutGraphicDocument::isModified() const
{
  return false;
}

bool SutGraphicDocument::isSaveAsAllowed() const
{
  return false;
}

bool SutGraphicDocument::reload(QString *errorString,
                                ReloadFlag flag,
                                ChangeType type)
{
  Q_UNUSED(errorString);
  Q_UNUSED(flag);
  Q_UNUSED(type);

  return true;
}

void SutGraphicDocument::rename(const QString &newName)
{
  Q_UNUSED(newName);

  return;
}

} // namespace suteditor

