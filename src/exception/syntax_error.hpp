#ifndef CROW_EXCEPTION_SYNTAX_ERROR_HPP
#define CROW_EXCEPTION_SYNTAX_ERROR_HPP

// STL Includes:
#include <filesystem>
#include <stdexcept>

// Includes:
#include "../container/text_position.hpp"


namespace exception {
//! SyntaxError is thrown when there is an error in the syntax
class SyntaxError : public std::exception {
  protected:
  std::string m_error;
  container::TextPosition m_pos;

  public:
  SyntaxError(std::string_view t_msg, const container::TextPosition& t_pos);

  auto what() const noexcept -> const char* override;
};
} // namespace exception

#endif // CROW_EXCEPTION_SYNTAX_ERROR_HPP
