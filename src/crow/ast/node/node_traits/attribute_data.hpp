#ifndef CROW_CROW_AST_NODE_NODE_TRAITS_ATTRIBUTE_DATA_HPP
#define CROW_CROW_AST_NODE_NODE_TRAITS_ATTRIBUTE_DATA_HPP

// STL Include:
#include <string>
#include <string_view>
#include <vector>

// Absolute Includes:
#include "crow/ast/node/node_interface.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::node_traits {
// Aliases:
using AttributeArgs = std::vector<std::string>;

// Enums:
enum class AttributeType {
  NO_ATTRIBUTE, //!< If no attribute is given.

  // Common builtin
  INLINE,
  DEPRECATED,
  EXTERN,

  UNKNOWN //!< Reserved for third party attributes.
};

// Structs:
/*!
 * Holds the metadata which we annotate the AST with.
 */
struct AttributeMetadata {
  //! Determines what behavior should be classified.
  AttributeType m_type;

  // Raw data.
  std::string m_identifier;
  AttributeArgs m_args;
};

// Classes:
/*!
 * Class for annotating the AST with attribute information.
 * This is necessary, for when need the attribute information on hand.
 * When generating code, or translating to IR.
 */
class AttributeData : virtual public NodeInterface {
  private:
  AttributeMetadata m_attr;

  public:
  AttributeData();

  virtual auto set_attribute(const AttributeMetadata&) -> void;
  virtual auto set_attribute(std::string_view t_identifier,
                             const AttributeArgs& t_args) -> void;

  virtual auto get_attribute() const -> const AttributeMetadata&;

  virtual auto is_attribute_set() -> bool;

  // AST_ARCHIVE_MAKE_ARCHIVEABLE(AttributeData)
  // {
  //   t_archive(CEREAL_NVP(m_args));
  // }

  AST_VISITOR_VISITABLE_PURE_ACCEPT(visitor::NodeVisitor);

  virtual ~AttributeData() = default;
};

// Functions:
auto str2attribute_type(std::string_view t_str) -> AttributeType;
} // namespace ast::node::node_traits

// Cereal register type:
// REGISTER_ARCHIVEABLE_TYPE(ast::node::node_traits, AttributeData);

#endif // CROW_CROW_AST_NODE_NODE_TRAITS_ATTRIBUTE_DATA_HPP
