#include "return_type.hpp"

namespace ast::node::function {
ReturnType::ReturnType(NodePtr&& t_type): TypeAnnotation{std::move(t_type)}
{}
} // namespace ast::node::function
