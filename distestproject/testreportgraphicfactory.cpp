#include "testreportgraphicfactory.hpp"

#include "distestprojectconstants.hpp"
#include "testreportgraphiceditor.hpp"

#include <QDebug>
#include <QtQuickWidgets/QQuickWidget>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

TestReportGraphicFactory::TestReportGraphicFactory(QObject* parent)
  : Core::IEditorFactory(parent)
{
    qDebug()<< "TestReportGraphicFactory::TestReportGraphicFactory";
}

TestReportGraphicFactory::~TestReportGraphicFactory()
{}

Core::IEditor* TestReportGraphicFactory::createEditor(QWidget* parent)
{
  qDebug()<< "TestReportGraphicFactory::createEditor";
  return new TestReportGraphicEditor(new QQuickWidget(parent));
}

QStringList TestReportGraphicFactory::mimeTypes() const
{
  return QStringList()<< QLatin1String(Constants::TESTREPORTGRAPHIC_MIME_TYPE);
}

Core::Id TestReportGraphicFactory::id() const
{
  return Core::Id(Constants::TESTREPORTGRAPHIC_ID);
}

QString TestReportGraphicFactory::displayName() const
{
  return QLatin1String(Constants::TESTREPORTGRAPHIC_NAME);
}

} // namespace distestproject
