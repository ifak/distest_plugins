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
#ifndef DISTESTEDITOR_DISTESTDSLAUTOCOMPLETER_HPP
#define DISTESTEDITOR_DISTESTDSLAUTOCOMPLETER_HPP

#include "distesteditor_global.hpp"

#include <dsleditor/dslautocompleter.hpp>

namespace distesteditor {

typedef dsleditor::DslAutoCompleter DisTestDslAutoCompleter;

//class DISTESTEDITOR_EXPORT DisTestDslAutoCompleter
//        : public TextEditor::AutoCompleter
//{
//public:
//  DisTestDslAutoCompleter();
//  virtual ~DisTestDslAutoCompleter();

//public:
//  virtual bool    contextAllowsAutoParentheses(const QTextCursor &cursor,
//                                               const QString &textToInsert = QString()) const;
//  virtual bool    contextAllowsElectricCharacters(const QTextCursor &cursor) const;
//  virtual bool    isInComment(const QTextCursor &cursor) const;
//  virtual QString insertMatchingBrace(const QTextCursor &tc,
//                                      const QString &text,
//                                      QChar la,
//                                      int *skippedChars) const;
//  virtual QString insertParagraphSeparator(const QTextCursor &tc) const;
//};

} // namespace distesteditor

#endif // DISTESTEDITOR_DISTESTDSLAUTOCOMPLETER_HPP
