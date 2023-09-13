#include "return.hpp"


using namespace ast::node::control;
using namespace ast::node::node_traits;

Return::Return(NodePtr&& t_expr): Expr{std::move(t_expr)}
{}
