#ifndef ATTRIBUTE_DATA_HPP
#define ATTRIBUTE_DATA_HPP

// STL Include:
#include <string>
#include <string_view>

// Absolute Includes:
#include "crow/ast/node/node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::node_traits {
// Structs:
// struct AttributeSpec {
//   std::string t_identifier;
//   TODO:
// };

// Classes:
/*!
 * Class for annotating the AST with attribute information.
 * This is necessary, for when need the attribute information on hand.
 * When generating code, or translating to IR.
 */
class AttributeData : virtual public NodeInterface {
  public:
  AttributeData() = default;

  // virtual auto set_attribute() -> void;
  // virtual auto get_attribute() const -> const TypeVariant&;

  // AST_ARCHIVE_MAKE_ARCHIVEABLE(AttributeData)
  // {
  //   t_archive(CEREAL_NVP(m_args));
  // }

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~AttributeData() = default;
};
} // namespace ast::node::node_traits

// Cereal register type:
// REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, AttributeData);

#endif // ATTRIBUTE_DATA_HPP
