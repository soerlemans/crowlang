#ifndef CROW_AST_NODE_NODE_INTERFACE_HPP
#define CROW_AST_NODE_NODE_INTERFACE_HPP

// Library Includes:
#include <cereal/types/list.hpp>
#include <cereal/types/memory.hpp>

// Includes:
#include "../../lib/visitable/visitable.hpp"
#include "../visitor/node_visitor.hpp"

// Local Includes:
#include "archive_macros.hpp"
#include "fdecl.hpp"


namespace ast::node {
/*!
 * This is the root interface class that defines the fields each node must
 * have.
 */
class NodeInterface : public visitable::Visitable<visitor::NodeVisitor> {
  public:
  NodeInterface() = default;

	//! Utility method for automatically archiving traits.
  template<typename Archive, typename Derived, typename... Args>
  auto archive_traits(Archive& t_archive, Derived* t_derived) -> void
  {
    t_archive(cereal::base_class<Args>(t_derived)...);
  }

  virtual auto accept(visitor::NodeVisitor* t_visitor) -> visitable::Any = 0;

  virtual ~NodeInterface() = default;
};
} // namespace ast::node

#endif // CROW_AST_NODE_NODE_INTERFACE_HPP
