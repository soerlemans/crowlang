#ifndef ACRIS_ACRIS_DIAGNOSTIC_SYNTAX_ERROR_HPP
#define ACRIS_ACRIS_DIAGNOSTIC_SYNTAX_ERROR_HPP

// STL Includes:
#include <filesystem>

// Absolute Includes:
#include "acris/container/text_position.hpp"

// Local Includes:
#include "diagnostic_error.hpp"

namespace diagnostic {
// Using Statements:
using container::TextPosition;

// Classes:
/*!
 * Is thrown when source code of a acris program contains a syntax error.
 */
class SyntaxError : public DiagnosticError {
  private:
  auto format(std::string_view t_msg, const TextPosition& t_pos) const
    -> std::string;

  protected:
  container::TextPosition m_pos;

  public:
  SyntaxError(std::string_view t_msg, const TextPosition& t_pos);

  virtual ~SyntaxError() = default;
};
} // namespace diagnostic

#endif // ACRIS_ACRIS_DIAGNOSTIC_SYNTAX_ERROR_HPP
