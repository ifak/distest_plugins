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
#ifndef DISTESTEDITOR_DISTESTDSLHIGHLIGHTER_HPP
#define DISTESTEDITOR_DISTESTDSLHIGHLIGHTER_HPP

#include "distesteditor_global.hpp"

#include <dsleditor/dslhighlighter.hpp>

namespace distesteditor {

typedef dsleditor::DslHighlighter DisTestDslHighlighter;

//class DISTESTEDITOR_EXPORT DisTestDslHighlighter
//    : public TextEditor::SyntaxHighlighter
//{
//  Q_OBJECT

//public:
//  DisTestDslHighlighter(QTextDocument *parent = 0);
//  virtual ~DisTestDslHighlighter();

//public:
//  enum {
//      NumberFormat,
//      StringFormat,
//      TypeFormat,
//      KeywordFormat,
//      FieldFormat,
//      CommentFormat,
//      VisualWhitespace,
//      NumFormats
//  };

//  bool isQmlEnabled() const;
//  void setQmlEnabled(bool qmlEnabled);
//  void setFormats(const QVector<QTextCharFormat> &formats);

//protected:
//  virtual void highlightBlock(const QString &text);
//  virtual bool maybeDisTestDslKeyword(const QStringRef &text) const;
//  virtual bool maybeDisTestDslBuiltinType(const QStringRef &text) const;

//  int onBlockStart();
//  void onBlockEnd(int state);

//  // The functions are notified whenever parentheses are encountered.
//  // Custom behaviour can be added, for example storing info for indenting.
//  void onOpeningParenthesis(QChar parenthesis, int pos, bool atStart);
//  void onClosingParenthesis(QChar parenthesis, int pos, bool atEnd);

//private:
//  typedef TextEditor::Parenthesis Parenthesis;
//  typedef TextEditor::Parentheses Parentheses;

//  bool m_qmlEnabled;
//  int m_braceDepth;
//  int m_foldingIndent;
//  bool m_inMultilineComment;

//  QmlJS::Scanner m_scanner;
//  Parentheses m_currentBlockParentheses;

//  QTextCharFormat m_formats[NumFormats];
//};

} // namespace distesteditor

#endif // DISTESTEDITOR_DISTESTDSLHIGHLIGHTER_HPP
