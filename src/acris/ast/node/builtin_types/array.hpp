#ifndef ARRAY_HPP
#define ARRAY_HPP


// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::builtin_types {
// Aliases:
using container::TextPosition;
using node_traits::NodePosition;
using node_traits::UnaryOperator;

// Classes:
class Array : public NodePosition, public UnaryOperator {
  private:
  usz m_size;

  public:
  Array(TextPosition t_pos, NodePtr&& t_left, usz t_size);

  auto size() const -> usz;

  // AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(Array, NodePosition)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Array() = default;
};
} // namespace ast::node::builtin_types

// Cereal type registration:
// REGISTER_ARCHIVEABLE_TYPE(ast::node::user_types, Array);

#endif // ARRAY_HPP
