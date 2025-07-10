#include "syntax_error.hpp"

// STL Includes:
#include <iomanip>
#include <string>

namespace exception {
// Methods:
auto SyntaxError::format(const std::string_view t_msg,
                         const TextPosition& t_pos) const -> std::string
{
  std::stringstream ss;
  std::stringstream lineno_ss;

  const auto [path, line, lineno, columnno] = t_pos;

  // Line number is zero indexed
  lineno_ss << " - Line(";
  lineno_ss << lineno + 1;
  lineno_ss << "):";

  ss << "Error in file: " << std::quoted(path) << '\n';
  ss << "Error description: " << std::quoted(t_msg) << '\n';
  ss << lineno_ss.str();

  // If the line does not have a newline at the end add it.
  if(line.back() != '\n') {
    ss << '\n';
  }

  ss << line;

  const auto indent{lineno_ss.str().size() + columnno};
  ss << std::string(indent, ' ') << "^__" << '\n';

  return ss.str();
}

SyntaxError::SyntaxError(const std::string_view t_msg,
                         const TextPosition& t_pos)
  : Error{format(t_msg, t_pos)}, m_pos(t_pos)
{}
} // namespace exception
