#include "clir.hpp"

// STL Includes:
#include <stdexcept>
#include <string_view>

namespace clir {

// Macros:
#define MATCH(t_key, t_value) \
  case ComparisonOp::t_key:   \
    str = t_value;            \
    break

// Functions:
auto opcode2str(const Opcode t_opcode) -> std::string_view
{
  std::string_view str{};

  switch(t_opcode) {
    default:
      throw std::invalid_argument{
        "opcode2str(): Opcode could not be converted to std::string_view."};
      break;
  }

  return str;
}

} // namespace clir
