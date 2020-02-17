#include "sutgraphicfactory.hpp"

#include "distesteditorconstants.hpp"
#include "sutgraphiceditor.hpp"
#include "sutgraphicwidget.hpp"

#include <mobata/memory_leak_start.hpp>

namespace distesteditor {

SutGraphicFactory::SutGraphicFactory(QObject* parent)
  : Core::IEditorFactory(parent)
{}

SutGraphicFactory::~SutGraphicFactory()
{}

Core::IEditor* SutGraphicFactory::createEditor(QWidget* parent)
{
  return new SutGraphicEditor(new SutGraphicWidget(parent));
}

QStringList SutGraphicFactory::mimeTypes() const
{
  return QStringList()<< QLatin1String(Constants::SUTGRAPHIC_MIME_TYPE);
}

Core::Id SutGraphicFactory::id() const
{
  return Core::Id(Constants::SUTGRAPHIC_ID);
}

QString SutGraphicFactory::displayName() const
{
  return QLatin1String(Constants::SUTGRAPHIC_NAME);
}

} // namespace distesteditor

