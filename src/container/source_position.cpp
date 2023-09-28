#include "source_position.hpp"

// STL Includes:
#include <sstream>


using namespace container;

SourcePosition::SourcePosition(const std::string_view t_source,
                               const std::size_t t_line_nr,
                               const std::string_view t_function)
  : m_source{t_source}, m_line_nr{t_line_nr}, m_function{t_function}
{}

namespace container {
auto operator<<(std::ostream& t_os, const SourcePosition& t_fp) -> std::ostream&
{
  std::stringstream ss;

  ss << t_fp.m_source << ":" << t_fp.m_line_nr;
  ss << " -> " << t_fp.m_function << "()";

  t_os << ss.str();

  return t_os;
}
} // namespace container
