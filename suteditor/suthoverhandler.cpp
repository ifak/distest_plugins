#include "suthoverhandler.hpp"

#include "suteditor.hpp"
#include "suteditorwidget.hpp"

#include <mobata/memory_leak_start.hpp>

using namespace Core;

namespace suteditor {

SutHoverHandler::SutHoverHandler(QObject* parent)
  : BaseHoverHandler(parent)
{}

SutHoverHandler::~SutHoverHandler()
{}

bool SutHoverHandler::acceptEditor(IEditor* editor)
{
  if (qobject_cast<SutEditor*>(editor))
    return true;
  return false;
}

void SutHoverHandler::identifyMatch(TextEditor::ITextEditor* editor, int pos)
{
  if (SutEditorWidget* sutEditorWidget = qobject_cast<SutEditorWidget *>(editor->widget()))
  {
    if (! sutEditorWidget->extraSelectionTooltip(pos).isEmpty())
      this->setToolTip(sutEditorWidget->extraSelectionTooltip(pos));
  }
}

void SutHoverHandler::decorateToolTip()
{
  if (Qt::mightBeRichText(toolTip()))
    this->setToolTip(Qt::escape(toolTip()));
}

} // namespace suteditor
