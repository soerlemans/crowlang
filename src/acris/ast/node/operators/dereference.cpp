#include "dereference.hpp"

namespace ast::node::operators {
// Methods:
Dereference::Dereference(NodePtr&& t_left): UnaryOperator{std::move(t_left)}
{}
} // namespace ast::node::operators
