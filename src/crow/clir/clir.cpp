#include "clir.hpp"

// STL Includes:
#include <format>
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

    // Memory handling:
    MATCH(ASSIGN, "assign");
    MATCH(LOAD, "load");
    MATCH(STORE, "store");
    MATCH(LEA, "lea");

    // Control Flow:
    MATCH(COND_JUMP, "cond_jmp");
    MATCH(JUMP, "jmp");
    MATCH(RETURN, "ret");

    MATCH(PHI, "phi");

    // High level control flow:
    MATCH(IF, "if");
    MATCH(ELSE, "else");
    MATCH(LOOP, "loop");
    MATCH(MATCH, "match");
    MATCH(SWITCH, "switch");

    // Struct operations:
    MATCH(CONSTRUCT, "construct");
    MATCH(INSERT, "insert");
    MATCH(EXTRACT, "extract");

    MATCH(CALL, "call");

    MATCH(NOP, "nop");

    default:
      throw std::invalid_argument{
        "opcode2str(): Opcode could not be converted to std::string_view."};
      break;
  }

  return str;
}
} // namespace clir

auto operator<<(std::ostream& t_os, const clir::Opcode t_op) -> std::ostream&
{
  t_os << clir::opcode2str(t_op);

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Value& t_val) -> std::ostream&
{
  t_os << std::format("v{}", t_val.m_id);

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Operand& t_operand)
  -> std::ostream&
{
  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Instruction& t_inst)
  -> std::ostream&
{
  using clir::opcode2str;
  using clir::Value;

  const auto& [id, opcode, operands] = t_inst;

  const auto str{opcode2str(opcode)};
  t_os << std::format("{}: %{} ", id, str);

  // Loop over operands and print them.
  std::string_view sep{};
  for(const Value& val : operands) {
    t_os << sep << val;

    sep = ", ";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::BasicBlock& t_bblock)
  -> std::ostream&
{
  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Function& t_fn) -> std::ostream&
{
  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Module& t_mod) -> std::ostream&
{
  return t_os;
}
