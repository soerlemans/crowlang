#ifndef CROW_CROW_AST_NODE_NODE_INTERFACE_HPP
#define CROW_CROW_AST_NODE_NODE_INTERFACE_HPP

// Includes:
#include "../archive/archive.hpp"
#include "../visitor/node_visitor.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node {
// Using Statements:
using visitor::Any;
using visitor::Visitable;

/*!
 * This is the root interface class that defines the fields each node must
 * have.
 */
class NodeInterface : public Visitable<visitor::NodeVisitor> {
  public:
  NodeInterface() = default;

  //! Utility method for automatically archiving traits.
  template<typename Archive, typename Derived, typename... Args>
  auto archive_traits(Archive& t_archive, Derived* t_derived) -> void
  {
    t_archive(cereal::base_class<Args>(t_derived)...);
  }

  // TODO: Add the node position trait as a must for node init.
  // This will be usefull later down the line for tracibility purposes.


  //! This is the pure virtual method that the visitor pattern relies on.
  virtual auto accept(visitor::NodeVisitor* t_visitor) -> Any = 0;

  virtual ~NodeInterface() = default;
};
} // namespace ast::node

#endif // CROW_CROW_AST_NODE_NODE_INTERFACE_HPP
