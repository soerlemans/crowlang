#ifndef CROW_AST_NODE_TYPING_STRUCT_HPP
#define CROW_AST_NODE_TYPING_STRUCT_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Aliases:
namespace nt = node_traits;

// Classes:
class Struct : public nt::Identifier, public nt::Body {

  public:
  Struct(std::string_view t_identifier, NodeListPtr&& t_body);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Struct() = default;
};
} // namespace ast::node::typing

#endif // CROW_AST_NODE_TYPING_STRUCT_HPP
