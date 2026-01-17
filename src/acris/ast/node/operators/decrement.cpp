#include "decrement.hpp"

namespace ast::node::operators {
Decrement::Decrement(NodePtr&& t_left): UnaryOperator{std::move(t_left)}
{}
} // namespace ast::node::operators
