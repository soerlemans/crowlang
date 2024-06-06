#ifndef CROW_CROW_AST_NODE_LVALUE_LET_HPP
#define CROW_CROW_AST_NODE_LVALUE_LET_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::lvalue {
// Using Statements:
using container::TextPosition;
using node_traits::DeclExpr;

// Classes:
class Let : public DeclExpr {
  public:
  Let(TextPosition t_pos, std::string_view t_identifier,
      std::string_view t_type, NodePtr&& t_init);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Let, DeclExpr)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Let() = default;
};
} // namespace ast::node::lvalue

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::lvalue, Let);

#endif // CROW_CROW_AST_NODE_LVALUE_LET_HPP
