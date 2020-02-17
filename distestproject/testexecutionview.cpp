#include "testexecutionview.hpp"

#include "distestproject.hpp"
#include "distestprojectmodel.hpp"

#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/actionmanager/actionmanager.h>

#include <projectexplorer/projectexplorer.h>

#include <QApplication>
#include <QPainter>
#include <QHeaderView>
#include <QDebug>

namespace distestproject {

////
// TestExecutionView
////

TestExecutionView::TestExecutionView()
{
  using namespace ProjectExplorer;

  this->setWindowTitle(tr("Test Execution"));
  this->setWindowIcon(QIcon(QLatin1String(":/mobata/images/ts/testsuite.png")));
  this->setUniformRowHeights(true);
  this->header()->hide();
  this->expandAll();

  this->setSelectionMode(QAbstractItemView::SingleSelection);
//  this->setDragEnabled(true);
//  this->setAcceptDrops(true);
//  this->setDropIndicatorShown(true);

  //  setIndentation(0);
  //  setTextElideMode(Qt::ElideMiddle);
  //  setFrameStyle(QFrame::NoFrame);
  //  setAttribute(Qt::WA_MacShowFocusRect, false);
  //  setSelectionMode(QAbstractItemView::SingleSelection);
  //  setSelectionBehavior(QAbstractItemView::SelectRows);
  //  header()->setStretchLastSection(false);
  //  header()->setResizeMode(0, QHeaderView::Stretch);
  //  header()->setResizeMode(1, QHeaderView::Fixed);
  //  header()->resizeSection(1, 16);
  //  setContextMenuPolicy(Qt::CustomContextMenu);
  //  installEventFilter(this);
  //  viewport()->installEventFilter(this);

  //  this->currentProjectChanged(ProjectExplorerPlugin::currentProject());

  ProjectExplorerPlugin* pePlugin= ProjectExplorerPlugin::instance();
  Q_ASSERT(pePlugin);
  connect(pePlugin, &ProjectExplorerPlugin::currentProjectChanged,
          this, &TestExecutionView::currentProjectChanged);

  ProjectExplorer::Project* currentProject = pePlugin->currentProject();
  distestproject::DisTestProject* disTestProject = qobject_cast<distestproject::DisTestProject*>(currentProject);
  if(disTestProject)
    this->setModel(const_cast<distestproject::DisTestProjectModel*>(disTestProject->disTestProjectModel()));

  Core::EditorManager* em = Core::EditorManager::instance();
  connect(em, &Core::EditorManager::currentEditorChanged,
          this, &TestExecutionView::updateCurrentItem);
  connect(this, &TestExecutionView::pressed,
          this, &TestExecutionView::handlePressed);
  connect(this, &TestExecutionView::customContextMenuRequested,
          this, &TestExecutionView::contextMenuRequested);
}

TestExecutionView::~TestExecutionView()
{}

void TestExecutionView::currentProjectChanged(ProjectExplorer::Project* currentProject)
{
  qDebug()<<"TestExecutionView::currentProjectChanged() executed!";

  if(!currentProject)
    return;

  distestproject::DisTestProject* disTestProject = qobject_cast<distestproject::DisTestProject*>(currentProject);
  if(!disTestProject)
    return;

  //find and set model
  this->setModel(const_cast<distestproject::DisTestProjectModel*>(disTestProject->disTestProjectModel()));
  this->update();
  this->expandAll();

  QObject::connect(disTestProject, &distestproject::DisTestProject::projectContextUpdated,
                   this, &TestExecutionView::expandAll);

  return;
}

void TestExecutionView::updateCurrentItem(Core::IEditor *editor)
{
  qDebug()<<"TestExecutionView::updateCurrentItem() executed!";
  this->expandAll();
  if (!editor) {
    clearSelection();
    return;
  }

  //  //find project
  //  ProjectExplorer::Project* currentProject=distestproject::Helpers::projectForFile(editor->document()->fileName());
  //  if(!currentProject)
  //    return;



  //  Core::EditorManager *em = Core::EditorManager::instance();
  //  setCurrentIndex(em->openedEditorsModel()->indexOf(editor));
  //  selectionModel()->select(currentIndex(),
  //                           QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
  //  scrollTo(currentIndex());

  return;
}

bool TestExecutionView::eventFilter(QObject *obj, QEvent *event)
{
  if (obj == this
      && event->type() == QEvent::KeyPress
      && currentIndex().isValid())
  {
    QKeyEvent *ke = static_cast<QKeyEvent*>(event);
    if ((ke->key() == Qt::Key_Return
         || ke->key() == Qt::Key_Enter)
        && ke->modifiers() == 0)
    {
      activateEditor(currentIndex());
      return true;
    }
  }

  return false;
}

void TestExecutionView::handlePressed(const QModelIndex &index)
{
  QAbstractItemModel* model = this->model();
  QVariant data = model->data(index);
  qDebug()<<data;

  if (index.column() == 0)
    activateEditor(index);

  return;
}

void TestExecutionView::activateEditor(const QModelIndex& index)
{
  selectionModel()->select(index, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
  //  EditorManager::instance()->activateEditorForIndex(index);

  return;
}

void TestExecutionView::contextMenuRequested(QPoint pos)
{
  QMenu contextMenu;
  //  QModelIndex editorIndex = indexAt(pos);
  //  EditorManager::instance()->addSaveAndCloseEditorActions(&contextMenu, editorIndex);
  //  contextMenu.addSeparator();
  //  EditorManager::instance()->addNativeDirActions(&contextMenu, editorIndex);
  contextMenu.exec(mapToGlobal(pos));
}

///
// TestExecutionViewFactory
///

Core::NavigationView TestExecutionViewFactory::createWidget()
{
  Core::NavigationView n;
  n.widget = new TestExecutionView();
  return n;
}

QString TestExecutionViewFactory::displayName() const
{
  return TestExecutionView::tr("Test Execution");
}

int TestExecutionViewFactory::priority() const
{
  return 200;
}

Core::Id TestExecutionViewFactory::id() const
{
  return Core::Id("Test Execution");
}

QKeySequence TestExecutionViewFactory::activationSequence() const
{
  return QKeySequence(Core::UseMacShortcuts ? tr("Meta+T") : tr("Alt+T"));
}

TestExecutionViewFactory::TestExecutionViewFactory()
{}

TestExecutionViewFactory::~TestExecutionViewFactory()
{}

} // namespace smarttestproject
