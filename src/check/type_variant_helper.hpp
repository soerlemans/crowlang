#ifndef CROW_CHECK_TYPE_VARIANT_HELPER_HPP
#define CROW_CHECK_TYPE_VARIANT_HELPER_HPP


// Includes:
#include "../ast/visitor/node_visitor.hpp"

// Local Includes:
#include "type_variant.hpp"


namespace check {
// Using statements:
using namespace ast;
using visitable::Any;

// Classes:
/*! This class defines some utiilties for dealing with a TypeVariant in Visitor
 * context
 */
class TypeVariantHelper : public visitor::NodeVisitor {
  protected:
  template<typename T, typename... Args>
  inline auto define_type_variant(Args&&... t_args) -> TypeVariant
  {
    return {std::make_shared<T>(std::forward<Args>(t_args)...)};
  }

  template<typename... Args>
  inline auto define_function(Args&&... t_args) -> TypeVariant
  {
    return {define_type_variant<FnType>(std::forward<Args>(t_args)...)};
  }

  template<typename... Args>
  inline auto define_variable(Args&&... t_args) -> TypeVariant
  {
    return {define_type_variant<VarType>(std::forward<Args>(t_args)...)};
  }

  auto get_variant(ast::node::NodePtr t_ptr) -> TypeVariant;
  auto get_list(ast::node::NodeListPtr t_list) -> TypeList;
  // auto get_type(TypeVariant t_variant) -> NativeType;

  public:
  TypeVariantHelper() = default;

  ~TypeVariantHelper() override = default;
};
} // namespace check

#endif // CROW_CHECK_TYPE_VARIANT_HELPER_HPP
