#include "source_position.hpp"

// Library includes:
#include <rang.hpp>


using namespace container;

SourcePosition::SourcePosition(const std::string_view t_source,
                               const std::size_t t_line_nr,
                               const std::string_view t_function)
  : m_source{t_source}, m_line_nr{t_line_nr}, m_function{t_function}
{}

namespace container {
auto operator<<(std::ostream& t_os, const SourcePosition& t_fp) -> std::ostream&
{
  using namespace rang;

  t_os << t_fp.m_source << ":" << style::bold << t_fp.m_line_nr << style::reset;
  t_os << " -> " << t_fp.m_function << "()";

  return t_os;
}
} // namespace container
