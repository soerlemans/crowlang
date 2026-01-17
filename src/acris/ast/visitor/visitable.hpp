#ifndef ACRIS_ACRIS_AST_VISITOR_VISITABLE_HPP
#define ACRIS_ACRIS_AST_VISITOR_VISITABLE_HPP

// STL Includes:
#include <any>


// Macros:
#define AST_VISITOR_MAKE_VISITABLE(t_visitor_type)                     \
  auto accept(t_visitor_type* t_visitor) -> ast::visitor::Any override \
  {                                                                    \
    return {t_visitor->visit(this)};                                   \
  }

#define AST_VISITOR_VISITABLE_PURE_ACCEPT(t_visitor_type) \
  auto accept(t_visitor_type*) -> ast::visitor::Any override = 0

namespace ast::visitor {
// We use std::any to allow a visitor to return anything
using Any = std::any;

// Classes:
/*!
 * Inheriting from this forces children to be visitable.
 */
template<typename VisitorType, typename RetType = Any>
class Visitable {
  public:
  virtual auto accept(VisitorType* t_visitor) -> RetType = 0;
};
} // namespace ast::visitor

#endif // ACRIS_ACRIS_AST_VISITOR_VISITABLE_HPP
