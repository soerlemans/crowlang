#include "native_types.hpp"


namespace typing {
auto nativetype2str(const NativeType t_ntype) -> std::string
{
  std::string id;
  auto& rmap{reserved_types.right};

  const auto iter{rmap.find(t_ntype)};
  if(iter != rmap.end()) {
    id = iter->second;
  }

  return id;
}
} // namespace typing

auto operator<<(std::ostream& t_os, const typing::NativeType t_type)
  -> std::ostream&
{
  t_os << typing::nativetype2str(t_type);

	return t_os;
}
