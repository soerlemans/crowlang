#ifndef CROW_AST_NODE_NODE_INTERFACE_HPP
#define CROW_AST_NODE_NODE_INTERFACE_HPP

// Library Includes:
#include <cereal/types/polymorphic.hpp>

// Includes:
#include "../../lib/visitable/visitable.hpp"
#include "../visitor/node_visitor.hpp"

// Local Includes:
#include "fdecl.hpp"


// Macros:
// TODO: Place these elsewhere (possibly in src/lib somewhere?).
#define CEREAL_FRIEND_DEF(t_type) \
  friend cereal::access;          \
                                  \
  template<typename Archive>      \
  friend void serialize(Archive& t_archive, t_type& t_this)


//!
#define GIVE_ARCHIVE_ACCESS(t_type) \
  t_type() = default;               \
                                    \
  CEREAL_FRIENDS_DEF(t_type)

//!
#define MAKE_NVP(t_type, t_member) \
  (cereal::make_nvp(#t_member, t_type.t_member))

//! Macro for making a type serializable by the cereal library.
#define MAKE_ARCHIVEABLE(t_type, ...)                \
  template<typename Archive>                         \
  void serialize(Archive& t_archive, t_type& t_this) \
  {                                                  \
    t_archive(__VA_ARGS__);                          \
  }                                                  \
  CEREAL_REGISTER_TYPE(t_type)

namespace ast::node {
/*!
 * This is the root interface class that defines the fields each node must
 * have.
 */
class NodeInterface : public visitable::Visitable<visitor::NodeVisitor> {
  public:
  NodeInterface() = default;

  virtual auto accept(visitor::NodeVisitor* t_visitor) -> visitable::Any = 0;

  //! Nothing to serialize in the base class.
  template<class Archive>
  auto serialize([[maybe_unused]] Archive& t_archive,
                 [[maybe_unused]] const unsigned int version) -> void
  {}

  virtual ~NodeInterface() = default;
};
} // namespace ast::node

#endif // CROW_AST_NODE_NODE_INTERFACE_HPP
