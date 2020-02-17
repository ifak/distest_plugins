#include "testsystemeditorfactory.hpp"
#include "distesteditorconstants.hpp"
#include "distesteditorplugin.hpp"
#include "testsystemeditor.hpp"
#include "testsystemeditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{
namespace Internal{

class TestSystemEditorFactory::Private
{
  friend class TestSystemEditorFactory;

  Private(DisTestEditorPlugin*	disTestPlugin)
    :	_disTestPlugin(disTestPlugin),
      _id(Constants::TESTSYSTEMEDITOR_ID)
  {
    this->_mimeTypes<<QLatin1String(Constants::TESTSYSTEM_MIME_TYPE);
  }

public:
  ~Private()
  {}

private:
  DisTestEditorPlugin*  _disTestPlugin;
  Core::Id              _id;
  QStringList           _mimeTypes;
};

TestSystemEditorFactory::TestSystemEditorFactory(DisTestEditorPlugin *owner)
  :Core::IEditorFactory(owner), _d(new Private(owner))
{
  Q_ASSERT(this->_d->_disTestPlugin);
}

TestSystemEditorFactory::~TestSystemEditorFactory()
{}

QStringList TestSystemEditorFactory::mimeTypes() const
{
  return this->_d->_mimeTypes;
}

Core::Id TestSystemEditorFactory::id() const
{
  return this->_d->_id;
}

QString TestSystemEditorFactory::displayName() const
{
  return QLatin1String(Constants::TESTSYSTEMEDITOR_NAME);
}

Core::IEditor* TestSystemEditorFactory::createEditor(QWidget *parent)
{
  TestSystemEditorWidget* editorWidget = new TestSystemEditorWidget(parent);
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //namespace Internal
} //end namespace distesteditor
