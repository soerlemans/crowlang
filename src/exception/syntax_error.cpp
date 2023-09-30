#include "syntax_error.hpp"

// STL Includes:
#include <iomanip>
#include <sstream>
#include <string>


// Using statements:
using namespace exception;

SyntaxError::SyntaxError(const std::string_view t_msg,
                         const container::TextPosition& t_pos)
  : m_pos(t_pos)
{
  std::stringstream ss;
  std::stringstream lineno_ss;

  auto [path, line, lineno, columnno] = m_pos;

  // Lineno is zero indexed
  lineno_ss << " - Line(";
  lineno_ss << lineno + 1;
  lineno_ss << "):";

  ss << "Error in file: " << std::quoted(path) << '\n';
  ss << "Error description: " << std::quoted(t_msg) << "\n";
  ss << lineno_ss.str();

  ss << line;

  const auto indent{lineno_ss.str().size() + columnno};
  ss << std::string(indent, ' ') << "^__" << '\n';

  m_error = ss.str();
}

auto SyntaxError::what() const noexcept -> const char*
{
  return m_error.c_str();
}
