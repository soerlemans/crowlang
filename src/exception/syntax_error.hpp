#ifndef CROW_EXCEPTION_SYNTAX_ERROR_HPP
#define CROW_EXCEPTION_SYNTAX_ERROR_HPP

// STL Includes:
#include <filesystem>

// Includes:
#include "../container/text_position.hpp"

// Local Includes:
#include "stacktrace_exception.hpp"


namespace exception {
//! SyntaxError is thrown when there is an error in the syntax
class SyntaxError : public StacktraceException {
  private:
  auto format(std::string_view t_msg) -> std::string override;

  protected:
  container::TextPosition m_pos;

  public:
  SyntaxError(std::string_view t_msg, const container::TextPosition& t_pos);

  ~SyntaxError() override = default;
};
} // namespace exception

#endif // CROW_EXCEPTION_SYNTAX_ERROR_HPP
