#ifndef CROW_CROW_DIAGNOSTIC_DIAGNOSTIC_ERROR_HPP
#define CROW_CROW_DIAGNOSTIC_DIAGNOSTIC_ERROR_HPP

// STL Includes:
#include <sstream>
#include <string>

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
  DiagnosticError(std::string_view t_msg);

  virtual auto what() const noexcept -> const std::string_view;

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

  // Add all arguments to the string stream.
  (ss << ... << t_args);

  throw T{ss.view()};
}
} // namespace diagnostic

#endif // CROW_CROW_DIAGNOSTIC_DIAGNOSTIC_ERROR_HPP
