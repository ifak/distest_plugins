#include "testsystemgraphiceditor.hpp"

#include "testsystemeditorconstants.hpp"
#include "testsystemgraphicwidget.hpp"
#include "testsystemgraphicdocument.hpp"

#include <mobata/utils/functors.hpp>
#include <mobatawidgets/ts/testsystemscene.hpp>

#include <QToolBar>
#include <QFileInfo>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace testsystemeditor {

class TestSystemGraphicEditor::Private
{
  friend class TestSystemGraphicEditor;

  Private()
    : _testSystemItem(0),
      _testSystemGraphicDocument(0)
  {}

  model::ts::TestSystemItem const*  _testSystemItem;
  TestSystemGraphicDocument*        _testSystemGraphicDocument;
  QString                           _displayName;
};

TestSystemGraphicEditor::TestSystemGraphicEditor(TestSystemGraphicWidget* testSystemGraphicWidget)
  : dsleditor::DslGraphicEditor(Constants::TESTSYSTEMGRAPHIC_ID),
    _d(new Private)
{
  Q_ASSERT(testSystemGraphicWidget);

  this->_d->_testSystemGraphicDocument=new TestSystemGraphicDocument(this);
  testSystemGraphicWidget->setScene(this->_d->_testSystemGraphicDocument->testSystemScene());
  this->setWidget(testSystemGraphicWidget);
}

TestSystemGraphicEditor::~TestSystemGraphicEditor()
{
  delete this->_d;
}

bool TestSystemGraphicEditor::open(QString* errorString,
                                   const QString& fileName,
                                   const QString& realFileName)
{
  Q_UNUSED(errorString);
  Q_UNUSED(realFileName);

  bool result=this->_d->_testSystemGraphicDocument->open(errorString,
                                                         fileName,
                                                         realFileName);

  if(!result)
    return false;

  QFileInfo fileInfo(this->_d->_testSystemGraphicDocument->fileName());
  if(!fileInfo.exists())
    return false;

  this->setDisplayName(fileInfo.fileName());

  return true;
}

Core::IDocument*  TestSystemGraphicEditor::document()
{
  return this->_d->_testSystemGraphicDocument;
}

QWidget* TestSystemGraphicEditor::toolBar()
{
  return 0;
}

void TestSystemGraphicEditor::setTestSystemItem(model::ts::TestSystemItem const* testSystemItem)
{
  this->_d->_testSystemItem=testSystemItem;

  return;
}

model::ts::TestSystemItem const* TestSystemGraphicEditor::testSystemItem() const
{
  return this->_d->_testSystemItem;
}


TestSystemGraphicWidget* TestSystemGraphicEditor::testSystemGraphicWidget()
{
  return utils::simple_cast<TestSystemGraphicWidget*>(this->m_widget.data());
}

QString TestSystemGraphicEditor::fileName() const
{
  return this->_d->_testSystemGraphicDocument->fileName();
}

} // namespace testsystemeditor

