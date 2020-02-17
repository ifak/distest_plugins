#include "decleditorfactory.hpp"
#include "distesteditorconstants.hpp"
#include "distesteditorplugin.hpp"
#include "decleditor.hpp"
#include "decleditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{
namespace Internal{

class DeclEditorFactory::Private
{
  friend class DeclEditorFactory;

  Private(DisTestEditorPlugin*	disTestPlugin)
    :	_disTestPlugin(disTestPlugin),
      _id(Constants::DECLEDITOR_ID)
  {
    this->_mimeTypes<<QLatin1String(Constants::DECL_MIME_TYPE);
  }

public:
  ~Private()
  {}

private:
  DisTestEditorPlugin*	_disTestPlugin;
  Core::Id		_id;
  QStringList	_mimeTypes;
};

DeclEditorFactory::DeclEditorFactory(DisTestEditorPlugin *owner)
  :Core::IEditorFactory(owner), _d(new Private(owner))
{
  Q_ASSERT(this->_d->_disTestPlugin);
}

DeclEditorFactory::~DeclEditorFactory()
{}

QStringList DeclEditorFactory::mimeTypes() const
{
  return this->_d->_mimeTypes;
}

Core::Id DeclEditorFactory::id() const
{
  return this->_d->_id;
}

QString DeclEditorFactory::displayName() const
{
  return QLatin1String(Constants::DECLEDITOR_NAME);
}

Core::IEditor *DeclEditorFactory::createEditor(QWidget *parent)
{
  DeclEditorWidget* editorWidget = new DeclEditorWidget(parent);
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //namespace Internal
} //end namespace distesteditor
