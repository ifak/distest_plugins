#include "testcasegraphicfactory.hpp"

#include "testcaseeditorconstants.hpp"
#include "testcasegraphiceditor.hpp"
#include "testcasegraphicwidget.hpp"
#include "testcaseeditorplugin.hpp"

#include <mobata/memory_leak_start.hpp>

namespace testcaseeditor {

TestCaseGraphicFactory::TestCaseGraphicFactory(QObject* parent)
  : Core::IEditorFactory(parent)
{}

TestCaseGraphicFactory::~TestCaseGraphicFactory()
{}

Core::IEditor* TestCaseGraphicFactory::createEditor(QWidget* parent)
{
  TestCaseGraphicWidget* testCaseGraphicWidget = new TestCaseGraphicWidget(parent);
  TestCaseEditorPlugin::instance()->initializeGraphicEditor(testCaseGraphicWidget);
  connect(this, &TestCaseGraphicFactory::refreshGraphicOut,
          testCaseGraphicWidget, &TestCaseGraphicWidget::updateTestCaseGraphic);

  return testCaseGraphicWidget->testCaseGraphicEditor();
}

QStringList TestCaseGraphicFactory::mimeTypes() const
{
  return QStringList()<< QLatin1String(Constants::TESTCASEGRAPHIC_MIME_TYPE);
}

Core::Id TestCaseGraphicFactory::id() const
{
  return Core::Id(Constants::TESTCASEGRAPHIC_ID);
}

QString TestCaseGraphicFactory::displayName() const
{
  return QLatin1String(Constants::TESTCASEGRAPHIC_NAME);
}
void TestCaseGraphicFactory::refreshGraphicIn(){
    emit this->refreshGraphicOut();
}
} // namespace testcaseeditor

