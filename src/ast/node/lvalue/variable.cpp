#include "variable.hpp"


using namespace ast::node::lvalue;
using namespace ast::node::node_traits;

Variable::Variable(const std::string_view t_identifier)
  : Identifier{t_identifier}, Type{""}
{}

Variable::Variable(std::string_view t_identifier, std::string_view t_type)
  : Identifier{t_identifier}, Type{t_type}
{}
