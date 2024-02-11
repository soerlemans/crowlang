#include "unary_prefix.hpp"


namespace ast::node::operators {
UnaryPrefix::UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left)
  : Op{t_op}, UnaryOperator{std::move(t_left)}
{}
} // namespace ast::node::operators
