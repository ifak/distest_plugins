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
#ifndef DISTESTEDITOR_DISTESTDSLINDENTER_HPP
#define DISTESTEDITOR_DISTESTDSLINDENTER_HPP

#include "distesteditor_global.hpp"

#include <dsleditor/dslindenter.hpp>

namespace distesteditor {

typedef dsleditor::DslIndenter  DisTestDslIndenter;

//class DISTESTEDITOR_EXPORT DisTestDslIndenter : public TextEditor::Indenter
//{
//public:
//  DisTestDslIndenter();
//  virtual ~DisTestDslIndenter();

//public:
//  virtual bool isElectricCharacter(const QChar &ch) const;
//  virtual void indentBlock(QTextDocument *doc,
//                           const QTextBlock &block,
//                           const QChar &typedChar,
//                           const TextEditor::TabSettings &tabSettings);
//  virtual void invalidateCache(QTextDocument *doc);
//};

} // namespace distesteditor

#endif // DISTESTEDITOR_DISTESTDSLINTENDER_HPP
