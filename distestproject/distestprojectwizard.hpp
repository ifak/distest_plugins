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
#ifndef DISTESTPROJECT_DISTESTPROJECTWIZARD_HPP
#define DISTESTPROJECT_DISTESTPROJECTWIZARD_HPP

#include "distestproject_global.hpp"

#include <coreplugin/basefilewizard.h>
#include <utils/filewizarddialog.h>

#include <QWizardPage>

class QLineEdit;
class QPlainTextEdit;
class QFile;

namespace distestproject {

class DISTESTPROJECTSHARED_EXPORT DisTestProjectWizardPage
    : public QWizardPage
{
  Q_OBJECT
public:
  explicit DisTestProjectWizardPage(const QString& title,
                                    QWidget *parent = 0);

public:
  virtual bool isComplete() const { return _complete; }

private slots:
  void slotChanged();

private:
  bool _complete;
};


class DISTESTPROJECTSHARED_EXPORT DisTestProjectWizardDialog
    : public Utils::FileWizardDialog
{
  Q_OBJECT
public:
  explicit DisTestProjectWizardDialog(const QString& title,
                                      QWidget *parent = 0);

  QString title() const    { return this->_contentPage->title(); }

private:
  DisTestProjectWizardPage* _contentPage;
};


class DISTESTPROJECTSHARED_EXPORT DisTestProjectWizard
    : public Core::BaseFileWizard
{
public:
  explicit DisTestProjectWizard(const QString& title,
                                const QString& projectFileExtension,
                                const Core::BaseFileWizardParameters &parameters,
                                QObject *parent = 0);

protected:
  virtual QWizard* createWizardDialog(QWidget *parent,
                                      const Core::WizardDialogParameters &wizardDialogParameters) const;

  virtual Core::GeneratedFiles generateFiles(const QWizard *wizard,
                                             QString* errorString) const;

  virtual QString generateExampleProjectFileContent(const QString& projectFileName,
                                                    QString* errorMessage) const;

  virtual bool postGenerateFiles(QWizard const* wizard,
                                 const Core::GeneratedFiles& files,
                                 QString *errorMessage);

protected:
  QString _title;
  QString _projectFileExtension;
};

} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTPROJECTWIZARD_HPP
