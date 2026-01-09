#include "address_of.hpp"

// STL Includes:
#include <exception>

namespace ast::node::operators {
// Using Declarations:
using token::TokenType;

// Methods:
AddressOf::AddressOf(NodePtr&& t_left): UnaryOperator{std::move(t_left)}
{}
} // namespace ast::node::operators
