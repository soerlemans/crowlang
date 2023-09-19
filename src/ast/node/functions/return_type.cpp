#include "return_type.hpp"


using namespace ast::node::functions;
using namespace ast::node::node_traits;

ReturnType::ReturnType(const std::string_view t_type): Type{t_type}
{}
