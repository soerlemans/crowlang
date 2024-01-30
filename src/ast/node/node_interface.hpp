#ifndef CROW_AST_NODE_NODE_INTERFACE_HPP
#define CROW_AST_NODE_NODE_INTERFACE_HPP

// Library Includes:
#include <cereal/types/memory.hpp>

// Includes:
#include "../../lib/visitable/visitable.hpp"
#include "../visitor/node_visitor.hpp"

// Local Includes:
#include "fdecl.hpp"


// Macros:
// TODO: Move these cereal related macros somewhere else?
/*!
 * Make it so that only cereal has access to the default constructor.
 * Most node types should not be default constructible.
 */
#define GIVE_ARCHIVE_ACCESS(t_type) \
  protected:                        \
  t_type() = default;               \
                                    \
  friend cereal::access

//! Macro for making a type serializable by the cereal library.
#define MAKE_ARCHIVEABLE(t_type) \
  GIVE_ARCHIVE_ACCESS(t_type);   \
                                 \
  public:                        \
  template<typename Archive>     \
  auto serialize(Archive& t_archive)->void


//!
#define REGISTER_ARCHIVEABLE_TYPE(t_namespace, t_type)           \
  CEREAL_REGISTER_POLYMORPHIC_RELATION(ast::node::NodeInterface, \
                                       t_namespace::t_type);     \
  CEREAL_REGISTER_TYPE_WITH_NAME(t_namespace::t_type, #t_type)


namespace ast::node {
/*!
 * This is the root interface class that defines the fields each node must
 * have.
 */
class NodeInterface : public visitable::Visitable<visitor::NodeVisitor> {
  public:
  NodeInterface() = default;

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
