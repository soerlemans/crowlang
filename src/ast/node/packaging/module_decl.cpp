#include "module_decl.hpp"


using namespace ast::node::packaging;
using namespace ast::node::node_traits;

ModuleDecl::ModuleDecl(const std::string_view t_identifier)
  : Identifier{t_identifier}
{}
