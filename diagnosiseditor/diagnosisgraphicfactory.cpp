#include "diagnosisgraphicfactory.hpp"

#include "diagnosiseditorconstants.hpp"
#include "diagnosisgraphiceditor.hpp"
#include "diagnosisgraphicwidget.hpp"

#include <mobata/memory_leak_start.hpp>

namespace diagnosiseditor {

DiagnosisGraphicFactory::DiagnosisGraphicFactory(QObject* parent)
  : Core::IEditorFactory(parent)
{}

DiagnosisGraphicFactory::~DiagnosisGraphicFactory()
{}

Core::IEditor* DiagnosisGraphicFactory::createEditor(QWidget* parent)
{
  return new DiagnosisGraphicEditor(new DiagnosisGraphicWidget(parent));
}

QStringList DiagnosisGraphicFactory::mimeTypes() const
{
  return QStringList()<< QLatin1String(Constants::DIAGNOSISGRAPHIC_MIME_TYPE);
}

Core::Id DiagnosisGraphicFactory::id() const
{
  return Core::Id(Constants::DIAGNOSISGRAPHIC_ID);
}

QString DiagnosisGraphicFactory::displayName() const
{
  return QLatin1String(Constants::DIAGNOSISGRAPHIC_NAME);
}

} // namespace diagnosiseditor

