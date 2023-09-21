#ifndef CONST_HPP
#define CONST_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::lvalue {
// Aliases:
namespace nt = node_traits;

// Classes:
class Const : public nt::Identifier {
  private:
  NodePtr m_init;

  public:
  Const(std::string_view t_identifier, NodePtr&& t_init);

  auto init() -> NodePtr&;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Const() override = default;
};
} // namespace ast::node::lvalue

#endif // CONST_HPP
