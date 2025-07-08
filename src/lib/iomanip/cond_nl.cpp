#include "cond_nl.hpp"

// STL Includes:
#include <iostream>

namespace lib::iomanip {
// Set static member indicating a newline should be inserted.
bool CondNl::m_insert_nl{false};

auto CondNl::enable() -> void
{
  m_insert_nl = true;
}

auto CondNl::disable() -> void
{
  m_insert_nl = false;
}

// Friend method:
auto operator<<(std::ostream& t_os, lib::iomanip::CondNl t_cond_nl)
  -> std::ostream&
{
  if(t_cond_nl.m_insert_nl) {
    t_os.put('\n');
  }

  return t_os;
}

// Functions:
auto cond_nl(std::ostream& t_os) -> std::ostream&
{
  t_os << lib::iomanip::CondNl{};

  return t_os;
}
} // namespace lib::iomanip
