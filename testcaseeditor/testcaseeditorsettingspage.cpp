#include "testcaseeditorsettingspage.hpp"

#include "testcaseeditorconstants.hpp"

namespace testcaseeditor {
namespace Internal {

class TestcaseEditorSettingsWidget::Private
{
  friend class TestcaseEditorSettingsWidget;
};

TestcaseEditorSettingsWidget::TestcaseEditorSettingsWidget(QWidget *parent)
  : QWidget(parent), _d(new Private())
{}

TestcaseEditorSettingsWidget::~TestcaseEditorSettingsWidget()
{
  delete _d;
}

// ------------------ TestcaseEditorSettingsPage
TestcaseEditorSettingsPage::TestcaseEditorSettingsPage()
{
  this->setId(Constants::TESTCASE_SETTINGS_ID);
  this->setDisplayName(tr("Testcase Editor"));
  this->setCategory(Constants::TESTCASE_SETTINGS_CATEGORY);
  this->setDisplayCategory(tr(Constants::TESTCASE_SETTINGS_TR_CATEGORY));
  this->setCategoryIcon(QLatin1String(Constants::TESTCASE_SETTINGS_CATEGORY_ICON));
}

TestcaseEditorSettingsPage::~TestcaseEditorSettingsPage()
{
  // Do nothing
}

QWidget* TestcaseEditorSettingsPage::createPage(QWidget *parent)
{
  this->_widget = new TestcaseEditorSettingsWidget(parent);

  return this->_widget;
}

void TestcaseEditorSettingsPage::apply()
{

  return;
}

void TestcaseEditorSettingsPage::finish()
{
  // Do nothing

  return;
}

bool TestcaseEditorSettingsPage::matches(const QString& s) const
{
  return this->_searchKeywords.contains(s, Qt::CaseInsensitive);
}

}// end namespace Internal
}//end namespace testcaseeditor


