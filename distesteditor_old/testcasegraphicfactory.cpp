#include "testcasegraphicfactory.hpp"

#include "distesteditorconstants.hpp"
#include "testcasegraphiceditor.hpp"
#include "testcasegraphicwidget.hpp"

#include <mobata/memory_leak_start.hpp>

namespace distesteditor {

TestCaseGraphicFactory::TestCaseGraphicFactory(QObject* parent)
  : Core::IEditorFactory(parent)
{}

TestCaseGraphicFactory::~TestCaseGraphicFactory()
{}

Core::IEditor* TestCaseGraphicFactory::createEditor(QWidget* parent)
{
  return new TestCaseGraphicEditor(new TestCaseGraphicWidget(parent));
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

} // namespace distesteditor

