#include "syntax_error.hpp"

#include <iomanip>
#include <sstream>
#include <string>

// The following members m_lineno and m_columno are zero indexed so they need to
// Have + 1 counted for them to line up properly
SyntaxError::SyntaxError(const std::string_view t_msg,
                         const container::TextPosition& t_pos)
  : m_pos(t_pos)
{
  std::stringstream ss;
  std::stringstream lineno_ss;

  auto [path, line, lineno, columnno] = m_pos;

  lineno_ss << " - Line(";
  lineno_ss << lineno;
  lineno_ss << "): ";

  ss << "Error in file: " << '"' << path << '"' << '\n';
  ss << "Error description: " << '"' << t_msg << '"' << "\n";
  ss << lineno_ss.str();

  // FIXME: If t_line does not end in a newline we have an issue!
  ss << line;

  // FIXME: ~^~ does not align
  const auto indent{lineno_ss.str().size() + columnno};
  ss << std::string(indent, ' ') << "~^~" << '\n';

  m_error = ss.str();
}

auto SyntaxError::what() const noexcept -> const char*
{
  return m_error.c_str();
}
