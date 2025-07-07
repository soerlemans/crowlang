#include "cond_nl.hpp"

namespace lib::iomanip {
// Set static
bool CondNl::m_insert_nl{false};

} // namespace lib::iomanip

// Functions:
auto operator<<(std::ostream& t_os, lib::iomanip::CondNl t_cond_nl)
  -> std::ostream&
{
  if(t_cond_nl.m_insert_nl) {
    t_os << '\n';
  }

  return t_os;
}
