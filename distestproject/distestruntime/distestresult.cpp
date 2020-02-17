#include "distestresult.hpp"

#include <mobata/memory_leak_start.hpp>

namespace distestproject {
namespace distestruntime {

DisTestResult::DisTestResult()
    : _verdict(DisTestResult::NOT_EXECUTED),
      _errorMessage(QLatin1String(""))
{}

DisTestResult::~DisTestResult()
{}

void DisTestResult::clearResult()
{
  this->_verdict = NOT_EXECUTED;
  this->_errorMessage = QLatin1String("");
}

void DisTestResult::setVerdict(DisTestResult::Verdict verdict)
{
  this->_verdict = verdict;
}

DisTestResult::Verdict DisTestResult::verdict() const
{
  return this->_verdict;
}

void DisTestResult::setErrorMessage(const QString &error)
{
  this->_errorMessage = error;
}

QString DisTestResult::errorMessage() const
{
  return this->_errorMessage;
}

QString DisTestResult::toString() const
{
  return this->toString(this->_verdict);
}

QString DisTestResult::toString(const Verdict& ver)
{
  switch (ver)
  {
    case SUCCESS:
      return QStringLiteral("Succeeded");
    case FAIL:
      return QStringLiteral("Failed");
    case EXCLUDE:
      return QStringLiteral("Excluded");
    case NOT_EXECUTED:
      return QStringLiteral("NoRun");
    default:
      return QStringLiteral("Unknown result");
  }
  return QStringLiteral("Unknown result");
}

} // namespace distestruntime
} // namespace distestproject

