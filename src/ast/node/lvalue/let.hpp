#ifndef CROW_AST_NODE_LVALUE_LET_HPP
#define CROW_AST_NODE_LVALUE_LET_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::lvalue {
// Aliases:
namespace nt = node_traits;

// Classes:
class Let : public nt::Identifier, public nt::InitExpr {
  private:
  NodePtr m_init;

  public:
  Let(std::string_view t_identifier, NodePtr&& t_init);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Let() override = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_LVALUE_LET_HPP
