#include "interface.hpp"


using namespace ast::node::typing;
using namespace ast::node::node_traits;

Interface::Interface(const std::string_view t_identifier, NodeListPtr&& t_body)
  : Identifier{t_identifier}, Body{std::move(t_body)}
{}
