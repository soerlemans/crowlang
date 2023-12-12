#include "function.hpp"


using namespace ast::node::function;
using namespace ast::node::node_traits;

Function::Function(const std::string_view t_identifier, NodeListPtr&& t_params,
                   const std::string_view t_type, NodeListPtr&& t_body)
  : Identifier{t_identifier},
    Params{std::move(t_params)},
    TypeAnnotation{t_type},
    Body{std::move(t_body)}
{}
