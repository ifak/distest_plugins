/*
 * This file is part of distest_plugins.
 *
 * distest_plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * distest_plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with distest_plugins.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DISTESTPROJECT_DISTESTCASEWIZARD_HPP
#define DISTESTPROJECT_DISTESTCASEWIZARD_HPP

#include <coreplugin/basefilewizard.h>
#include <utils/filewizarddialog.h>

#include <QWizardPage>

namespace ProjectExplorer{
class Node;
class Project;
}


namespace distestproject {
namespace Internal {

class DisTestCaseWizardDialog : public Utils::FileWizardDialog
{
  Q_OBJECT
public:
  explicit DisTestCaseWizardDialog(QWidget *parent = 0);

  QString title() const    { return QStringLiteral("DisTest Test Case"); }
};


class DisTestCaseWizard : public Core::BaseFileWizard
{
  Q_OBJECT

public:
  explicit DisTestCaseWizard(const Core::BaseFileWizardParameters &parameters,
                                 QObject *parent = 0);

public:
  void setContextNode(ProjectExplorer::Node* node);
  void setContextProject(ProjectExplorer::Project* project);

protected:
  virtual QWizard*              createWizardDialog(QWidget *parent,
                                                   const Core::WizardDialogParameters &wizardDialogParameters) const;
  virtual Core::GeneratedFiles  generateFiles(const QWizard *wizard,
                                              QString* errorString) const;
  virtual bool                  postGenerateFiles(QWizard const* wizard,
                                                  const Core::GeneratedFiles& files,
                                                  QString *errorMessage);

private:
  ProjectExplorer::Project* _contextProject;
  ProjectExplorer::Node*    _contextNode;
};

} // namespace Internal
} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTCASEWIZARD_HPP
