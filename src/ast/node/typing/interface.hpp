#ifndef CROW_AST_NODE_TYPING_INTERFACE_HPP
#define CROW_AST_NODE_TYPING_INTERFACE_HPP


// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::typing {
// Aliases:
namespace nt = node_traits;

// Classes:
class Interface : public nt::Identifier, nt::Body {
  public:
  Interface(std::string_view t_identifier, NodeListPtr&& t_body);

  ~Interface() override = default;
};
} // namespace ast::node::typing

#endif // CROW_AST_NODE_TYPING_INTERFACE_HPP
