#include "dot_expr.hpp"


using namespace ast::node::typing;
using namespace ast::node::node_traits;

DotExpr::DotExpr(const std::string_view t_identifier, NodePtr&& t_expr)
  : Identifier{t_identifier}, Expr{std::move(t_expr)}
{}
