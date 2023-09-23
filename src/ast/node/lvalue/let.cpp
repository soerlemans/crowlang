#include "let.hpp"


using namespace ast::node::lvalue;
using namespace ast::node::node_traits;

Let::Let(const std::string_view t_identifier, NodePtr&& t_init)
  : Identifier{t_identifier}, InitExpr{std::move(t_init)}
{}
