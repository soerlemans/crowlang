#include "clir.hpp"

// STL Includes:
#include <format>
#include <stdexcept>
#include <string_view>

// Absolute Includes:
#include "lib/stdprint.hpp"

namespace clir {

// Macros:
#define MATCH(t_key, t_value) \
  case Opcode::t_key:         \
    str = t_value;            \
    break

// Methods:
// TODO: Move somewhere else.
auto Label::label() const -> std::string_view
{
  if(!m_target) {
    throw std::runtime_error{"Label points to nullptr"};
  }

  return m_target->m_label;
}

// Functions:
auto opcode2str(const Opcode t_opcode) -> std::string_view
{
  std::string_view str{};

  switch(t_opcode) {
    // Literals:
    MATCH(CONST_F32, "const_f32");
    MATCH(CONST_F64, "const_f64");

    MATCH(CONST_INT, "const_int");
    MATCH(CONST_I8, "const_i8");
    MATCH(CONST_I16, "const_i16");
    MATCH(CONST_I32, "const_i32");
    MATCH(CONST_I64, "const_i64");
    MATCH(CONST_ISIZE, "const_isize");

    MATCH(CONST_UINT, "const_uint");
    MATCH(CONST_U8, "const_u8");
    MATCH(CONST_U16, "const_u16");
    MATCH(CONST_U32, "const_u32");
    MATCH(CONST_U64, "const_u64");
    MATCH(CONST_USIZE, "const_usize");

    MATCH(CONST_STRING, "const_string");

    MATCH(CONST_BOOL, "const_bool");

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

auto operator<<(std::ostream& t_os, const clir::Literal& t_val) -> std::ostream&
{
  std::visit(
    [&](auto&& t_value) {
      t_os << t_value << ":" << t_val.m_type;
    },
    t_val.m_value);

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::SsaVar& t_var) -> std::ostream&
{
  t_os << std::format("%{}", t_var.m_id);

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::SsaVarPtr& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}

auto operator<<(std::ostream& t_os, const clir::Label& t_label) -> std::ostream&
{
  t_os << std::format("{}", t_label.label());

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Operand& t_operand)
  -> std::ostream&
{
  auto print{[&](auto&& t_elem) {
    t_os << t_elem;
  }};

  std::visit(print, t_operand);

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Instruction& t_inst)
  -> std::ostream&
{
  using clir::opcode2str;
  using clir::Operand;

  const auto& [id, opcode, operands, result] = t_inst;

  // If the result is present, prepend it to the opcode.
  std::stringstream assign_ss{};
  if(result) {
    assign_ss << *result << " = ";
  }

  const auto opcode_str{opcode2str(opcode)};
  t_os << std::format("{}: {}{} ", id, assign_ss.str(), opcode_str);

  // Loop over operands and print them.
  std::string_view sep{};
  for(const Operand& operand : operands) {
    t_os << sep << operand;

    sep = ", ";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::BasicBlock& t_bblock)
  -> std::ostream&
{
  using clir::Instruction;

  const auto& [label, instructions, _1, _2] = t_bblock;

  t_os << std::format("{}:\n", label);

  for(const Instruction& inst : instructions) {
    t_os << "\t" << inst << '\n';
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Function& t_fn) -> std::ostream&
{
  using clir::BasicBlock;

  const auto& [name, bblocks] = t_fn;

  t_os << std::format("function {} {{\n", name);

  // TODO: Print parameters.
  // TODO: Print return type.

  for(const BasicBlock& bblock : bblocks) {
    t_os << bblock << "\n";
  }

  t_os << "}\n";

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::Module& t_mod) -> std::ostream&
{
  using clir::Function;

  const auto& [name, functions] = t_mod;

  // Module declaration header.
  t_os << std::format("module {}\n\n", name);

  // Print the functions part of the module.
  for(const Function& fn : functions) {
    t_os << fn;
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const clir::ModulePtr& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}
