#include "tokenstream.hpp"


auto operator<<(std::ostream& t_os, const token::TokenStream& t_ts)
  -> std::ostream&
{
  t_os << '[';

  for(const auto& tok : t_ts) {
    t_os << tok << ", ";
  }

  t_os << ']';

  return t_os;
}
