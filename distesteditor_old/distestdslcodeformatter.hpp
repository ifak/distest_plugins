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
#ifndef DISTESTEDITOR_DISTESTDSLCODEFORMATTER_HPP
#define DISTESTEDITOR_DISTESTDSLCODEFORMATTER_HPP

#include "distesteditor_global.hpp"

#include <dsleditor/dslcodeformatter.hpp>

namespace distesteditor {

typedef dsleditor::DslCodeFormatter DisTestDslCodeFormatter;

//class DISTESTEDITOR_EXPORT DisTestDslCodeFormatter
//    : public QmlJS::QtStyleCodeFormatter
//{
//public:
//  DisTestDslCodeFormatter();
//  explicit DisTestDslCodeFormatter(const TextEditor::TabSettings &tabSettings);

//  virtual ~DisTestDslCodeFormatter();

//protected:
//  virtual void saveBlockData(QTextBlock *block, const BlockData &data) const;
//  virtual bool loadBlockData(const QTextBlock &block, BlockData *data) const;

//  virtual void saveLexerState(QTextBlock *block, int state) const;
//  virtual int loadLexerState(const QTextBlock &block) const;

//private:
//  class DisTestDslCodeFormatterData: public TextEditor::CodeFormatterData
//  {
//  public:
//    QmlJS::CodeFormatter::BlockData m_data;
//  };
//};

} // namespace distesteditor

#endif // DISTESTEDITOR_DISTESTDSLCODEFORMATTER_HPP
