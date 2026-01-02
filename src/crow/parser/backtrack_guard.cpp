#include "backtrack_guard.hpp"

namespace parser {
BacktrackGuard::BacktrackGuard(TokenStream& t_stream, NodePtr& t_node)
  : m_stream{t_stream}, m_iter{t_stream.iter()}, m_node{t_node}
{}

BacktrackGuard::~BacktrackGuard()
{
  if(!m_node) {
    m_stream.set(m_iter);
  }
}
} // namespace parser::pratt
