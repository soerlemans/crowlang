#include "return_type.hpp"


using namespace ast::node::functions;
using namespace ast::node::node_traits;

ReturnType::ReturnType(NodePtr&& t_type): TypeExpr{std::move(t_type)}
{}
