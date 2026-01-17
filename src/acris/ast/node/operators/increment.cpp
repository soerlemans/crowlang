#include "increment.hpp"

namespace ast::node::operators {
Increment::Increment(NodePtr&& t_left): UnaryOperator{std::move(t_left)}
{}
} // namespace ast::node::operators
