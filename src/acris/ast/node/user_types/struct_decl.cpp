#include "struct_decl.hpp"

namespace ast::node::user_types {
StructDecl::StructDecl(const std::string_view t_identifier)
  : Identifier{t_identifier}
{}
} // namespace ast::node::user_types
