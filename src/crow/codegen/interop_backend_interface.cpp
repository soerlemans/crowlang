#include "interop_backend_interface.hpp"

namespace codegen {
auto interopbackendtype2str(InteropBackendType t_type) -> std::string_view
{
  switch(t_type) {
    case InteropBackendType::C_INTEROP_BACKEND:
      return "C";

    case InteropBackendType::PYTHON_INTEROP_BACKEND:
      return "python";

    case InteropBackendType::LUA_INTEROP_BACKEND:
      return "lua";

    case InteropBackendType::JS_INTEROP_BACKEND:
      return "javascript";

    default:
      throw std::invalid_argument{
        "interopbackendtype2str() could not convert BackendType to string."};
      break;
  }

  return {};
}
} // namespace codegen

// Operators:
auto operator<<(std::ostream& t_os, const codegen::InteropBackendType t_type)
  -> std::ostream&
{
  using codegen::interopbackendtype2str;

  t_os << interopbackendtype2str(t_type);

  return t_os;
}
