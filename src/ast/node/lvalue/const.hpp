#ifndef CROW_AST_NODE_LVALUE_CONST_HPP
#define CROW_AST_NODE_LVALUE_CONST_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::lvalue {
// Aliases:
namespace nt = node_traits;
namespace ct = container;

// Classes:
class Const : public nt::DeclExpr {
  private:
  NodePtr m_init;

  public:
  Const(ct::TextPosition t_pos, std::string_view t_identifier,
        std::string_view t_str, NodePtr&& t_init);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Const() = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_LVALUE_CONST_HPP
