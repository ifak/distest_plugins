#include "testreportgraphiceditor.hpp"

#include "distesteditorconstants.hpp"
#include "testreportgraphicdocument.hpp"

#include <QFile>
#include <QString>
#include <QByteArray>
#include <QFileInfo>
#include <QQuickWidget>

#include <mobata/utils/functors.hpp>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor {

class TestReportGraphicEditor::Private
{
  friend class TestReportGraphicEditor;

  Private()
    : _testReportGraphicDocument(0)
  {}
  QString                    _displayName;
  TestReportGraphicDocument* _testReportGraphicDocument;
};

TestReportGraphicEditor::TestReportGraphicEditor(QQuickWidget* testReportGraphicWidget)
  : Core::IEditor(testReportGraphicWidget), _d(new Private)
{
  Q_ASSERT(testReportGraphicWidget);

  this->_d->_testReportGraphicDocument=new TestReportGraphicDocument(this);
  //  sutGraphicWidget->setScene(this->_d->_sutGraphicDocument->sutScene());
  this->setWidget(testReportGraphicWidget);
}

TestReportGraphicEditor::~TestReportGraphicEditor()
{
  delete this->_d->_testReportGraphicDocument;
  delete this->_d;
}

bool TestReportGraphicEditor::createNew(const QString &contents)
{
  Q_UNUSED(contents);

  return true;
}

bool TestReportGraphicEditor::open(QString* errorString,
                                   const QString& fileName,
                                   const QString& realFileName)
{
  bool result=this->_d->_testReportGraphicDocument->open(errorString,
                                                         fileName,
                                                         realFileName);

  if(!result)
     return false;

  QFileInfo fileInfo(fileName);
  if(!fileInfo.exists())
  {
    *errorString = QLatin1String("File not found!") + fileName;
    return false;
  }

  QQuickWidget* view = utils::simple_cast<QQuickWidget*>(this->m_widget.data());
  view->setSource(QUrl(QStringLiteral("qrc:/distesteditor/testreport/Testreport.qml")));

  this->_d->_displayName = fileInfo.fileName();

  return true;
}

Core::IDocument*  TestReportGraphicEditor::document()
{
  return this->_d->_testReportGraphicDocument;;
}

Core::Id TestReportGraphicEditor::id() const
{
  return Core::Id(Constants::TESTREPORTGRAPHIC_ID);
}

QString TestReportGraphicEditor::displayName() const
{
  return this->_d->_displayName;
}

void TestReportGraphicEditor::setDisplayName(const QString &title)
{
  this->_d->_displayName=title;
}

bool TestReportGraphicEditor::isTemporary() const
{
  return true;
}

QWidget* TestReportGraphicEditor::toolBar()
{
  return 0;
}

} // namespace distesteditor
