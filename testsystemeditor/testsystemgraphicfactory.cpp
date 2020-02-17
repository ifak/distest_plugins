#include "testsystemgraphicfactory.hpp"

#include "testsystemeditorconstants.hpp"
#include "testsystemgraphiceditor.hpp"
#include "testsystemgraphicwidget.hpp"

#include <mobata/memory_leak_start.hpp>

namespace testsystemeditor {

TestSystemGraphicFactory::TestSystemGraphicFactory(QObject* parent)
  : Core::IEditorFactory(parent)
{}

TestSystemGraphicFactory::~TestSystemGraphicFactory()
{}

Core::IEditor* TestSystemGraphicFactory::createEditor(QWidget* parent)
{
  return new TestSystemGraphicEditor(new TestSystemGraphicWidget(parent));
}

QStringList TestSystemGraphicFactory::mimeTypes() const
{
  return QStringList()<< QLatin1String(Constants::TESTSYSTEMGRAPHIC_MIME_TYPE);
}

Core::Id TestSystemGraphicFactory::id() const
{
  return Core::Id(Constants::TESTSYSTEMGRAPHIC_ID);
}

QString TestSystemGraphicFactory::displayName() const
{
  return QLatin1String(Constants::TESTSYSTEMGRAPHIC_NAME);
}

} // namespace testsystemeditor

