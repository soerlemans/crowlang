#ifndef CROW_EXCEPTION_SYNTAX_ERROR_HPP
#define CROW_EXCEPTION_SYNTAX_ERROR_HPP

// STL Includes:
#include <filesystem>

// Includes:
#include "../container/text_position.hpp"

// Local Includes:
#include "error.hpp"


namespace exception {
/*!
 * Is thrown when source code of a crow program contains a syntax error.
 */
class SyntaxError : public Error {
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
