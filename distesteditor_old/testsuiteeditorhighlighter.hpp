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
#ifndef DISTESTEDITOR_TESTSUITEEDITORHIGHLIGHTER_HPP
#define DISTESTEDITOR_TESTSUITEEDITORHIGHLIGHTER_HPP

#include "distestdslhighlighter.hpp"

namespace distesteditor{

class DISTESTEDITOR_EXPORT TestSuiteEditorHighlighter
    : public DisTestDslHighlighter
{
  Q_OBJECT

public:
  TestSuiteEditorHighlighter(QTextDocument *parent = 0);
  virtual ~TestSuiteEditorHighlighter();
};

} // namespace distesteditor

#endif // DISTESTEDITOR_TESTSUITEEDITORHIGHLIGHTER_HPP
