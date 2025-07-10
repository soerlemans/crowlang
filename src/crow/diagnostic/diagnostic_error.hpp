#ifndef CROW_CROW_DIAGNOSTIC_DIAGNOSTIC_ERROR_HPP
#define CROW_CROW_DIAGNOSTIC_DIAGNOSTIC_ERROR_HPP

// STL Includes:
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <utility>

// Library Includes:
#include <cpptrace/cpptrace.hpp>

namespace diagnostic {
// Classes:
/*!
 * Base diagnostic error class.
 * Includes a stacktrace when compiling with the @ref DEBUG macro defined.
 * Used to signal when a user has made a mistake.
 */
class DiagnosticError {
  protected:
  std::string m_error;

  public:
  DiagnosticError(std::string t_msg);

  virtual auto what() const noexcept -> const char*;

  // TODO: Maybe keep the stack trace separately accessible?
  // auto trace() const noexcept -> const stacktrace&;

  virtual ~DiagnosticError() = default;
};

// Functions:
template<typename T = DiagnosticError, typename... Args>
  requires std::is_base_of<DiagnosticError, T>::value
inline auto diagnostic_error(Args&&... t_args) -> void
{
  std::stringstream ss;
  std::string str;

  // Add all arguments to the string stream.
  (ss << ... << t_args);

  str = ss.view();

  throw T{str};
}
} // namespace diagnostic

#endif // CROW_CROW_DIAGNOSTIC_DIAGNOSTIC_ERROR_HPP
