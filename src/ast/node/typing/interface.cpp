#include "interface.hpp"

namespace ast::node::typing {
Interface::Interface(const std::string_view t_identifier,
                     NodeListPtr&& t_methods)
  : Identifier{t_identifier}, m_methods{std::move(t_methods)}
{}

auto Interface::methods() -> NodeListPtr&
{
  return m_methods;
}
} // namespace ast::node::typing
