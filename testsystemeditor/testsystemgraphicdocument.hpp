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
#pragma once

#include "testsystemeditor_global.hpp"

#include <coreplugin/idocument.h>

namespace view{ namespace ts{ class TestSystemScene;}}

namespace testsystemeditor {

class TESTSYSTEMEDITOR_EXPORT TestSystemGraphicDocument
    : public Core::IDocument
{
  Q_OBJECT

public:
  TestSystemGraphicDocument(QObject *parent = 0);
  virtual ~TestSystemGraphicDocument();

public:
  view::ts::TestSystemScene*  testSystemScene();
  bool                        open(QString *errorString,
                                   const QString &fileName,
                                   const QString &realFileName);

public:
  virtual bool save(QString *errorString,
                    const QString &fileName = QString(),
                    bool autoSave = false);
  virtual QString fileName() const;
  virtual bool isFileReadOnly() const;

  virtual QString defaultPath() const;
  virtual QString suggestedFileName() const;
  virtual QString mimeType() const;

  virtual bool shouldAutoSave() const;
  virtual bool isModified() const;
  virtual bool isSaveAsAllowed() const;

  virtual bool reload(QString *errorString,
                      ReloadFlag flag,
                      ChangeType type);
  virtual void rename(const QString &newName);

private:
  Q_DISABLE_COPY(TestSystemGraphicDocument)
  class Private;
  Private* _d;
};

} // namespace testsystemeditor
