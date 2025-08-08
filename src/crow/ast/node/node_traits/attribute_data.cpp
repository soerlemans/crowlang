#include "attribute_data.hpp"

// STL Includes:
#include <iomanip>

// Absolute Includes:
#include "lib/stdexcept/stdexcept.hpp"

// Macros:
#define MATCH(t_key, t_value) \
  case AttributeType::t_key:  \
    str = t_value;            \
    break

namespace ast::node::node_traits {
AttributeMetadata::AttributeMetadata()
  : m_type{AttributeType::NO_ATTRIBUTE}, m_identifier{}, m_args{}
{}

AttributeMetadata::AttributeMetadata(const std::string_view t_identifier,
                                     AttributeArgs&& t_args)
  : m_type{str2attribute_type(t_identifier)},
    m_identifier{std::string{t_identifier}},
    m_args{std::move(t_args)}
{}

// Methods:
AttributeData::AttributeData(): m_attr{std::string{}, AttributeArgs{}}
{}

auto AttributeData::set_attribute(const AttributeMetadata& t_attr) -> void
{
  m_attr = t_attr;
}

auto AttributeData::set_attribute(std::string_view t_identifier,
                                  AttributeArgs t_args) -> void
{
  const auto type{str2attribute_type(t_identifier)};

  m_attr = AttributeMetadata{t_identifier, std::move(t_args)};
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
auto attribute_type2str(AttributeType t_type) -> std::string_view
{
  std::string_view str{};

  switch(t_type) {
    MATCH(NO_ATTRIBUTE, "no_attribute");
    MATCH(INLINE, "inline");
    MATCH(DEPRECATED, "deprecated");
    MATCH(EXTERN, "extern");
    MATCH(UNKNOWN, "unknown");

    default: {
      using lib::stdexcept::throw_invalid_argument;

      throw_invalid_argument(
        "Unhandled AttributeType cant be converted to string.");
      break;
    }
  }

  return str;
}

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

// Functions:
auto operator<<(std::ostream& t_os,
                const ast::node::node_traits::AttributeType t_type)
  -> std::ostream&
{
  using ast::node::node_traits::attribute_type2str;

  t_os << attribute_type2str(t_type);

  return t_os;
}

auto operator<<(std::ostream& t_os,
                const ast::node::node_traits::AttributeMetadata& t_data)
  -> std::ostream&
{
  const auto& [type, id, args] = t_data;

  t_os << "(" << type << ":" << std::quoted(id) << ")";

  return t_os;
}
