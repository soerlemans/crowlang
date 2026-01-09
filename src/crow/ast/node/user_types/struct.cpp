#include "struct.hpp"

namespace ast::node::user_types {
Struct::Struct(const std::string_view t_identifier, NodeListPtr&& t_body)
  : Identifier{t_identifier}, Body{std::move(t_body)}, TypeData{}
{}
} // namespace ast::node::user_types
