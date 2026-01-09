#ifndef CROW_CROW_AST_NODE_LVALUE_VAR_HPP
#define CROW_CROW_AST_NODE_LVALUE_VAR_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::lvalue {
// Aliases:
using container::TextPosition;
using node_traits::BindingExpr;

// Classes:
class Var : public BindingExpr {
  private:
  NodePtr m_init;

  public:
  Var(TextPosition t_pos, std::string_view t_identifier, NodePtr&& t_type,
      NodePtr&& t_init);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Var, BindingExpr)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Var() = default;
};
} // namespace ast::node::lvalue

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::lvalue, Var);

#endif // CROW_CROW_AST_NODE_LVALUE_VAR_HPP
