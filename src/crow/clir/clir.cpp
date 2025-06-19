#include "clir.hpp"

// STL Includes:
#include <stdexcept>
#include <string_view>

namespace clir {

// Macros:
#define MATCH(t_key, t_value) \
  case Opcode::t_key:         \
    str = t_value;            \
    break

// Functions:
auto opcode2str(const Opcode t_opcode) -> std::string_view
{
  std::string_view str{};

  switch(t_opcode) {
    // Integer arithmetic:
    MATCH(IADD, "iadd");
    MATCH(ISUB, "isub");
    MATCH(IMUL, "imul");
    MATCH(IDIV, "idiv");
    MATCH(INEG, "ineg");

    // Integer comparison:
    MATCH(ICMP_LT, "icmp_lt");
    MATCH(ICMP_LTE, "icmp_lte");
    MATCH(ICMP_EQ, "icmp_eq");
    MATCH(ICMP_NQ, "icmp_nq");
    MATCH(ICMP_GT, "icmp_gt");
    MATCH(ICMP_GTE, "icmp_gte");

    // Float arithmetic:
    MATCH(FADD, "fadd");
    MATCH(FSUB, "fsub");
    MATCH(FMUL, "fmul");
    MATCH(FDIV, "fdiv");
    MATCH(FNEG, "fneg");

    // Float comparison:
    MATCH(FCMP_LT, "fcmp_lt");
    MATCH(FCMP_LTE, "fcmp_lte");
    MATCH(FCMP_EQ, "fcmp_eq");
    MATCH(FCMP_NQ, "fcmp_nq");
    MATCH(FCMP_GT, "fcmp_gt");
    MATCH(FCMP_GTE, "fcmp_gte");

    default:
      throw std::invalid_argument{
        "opcode2str(): Opcode could not be converted to std::string_view."};
      break;
  }

  return str;
}

} // namespace clir
