#include "list.hpp"

namespace ast::node {
auto List::begin() -> NodeList::iterator
{
  return m_list.begin();
}

auto List::end() -> NodeList::iterator
{
  return m_list.end();
}

auto List::empty() -> bool
{
  return m_list.empty();
}

auto List::size() -> std::size_t
{
  return m_list.size();
}

auto List::push_front(NodePtr&& t_ptr) -> void
{
  m_list.push_front(std::move(t_ptr));
}

auto List::push_back(NodePtr&& t_ptr) -> void
{
  m_list.push_back(std::move(t_ptr));
}
} // namespace ast::node
