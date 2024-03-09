#include "type_variant.hpp"

// Includes:
#include "../../../../debug/log.hpp"
#include "../../../../exception/error.hpp"
#include "../../../../lib/overload.hpp"

// Local Includes:
#include "types.hpp"

namespace ast::node::node_traits::typing {
// Using Statements:
using exception::error;

// Methods:
auto TypeVariant::struct_() const -> StructTypePtr
{
  return std::get<StructTypePtr>(*this);
}

auto TypeVariant::function() const -> FnTypePtr
{
  return std::get<FnTypePtr>(*this);
}

auto TypeVariant::var() const -> VarTypePtr
{
  return std::get<VarTypePtr>(*this);
}

//! Resolves the @ref TypeVariant to a @ref NativeType if possible.
auto TypeVariant::native_type() const -> NativeTypeOpt
{
  NativeTypeOpt opt;

  const auto native{[&](const NativeType t_type) -> NativeTypeOpt {
    return t_type;
  }};

  const auto methods{[&](const std::shared_ptr<auto>& t_data) {
    if(!t_data) {
      error("ptr is nullptr!");
    }

    return t_data->native_type();
  }};

  opt = std::visit(Overload{native, methods}, *this);

  return opt;
}
} // namespace ast::node::node_traits::typing

// Functions:
auto operator<<(std::ostream& t_os,
                const ast::node::node_traits::typing::TypeVariant& t_variant)
  -> std::ostream&
{
  std::visit(
    [&](auto&& t_v) {
      t_os << t_v;
    },
    t_variant);

  return t_os;
}
