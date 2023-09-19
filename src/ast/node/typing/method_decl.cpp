#include "method_decl.hpp"


using namespace ast::node::typing;
using namespace ast::node::node_traits;

MethodDecl::MethodDecl(const std::string_view t_identifier,
                       NodeListPtr&& t_params, const std::string_view t_type)
  : Identifier{t_identifier}, Params{std::move(t_params)}, Type{t_type}
{}
