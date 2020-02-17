#include "testreportgraphicdocument.hpp"

#include "distestprojectconstants.hpp"

#include <utils/qtcassert.h>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

class TestReportGraphicDocument::Private
{
  friend class TestReportGraphicDocument;

  QString             _fileName;

  Private()
  {}
};

TestReportGraphicDocument::TestReportGraphicDocument(QObject* parent)
  : Core::IDocument(parent),
    _d(new Private())
{
}

TestReportGraphicDocument::~TestReportGraphicDocument()
{
  delete this->_d;
}

bool TestReportGraphicDocument::open(QString* errorString,
                              const QString& fileName,
                              const QString& realFileName)
{
  Q_UNUSED(realFileName);
  QTC_ASSERT(errorString, return false);

  this->_d->_fileName=fileName;

  return true;
}

bool TestReportGraphicDocument::save(QString *errorString,
                              const QString &fileName,
                              bool autoSave)
{
  Q_UNUSED(errorString);
  Q_UNUSED(autoSave);

  this->_d->_fileName=fileName;

  return true;
}

QString TestReportGraphicDocument::fileName() const
{
  return this->_d->_fileName;
}

bool TestReportGraphicDocument::isFileReadOnly() const
{
  return true;
}

QString TestReportGraphicDocument::defaultPath() const
{
  return QStringLiteral("");
}

QString TestReportGraphicDocument::suggestedFileName() const
{
  return QStringLiteral("");
}

QString TestReportGraphicDocument::mimeType() const
{
  return QLatin1String(Constants::TESTREPORTGRAPHIC_MIME_TYPE);
}

bool TestReportGraphicDocument::shouldAutoSave() const
{
  return false;
}

bool TestReportGraphicDocument::isModified() const
{
  return false;
}

bool TestReportGraphicDocument::isSaveAsAllowed() const
{
  return false;
}

bool TestReportGraphicDocument::reload(QString *errorString,
                                ReloadFlag flag,
                                ChangeType type)
{
  Q_UNUSED(errorString);
  Q_UNUSED(flag);
  Q_UNUSED(type);

  return true;
}

void TestReportGraphicDocument::rename(const QString &newName)
{
  Q_UNUSED(newName);

  return;
}

} // namespace distestproject

