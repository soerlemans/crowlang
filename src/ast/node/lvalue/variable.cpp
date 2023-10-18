#include "variable.hpp"


using namespace ast::node::lvalue;
using namespace ast::node::node_traits;

Variable::Variable(ct::TextPosition t_pos, const std::string_view t_identifier)
  : NodePosition{std::move(t_pos)}, Identifier{t_identifier}, Type{""}
{}

Variable::Variable(ct::TextPosition t_pos, std::string_view t_identifier,
                   std::string_view t_type)
  : NodePosition{std::move(t_pos)}, Identifier{t_identifier}, Type{t_type}
{}
