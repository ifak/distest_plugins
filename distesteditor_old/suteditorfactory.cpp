#include "suteditorfactory.hpp"
#include "distesteditorconstants.hpp"
#include "distesteditorplugin.hpp"
#include "suteditor.hpp"
#include "suteditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{
namespace Internal{

class SutEditorFactory::Private
{
  friend class SutEditorFactory;

  Private(DisTestEditorPlugin*	disTestPlugin)
    :	_disTestPlugin(disTestPlugin),
      _id(Constants::SUTEDITOR_ID)
  {
    this->_mimeTypes<<QLatin1String(Constants::SUT_MIME_TYPE);
  }

public:
  ~Private()
  {}

private:
  DisTestEditorPlugin*  _disTestPlugin;
  Core::Id              _id;
  QStringList           _mimeTypes;
};

SutEditorFactory::SutEditorFactory(DisTestEditorPlugin *owner)
  :Core::IEditorFactory(owner), _d(new Private(owner))
{
  Q_ASSERT(this->_d->_disTestPlugin);
}

SutEditorFactory::~SutEditorFactory()
{}

QStringList SutEditorFactory::mimeTypes() const
{
  return this->_d->_mimeTypes;
}

Core::Id SutEditorFactory::id() const
{
  return this->_d->_id;
}

QString SutEditorFactory::displayName() const
{
  return QLatin1String(Constants::SUTEDITOR_NAME);
}

Core::IEditor* SutEditorFactory::createEditor(QWidget *parent)
{
  qDebug()<<"SutEditorFactory::createEditor() with parent:"<<parent<<" executed";

  SutEditorWidget* editorWidget = new SutEditorWidget(parent);
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //namespace Internal
} //end namespace distesteditor
