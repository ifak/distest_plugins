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

#include "diagnosiseditor_global.hpp"

#include <dsleditor/dslgraphiceditor.hpp>

#include "diagnosisgraphicwidget.hpp"

namespace model{ namespace diagnosis{
class DiagnosisItem;
}}

namespace diagnosiseditor {

class DIAGNOSISEDITOR_EXPORT DiagnosisGraphicEditor
    : public dsleditor::DslGraphicEditor
{
  Q_OBJECT

public:
  DiagnosisGraphicEditor(DiagnosisGraphicWidget* diagnosisGraphicWidget);
  virtual ~DiagnosisGraphicEditor();

public:
  virtual bool              open(QString *errorString,
                                 const QString &fileName,
                                 const QString &realFileName) override;
  virtual Core::IDocument*  document() override;
  virtual QWidget*          toolBar() override;

public:
  void                                    setDiagnosisItem(model::diagnosis::DiagnosisItem const* diagnosisItem);
  model::diagnosis::DiagnosisItem const*  diagnosisItem() const;

public:
  DiagnosisGraphicWidget* diagnosisGraphicWidget();
  QString                 fileName() const;

private:
  Q_DISABLE_COPY(DiagnosisGraphicEditor)
  class Private;
  Private* _d;
};

} // namespace diagnosiseditor
