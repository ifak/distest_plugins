#include "testsystemgraphicdocument.hpp"

#include "distesteditorconstants.hpp"

#include <mobatawidgets/ts/testsystemscene.hpp>

#include <utils/qtcassert.h>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor {

class TestSystemGraphicDocument::Private
{
  friend class TestSystemGraphicDocument;

  view::ts::TestSystemScene*  _testSystemScene;
  QString                     _fileName;

  Private()
    : _testSystemScene(0)
  {}
};

TestSystemGraphicDocument::TestSystemGraphicDocument(QObject* parent)
  : Core::IDocument(parent),
    _d(new Private)
{
  this->_d->_testSystemScene=new view::ts::TestSystemScene(this);
}

TestSystemGraphicDocument::~TestSystemGraphicDocument()
{
  delete this->_d;
}

view::ts::TestSystemScene* TestSystemGraphicDocument::testSystemScene()
{
  return this->_d->_testSystemScene;
}

bool TestSystemGraphicDocument::open(QString* errorString,
                                     const QString& fileName,
                                     const QString& realFileName)
{
  Q_UNUSED(realFileName);
  QTC_ASSERT(errorString, return false);

  this->_d->_fileName=fileName;

  return true;
}

bool TestSystemGraphicDocument::save(QString *errorString,
                                     const QString &fileName,
                                     bool autoSave)
{
  Q_UNUSED(errorString);
  Q_UNUSED(autoSave);

  this->_d->_fileName=fileName;

  return true;
}

QString TestSystemGraphicDocument::fileName() const
{
  return this->_d->_fileName;
}

bool TestSystemGraphicDocument::isFileReadOnly() const
{
  return true;
}

QString TestSystemGraphicDocument::defaultPath() const
{
  return QStringLiteral("");
}

QString TestSystemGraphicDocument::suggestedFileName() const
{
  return QStringLiteral("");
}

QString TestSystemGraphicDocument::mimeType() const
{
  return QLatin1String(Constants::TESTSYSTEMGRAPHIC_MIME_TYPE);
}

bool TestSystemGraphicDocument::shouldAutoSave() const
{
  return false;
}

bool TestSystemGraphicDocument::isModified() const
{
  return false;
}

bool TestSystemGraphicDocument::isSaveAsAllowed() const
{
  return false;
}

bool TestSystemGraphicDocument::reload(QString *errorString,
                                       ReloadFlag flag,
                                       ChangeType type)
{
  Q_UNUSED(errorString);
  Q_UNUSED(flag);
  Q_UNUSED(type);

  return true;
}

void TestSystemGraphicDocument::rename(const QString &newName)
{
  Q_UNUSED(newName);

  return;
}
} // namespace distesteditor

