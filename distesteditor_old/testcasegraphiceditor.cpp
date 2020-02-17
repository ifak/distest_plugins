#include "testcasegraphiceditor.hpp"

#include "distesteditorconstants.hpp"
#include "testcasegraphicwidget.hpp"
#include "testcasegraphicdocument.hpp"

#include <mobatawidgets/ts/testcasescene.hpp>

#include <QToolBar>
#include <QFileInfo>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor {

class TestCaseGraphicEditor::Private
{
  friend class TestCaseGraphicEditor;

  Private()
    : _testCaseItem(0),
      _testCaseGraphicDocument(0)
  {}

  model::ts::TestCaseItem const*  _testCaseItem;
  TestCaseGraphicDocument*        _testCaseGraphicDocument;
  QString                         _displayName;
};

TestCaseGraphicEditor::TestCaseGraphicEditor(TestCaseGraphicWidget* testCaseGraphicWidget)
  : Core::IEditor(testCaseGraphicWidget), _d(new Private)
{
  Q_ASSERT(testCaseGraphicWidget);

  this->_d->_testCaseGraphicDocument=new TestCaseGraphicDocument(this);
  testCaseGraphicWidget->setScene(this->_d->_testCaseGraphicDocument->testCaseScene());
  this->setWidget(testCaseGraphicWidget);
}

TestCaseGraphicEditor::~TestCaseGraphicEditor()
{
  delete this->_d;
}

bool TestCaseGraphicEditor::createNew(const QString &contents)
{
  Q_UNUSED(contents);

  return true;
}

bool TestCaseGraphicEditor::open(QString* errorString,
                                 const QString& fileName,
                                 const QString& realFileName)
{
  Q_UNUSED(errorString);
  Q_UNUSED(realFileName);

  bool result=this->_d->_testCaseGraphicDocument->open(errorString,
                                                       fileName,
                                                       realFileName);

  if(!result)
     return false;

  QFileInfo fileInfo(this->_d->_testCaseGraphicDocument->fileName());
  if(!fileInfo.exists())
    return false;

  this->_d->_displayName = fileInfo.fileName();

  return true;
}

Core::IDocument*  TestCaseGraphicEditor::document()
{
  return this->_d->_testCaseGraphicDocument;
}

Core::Id TestCaseGraphicEditor::id() const
{
  return Core::Id(Constants::TESTCASEGRAPHIC_ID);
}

QString TestCaseGraphicEditor::displayName() const
{
  return this->_d->_displayName;
}

void TestCaseGraphicEditor::setDisplayName(const QString &title)
{
  this->_d->_displayName=title;
}

bool TestCaseGraphicEditor::isTemporary() const
{
  return true;
}

QWidget* TestCaseGraphicEditor::toolBar()
{
  return 0;
}

void TestCaseGraphicEditor::setTestCaseItem(model::ts::TestCaseItem const* testCaseItem)
{
  this->_d->_testCaseItem=testCaseItem;

  return;
}

model::ts::TestCaseItem const* TestCaseGraphicEditor::testCaseItem() const
{
  return this->_d->_testCaseItem;
}


TestCaseGraphicWidget* TestCaseGraphicEditor::widget()
{
  return utils::simple_cast<TestCaseGraphicWidget*>(this->m_widget.data());
}

QString TestCaseGraphicEditor::fileName() const
{
  return this->_d->_testCaseGraphicDocument->fileName();
}

} // namespace distesteditor
