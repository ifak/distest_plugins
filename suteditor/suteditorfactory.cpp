#include "suteditorfactory.hpp"
#include "suteditorconstants.hpp"
#include "suteditorplugin.hpp"
#include "suteditor.hpp"
#include "suteditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

using namespace TextEditor;

namespace suteditor{
namespace Internal{

class SutEditorFactory::Private
{
  friend class SutEditorFactory;

  Private(SutEditorPlugin*	sutEditorPlugin)
    :	_sutEditorPlugin(sutEditorPlugin),
      _id(Constants::SUTEDITOR_ID)
  {
    this->_mimeTypes<<QLatin1String(Constants::SUT_MIME_TYPE);
  }

public:
  ~Private()
  {}

private:
  SutEditorPlugin*  _sutEditorPlugin;
  Core::Id          _id;
  QStringList       _mimeTypes;
};

SutEditorFactory::SutEditorFactory(SutEditorPlugin* owner)
  :Core::IEditorFactory(owner),
    _d(new Private(owner))
{
  Q_ASSERT(this->_d->_sutEditorPlugin);
}

SutEditorFactory::~SutEditorFactory()
{
  delete this->_d;
}

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
  SutEditorWidget* editorWidget = new SutEditorWidget(parent);
  SutEditorPlugin::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //namespace Internal
} //end namespace suteditor
