#include "testcasegraphicdocument.hpp"

#include "testcaseeditorconstants.hpp"

#include <mobatawidgets/ts/testcasescene.hpp>

#include <utils/qtcassert.h>

#include <mobata/memory_leak_start.hpp>

namespace testcaseeditor {

class TestCaseGraphicDocument::Private
{
  friend class TestCaseGraphicDocument;

  QString                   _fileName;

  Private()
  {}
};

TestCaseGraphicDocument::TestCaseGraphicDocument(QObject* parent)
  : Core::IDocument(parent),
    _d(new Private)
{}

TestCaseGraphicDocument::~TestCaseGraphicDocument()
{
  delete this->_d;
}

bool TestCaseGraphicDocument::open(QString* errorString,
                                   const QString& fileName,
                                   const QString& realFileName)
{
  Q_UNUSED(realFileName);
  QTC_ASSERT(errorString, return false);

  this->_d->_fileName=fileName;

  return true;
}

bool TestCaseGraphicDocument::save(QString *errorString,
                                   const QString &fileName,
                                   bool autoSave)
{
  Q_UNUSED(errorString);
  Q_UNUSED(autoSave);

  this->_d->_fileName=fileName;

  return true;
}

QString TestCaseGraphicDocument::fileName() const
{
  return this->_d->_fileName;
}

bool TestCaseGraphicDocument::isFileReadOnly() const
{
  return true;
}

QString TestCaseGraphicDocument::defaultPath() const
{
  return QStringLiteral("");
}

QString TestCaseGraphicDocument::suggestedFileName() const
{
  return QStringLiteral("");
}

QString TestCaseGraphicDocument::mimeType() const
{
  return QLatin1String(Constants::TESTCASEGRAPHIC_MIME_TYPE);
}

bool TestCaseGraphicDocument::shouldAutoSave() const
{
  return false;
}

bool TestCaseGraphicDocument::isModified() const
{
  return false;
}

bool TestCaseGraphicDocument::isSaveAsAllowed() const
{
  return false;
}

bool TestCaseGraphicDocument::reload(QString *errorString,
                                     ReloadFlag flag,
                                     ChangeType type)
{
  Q_UNUSED(errorString);
  Q_UNUSED(flag);
  Q_UNUSED(type);

  return true;
}

void TestCaseGraphicDocument::rename(const QString &newName)
{
  Q_UNUSED(newName);

  return;
}

} // namespace testcaseeditor

