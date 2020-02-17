#include "testcaseeditorfactory.hpp"
#include "distesteditorconstants.hpp"
#include "distesteditorplugin.hpp"
#include "testcaseeditor.hpp"
#include "testcaseeditorwidget.hpp"

#include <coreplugin/id.h>
#include <texteditor/texteditorsettings.h>

#include <QStringList>
#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distesteditor{
namespace Internal{

class TestCaseEditorFactory::Private
{
  friend class TestCaseEditorFactory;

  Private(DisTestEditorPlugin*	disTestPlugin)
    :	_disTestPlugin(disTestPlugin),
      _id(Constants::TESTCASEEDITOR_ID)
  {
    this->_mimeTypes<<QLatin1String(Constants::TESTCASE_MIME_TYPE);
  }

public:
  ~Private()
  {}

private:
  DisTestEditorPlugin*  _disTestPlugin;
  Core::Id              _id;
  QStringList           _mimeTypes;
};

TestCaseEditorFactory::TestCaseEditorFactory(DisTestEditorPlugin *owner)
  :Core::IEditorFactory(owner), _d(new Private(owner))
{
  Q_ASSERT(this->_d->_disTestPlugin);
}

TestCaseEditorFactory::~TestCaseEditorFactory()
{}

QStringList TestCaseEditorFactory::mimeTypes() const
{
  return this->_d->_mimeTypes;
}

Core::Id TestCaseEditorFactory::id() const
{
  return this->_d->_id;
}

QString TestCaseEditorFactory::displayName() const
{
  return QLatin1String(Constants::TESTCASEEDITOR_NAME);
}

Core::IEditor* TestCaseEditorFactory::createEditor(QWidget *parent)
{
  TestCaseEditorWidget* editorWidget = new TestCaseEditorWidget(parent);
  TextEditor::TextEditorSettings::instance()->initializeEditor(editorWidget);

  return editorWidget->editor();
}

} //namespace Internal
} //end namespace distesteditor
