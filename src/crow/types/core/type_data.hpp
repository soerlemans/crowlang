#ifndef CROW_CROW_TYPES_CORE_TYPE_DATA_HPP
#define CROW_CROW_TYPES_CORE_TYPE_DATA_HPP

// Absolute Includes:
#include "crow/ast/node/node_interface.hpp"

// Local Includes:
#include "core_types.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace types::core {
/*!
 * Class for annotating the AST with type information.
 * This information is then later used during code generation.
 */
class TypeData : virtual public NodeInterface {
  protected:
  TypeVariant m_data;

  public:
  TypeData() = default;

  virtual auto set_type(TypeVariant t_data) -> void;
  virtual auto get_type() const -> const TypeVariant&;

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~TypeData() = default;
};
} // namespace types::core

#endif // CROW_CROW_TYPES_CORE_TYPE_DATA_HPP
