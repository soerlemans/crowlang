#include "module_decl.hpp"


namespace ast::node::packaging {
ModuleDecl::ModuleDecl(const std::string_view t_identifier)
  : Identifier{t_identifier}
{}
} // namespace ast::node::packaging
