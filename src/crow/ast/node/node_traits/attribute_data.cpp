#include "attribute_data.hpp"

namespace ast::node::node_traits {
// Methods:
AttributeData::AttributeData()
  : m_attr{AttributeType::NO_ATTRIBUTE, std::string{}, AttributeArgs{}}
{}

auto AttributeData::set_attribute(const AttributeMetadata& t_attr) -> void
{
  m_attr = t_attr;
}

auto AttributeData::set_attribute(std::string_view t_identifier,
                                  const AttributeArgs& t_args) -> void
{
  const auto type{str2attribute_type(t_identifier)};

  m_attr = {type, std::string{t_identifier}, t_args};
}

auto AttributeData::get_attribute() const -> const AttributeMetadata&
{
  return m_attr;
}

auto AttributeData::is_attribute_set() -> bool
{
  return (m_attr.m_type != AttributeType::NO_ATTRIBUTE);
}

// Functions:
auto str2attribute_type(std::string_view t_str) -> AttributeType
{
  auto type{AttributeType::NO_ATTRIBUTE};

  if(t_str.empty()) {
    // An empty string means no attribute is provided.
    return type;
  }

  // Builtin attributes:
  if(t_str == "inline") {
    type = AttributeType::INLINE;
  } else if(t_str == "deprecated") {
    type = AttributeType::DEPRECATED;
  } else if(t_str == "extern") {
    type = AttributeType::EXTERN;
  } else {
    // If we dont recognize, any of the builtin types
    type = AttributeType::UNKNOWN;
  }

  return type;
}
} // namespace ast::node::node_traits
