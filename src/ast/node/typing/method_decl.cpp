#include "method_decl.hpp"


using namespace ast::node::typing;
using namespace ast::node::node_traits;

MethodDecl::MethodDecl(const std::string_view t_identifier,
                       NodeListPtr&& t_params, NodePtr&& t_type)
  : Identifier{t_identifier},
    Params{std::move(t_params)},
    TypeExpr{std::move(t_type)}
{}
