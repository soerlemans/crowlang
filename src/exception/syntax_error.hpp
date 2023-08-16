#ifndef NEWLANG_EXCEPTION_SYNTAX_ERROR_HPP
#define NEWLANG_EXCEPTION_SYNTAX_ERROR_HPP

// STL Includes:
#include <filesystem>
#include <stdexcept>

// Includes:
#include "../container/text_position.hpp"


// Error classes intended for being thrown as exceptions
// When a mistake is made
class SyntaxError : public std::exception {
  protected:
  std::string m_error;
  container::TextPosition m_pos;

  public:
  SyntaxError(std::string_view t_msg,
              const container::TextPosition& t_pos);

  auto what() const noexcept -> const char* override;
};

#endif // NEWLANG_EXCEPTION_SYNTAX_ERROR_HPP
