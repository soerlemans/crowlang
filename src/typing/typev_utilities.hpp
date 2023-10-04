#ifndef CROW_TYPING_TYPEV_UTILITIES_HPP
#define CROW_TYPING_TYPEV_UTILITIES_HPP

// Includes:
#include "../ast/visitor/node_visitor.hpp"

// Local Includes:
#include "native_types.hpp"


namespace typing {
// Using statements:
using namespace ast;
using visitable::Any;

// Aliases:
//! This is an abbreviation for TypeVariant
using TypeV = std::variant<NativeType, std::string>;


// Classes:
/*! This class defines some utiilties for dealing with a TypeV in Visitor
 * context
 */
class TypeVVisitor : public visitor::NodeVisitor {
  protected:
  auto get_typev(ast::node::NodePtr t_ptr) -> TypeV;

  public:
  TypeVVisitor() = default;

  ~TypeVVisitor() override = default;
};

//! Check if a TypeV is one of the following arguments
template<typename... Args>
auto typev_any_of(const TypeV& t_typev, Args&&... t_args) -> bool
{
  return ((t_typev == TypeV{t_args}) || ...);
}

auto is_integer(const TypeV& t_typev) -> bool;
auto is_float(const TypeV& t_typev) -> bool;
auto is_bool(const TypeV& t_typev) -> bool;

auto is_condition(const TypeV& t_typev) -> bool;
auto is_numeric(const TypeV& t_typev) -> bool;
} // namespace typing

auto operator<<(std::ostream& t_os, const typing::TypeV t_typev)
  -> std::ostream&;

#endif // CROW_TYPING_TYPEV_UTILITIES_HPP
