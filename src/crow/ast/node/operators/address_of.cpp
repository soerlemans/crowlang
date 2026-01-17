#include "address_of.hpp"

namespace ast::node::operators {
// Methods:
AddressOf::AddressOf(NodePtr&& t_left): UnaryOperator{std::move(t_left)}
{}
} // namespace ast::node::operators
