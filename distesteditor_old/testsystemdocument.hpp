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
#ifndef DISTESTEDITOR_TESTSYSTEMDOCUMENT_HPP
#define DISTESTEDITOR_TESTSYSTEMDOCUMENT_HPP

#include "distesteditor_global.hpp"

#include <texteditor/basetextdocument.h>

namespace distesteditor{


class TestSystemDocument : public TextEditor::BaseTextDocument
{
  Q_OBJECT

public:
  explicit TestSystemDocument(QObject *parent = 0);
  virtual ~TestSystemDocument();
};

} //end namespace distesteditor
#endif //DISTESTEDITOR_TESTSYSTEMDOCUMENT_HPP
