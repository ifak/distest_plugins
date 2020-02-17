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
#ifndef DISTESTPROJECT_DISTESTRUNTIME_DISTESTRESULT_HPP
#define DISTESTPROJECT_DISTESTRUNTIME_DISTESTRESULT_HPP

#include "../distestproject_global.hpp"

#include <QString>

namespace distestproject {
namespace distestruntime {

class DISTESTPROJECTSHARED_EXPORT DisTestResult
{
public:

  enum Verdict{
    FAIL,
    SUCCESS,
    EXCLUDE,
    NOT_EXECUTED
  };

  DisTestResult();
  virtual ~DisTestResult();

public:
  void clearResult();
  void setVerdict(Verdict verdict);
  Verdict verdict() const;

  void setErrorMessage(const QString& error);
  QString errorMessage() const;
  QString toString() const;

  static QString toString(const Verdict &ver);

private:
  Verdict _verdict;
  QString _errorMessage;
};

} // namespace distestruntime
} // namespace distestproject

#endif // DISTESTPROJECT_DISTESTRUNTIME_DISTESTRESULT_HPP
