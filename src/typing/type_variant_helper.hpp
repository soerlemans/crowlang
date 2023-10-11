#ifndef CROW_TYPING_TYPE_VARIANT_HELPER_HPP
#define CROW_TYPING_TYPE_VARIANT_HELPER_HPP


// Includes:
#include "../ast/visitor/node_visitor.hpp"

// Local Includes:
#include "type_variant.hpp"


namespace typing {
// Using statements:
using namespace ast;
using visitable::Any;

// Classes:
/*! This class defines some utiilties for dealing with a TypeVariant in Visitor
 * context
 */
class TypeVariantHelper : public visitor::NodeVisitor {
  protected:
  auto get_variant(ast::node::NodePtr t_ptr) -> TypeVariant;
  auto get_list(ast::node::NodeListPtr t_list) -> TypeVec;
  // auto get_type(TypeVariant t_variant) -> NativeType;

  public:
  TypeVariantHelper() = default;

  ~TypeVariantHelper() override = default;
};
} // namespace typing

#endif // CROW_TYPING_TYPE_VARIANT_HELPER_HPP
