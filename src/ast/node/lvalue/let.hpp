#ifndef CROW_AST_NODE_LVALUE_LET_HPP
#define CROW_AST_NODE_LVALUE_LET_HPP

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
  protected:
  // GIVE_ARCHIVE_ACCESS(Let);

  public:
  Let(TextPosition t_pos, std::string_view t_identifier,
      std::string_view t_type, NodePtr&& t_init);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Let() = default;
};
} // namespace ast::node::lvalue

// MAKE_ARCHIVEABLE(ast::node::lvalue::Let, MAKE_NVP(t_this, m_identifier),
//                  MAKE_NVP(t_this, m_type), MAKE_NVP(t_this, m_init));

#endif // CROW_AST_NODE_LVALUE_LET_HPP
