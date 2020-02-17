#include "testsuiteeditorfactory.hpp"
#include "distesteditorconstants.hpp"
#include "distesteditorplugin.hpp"
#include "testsuiteeditor.hpp"
#include "testsuiteeditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{
namespace Internal{

class TestSuiteEditorFactory::Private
{
  friend class TestSuiteEditorFactory;

  Private(DisTestEditorPlugin*	disTestPlugin)
    :	_disTestPlugin(disTestPlugin),
      _id(Constants::TESTCASEEDITOR_ID)
  {
    this->_mimeTypes<<QLatin1String(Constants::TESTSUITE_MIME_TYPE);
  }

public:
  ~Private()
  {}

private:
  DisTestEditorPlugin*  _disTestPlugin;
  Core::Id              _id;
  QStringList           _mimeTypes;
};

TestSuiteEditorFactory::TestSuiteEditorFactory(DisTestEditorPlugin *owner)
  :Core::IEditorFactory(owner), _d(new Private(owner))
{
  Q_ASSERT(this->_d->_disTestPlugin);
}

TestSuiteEditorFactory::~TestSuiteEditorFactory()
{}

QStringList TestSuiteEditorFactory::mimeTypes() const
{
  return this->_d->_mimeTypes;
}

Core::Id TestSuiteEditorFactory::id() const
{
  return this->_d->_id;
}

QString TestSuiteEditorFactory::displayName() const
{
  return QLatin1String(Constants::TESTCASEEDITOR_NAME);
}

Core::IEditor* TestSuiteEditorFactory::createEditor(QWidget *parent)
{
  TestSuiteEditorWidget* editorWidget = new TestSuiteEditorWidget(parent);
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //namespace Internal
} //end namespace distesteditor
