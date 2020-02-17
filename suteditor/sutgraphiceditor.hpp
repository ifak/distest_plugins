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

#include "suteditor_global.hpp"

#include <dsleditor/dslgraphiceditor.hpp>

#include "sutgraphicwidget.hpp"

namespace model{ namespace ts{
class SutItem;
}}

namespace suteditor {

class SUTEDITOR_EXPORT SutGraphicEditor
    : public dsleditor::DslGraphicEditor
{
  Q_OBJECT

public:
  SutGraphicEditor(SutGraphicWidget* sutGraphicWidget);
  ~SutGraphicEditor();

public:
  virtual bool              open(QString *errorString,
                                 const QString &fileName,
                                 const QString &realFileName) override;
  virtual Core::IDocument*  document() override;
  virtual QWidget*          toolBar() override;

public:
  void                      setSutItem(model::ts::SutItem const* sutItem);
  model::ts::SutItem const* sutItem() const;

public:
  SutGraphicWidget* sutGraphicWidget();
  QString           fileName() const;

private:
  Q_DISABLE_COPY(SutGraphicEditor)
  class Private;
  Private* _d;
};

} // namespace suteditor
