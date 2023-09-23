#ifndef CROW_AST_NODE_TYPING_DEF_BLOCK_HPP
#define CROW_AST_NODE_TYPING_DEF_BLOCK_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Aliases:
namespace nt = node_traits;

// Classes:
class DefBlock : public nt::Identifier, public nt::Body {
  public:
  DefBlock(std::string_view t_identifier, NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~DefBlock() override = default;
};
} // namespace ast::node::typing

#endif // CROW_AST_NODE_TYPING_DEF_BLOCK_HPP
