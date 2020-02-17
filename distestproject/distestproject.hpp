/*
 * This file is part of mobata.
 *
 * mobata is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * mobata is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with mobata.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "distestproject_global.hpp"

#include <projectexplorer/baseproject.hpp>

#include <libs/dslparser/dslparser/dslerror.hpp>

namespace Core{
class IEditor;
}

namespace distestproject {

class DisTestConfiguration;
class DisTestProjectModel;

class DISTESTPROJECTSHARED_EXPORT DisTestProject
    : public ProjectExplorer::BaseProject
{
  Q_OBJECT

  friend class ComBuildTestModel;
public:
  explicit DisTestProject(ProjectExplorer::BaseProjectManager *projectManager,
                          const QString& fileName,
                          const QString& mimeType,
                          const QString& id);
  virtual ~DisTestProject();

public:
  DisTestConfiguration* disTestConfiguration() const;

public:
  virtual bool        needsConfiguration() const;
  virtual bool        supportsNoTargetPanel() const;
  virtual bool        reload(QString* errorString);
  virtual QStringList files(FilesMode fileMode) const;

public:
  DisTestProjectModel const*    disTestProjectModel() const;
  bool                          rebuildTestModel(QString* errorMessage);
  const QStringList&            declFiles() const;
  const QStringList&            sutFiles() const;
  const QStringList&            testSystemFiles() const;
  const QStringList&            testCaseFiles() const;
  int                           testCaseCount() const;
  const QString&                prioFile() const;

  bool                          addTestCaseFile(const QString& testCaseFileName,
                                                QString* errorMessage);
  bool                          addPrioFile(const QString& prioFileName,
                                                QString* errorMessage);

public:
  bool                                      isError() const;
  const QList<ProjectExplorer::BaseError>&  errors() const;
  void                                      addError(const ProjectExplorer::BaseError& newError);
  void                                      addDslError(const dslparser::DslError& newDslError,
                                                        const QString& errorFileName);
  QString                                   errorString() const;

protected:
  virtual bool        fromMap(const QVariantMap &map);
  virtual QVariantMap toMap() const;

private:
  void        reset();

private:
  Q_DISABLE_COPY(DisTestProject)
  class Private;
  Private*  _d;
};

} // namespace distestproject
