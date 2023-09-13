#include "interface.hpp"


using namespace ast::node::typing;
using namespace ast::node::node_traits;

Interface::Interface(const std::string_view t_identifier,
                     NodeListPtr&& t_methods)
  : Identifier{t_identifier}, m_methods{std::move(t_methods)}
{}
