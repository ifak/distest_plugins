#include "testcasegraphiceditor.hpp"

#include "testcaseeditorconstants.hpp"
#include "testcasegraphicwidget.hpp"
#include "testcasegraphicdocument.hpp"

#include <coreplugin/editormanager/editormanager.h>

#include <QStandardItemModel>
#include <QToolBar>
#include <QFileInfo>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace testcaseeditor {

using namespace model::ts;

class TestCaseGraphicEditor::Private
{
  friend class TestCaseGraphicEditor;

  Private()
    : _outlineModel(0),
      _testCaseItem(0),
      _testCaseGraphicDocument(0)
  {}

  QStandardItemModel*         _outlineModel=nullptr;
  TestCaseItem const*         _testCaseItem;
  TestCaseDocument const*     _testCaseDocument = nullptr;
  TestCaseGraphicDocument*    _testCaseGraphicDocument=nullptr;
  QString                     _displayName;
  QSet<TestCaseEditor const*> _connectedTestCaseEditors;
};

TestCaseGraphicEditor::TestCaseGraphicEditor(TestCaseGraphicWidget* testCaseGraphicWidget)
  : dsleditor::DslGraphicEditor(Constants::TESTCASEGRAPHIC_ID),
    _d(new Private)
{
  Q_ASSERT(testCaseGraphicWidget);

  this->_d->_outlineModel = new QStandardItemModel(this);

  this->_d->_testCaseGraphicDocument=new TestCaseGraphicDocument(this);
  this->setWidget(testCaseGraphicWidget);
}

TestCaseGraphicEditor::~TestCaseGraphicEditor()
{
  delete this->_d;
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

  this->setDisplayName(fileInfo.fileName());

  return true;
}

Core::IDocument*  TestCaseGraphicEditor::document()
{
  return this->_d->_testCaseGraphicDocument;
}

QWidget* TestCaseGraphicEditor::toolBar()
{
  TestCaseGraphicWidget* testCaseGraphicWidget = qobject_cast<TestCaseGraphicWidget*>(this->widget());
  Q_ASSERT(testCaseGraphicWidget);

  return testCaseGraphicWidget->toolBar();
}

QStandardItemModel*TestCaseGraphicEditor::outlineModel() const
{
  return this->_d->_outlineModel;
}

void TestCaseGraphicEditor::setTestCaseItem(TestCaseItem const* testCaseItem)
{
  this->_d->_testCaseItem = testCaseItem;

  this->_d->_outlineModel->removeRows(0, this->_d->_outlineModel->rowCount());

  if(this->_d->_testCaseItem)
    this->_d->_outlineModel->appendRow(this->_d->_testCaseItem->clone());

  return;
}

TestCaseItem const* TestCaseGraphicEditor::testCaseItem() const
{
  return this->_d->_testCaseItem;
}

void TestCaseGraphicEditor::setTestCaseDocument(const TestCaseDocument* testCaseDocument)
{
  this->_d->_testCaseDocument = testCaseDocument;

  return;
}

TestCaseDocument const* TestCaseGraphicEditor::testCaseDocument() const
{
  return this->_d->_testCaseDocument;
}

TestCaseGraphicWidget* TestCaseGraphicEditor::testCaseGraphicWidget()
{
  TestCaseGraphicWidget* testCaseGraphicWidget = qobject_cast<TestCaseGraphicWidget*>(this->widget());
  Q_ASSERT(testCaseGraphicWidget);

  //testCaseGraphicWidget->setTestcaseGraphicEditor(this);

  return testCaseGraphicWidget;
}

QString TestCaseGraphicEditor::fileName() const
{
  return this->_d->_testCaseGraphicDocument->fileName();
}

} // namespace testcaseeditor
