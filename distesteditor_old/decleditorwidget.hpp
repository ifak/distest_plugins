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
#ifndef DISTESTEDITOR_DECLEDITORWIDGET_HPP
#define DISTESTEDITOR_DECLEDITORWIDGET_HPP

#include <dsleditor/dsleditorwidget.hpp>

#include "decleditor.hpp"

namespace distesteditor{

class DeclEditorWidget
    : public dsleditor::DslEditorWidget
{
  Q_OBJECT

public:
  explicit DeclEditorWidget(QWidget *parent = 0);
  virtual ~DeclEditorWidget();

protected:
  DeclEditor* createEditor();

private:
  Q_DISABLE_COPY(DeclEditorWidget)
  class Private;
  Private* _d;
};

} //end namespace distesteditor

#endif //DISTESTEDITOR_DECLEDITORWIDGET_HPP
