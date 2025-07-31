#include "mir.hpp"

// STL Includes:
#include <format>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>


// Absolute Includes:
#include "lib/stdexcept/stdexcept.hpp"
#include "lib/stdprint.hpp"

// Macros:
#define MATCH(t_key, t_value) \
  case Opcode::t_key:         \
    str = t_value;            \
    break

// Internal
namespace {
// TODO: Move to lib/?
template<typename T>
constexpr inline auto to_string(const T& t_elem) -> std::string
{
  std::ostringstream oss{};

  oss << t_elem;

  return oss.str();
}

} // namespace

namespace mir {
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
  using lib::stdexcept::throw_invalid_argument;

  std::string_view str{};

  switch(t_opcode) {
    // Literals:
    MATCH(CONST_F32, "const_f32");
    MATCH(CONST_F64, "const_f64");

    MATCH(CONST_INT, "const_int");

    // FIXME: Unused as of writing as we dont support suffix literals yet.
    // MATCH(CONST_I8, "const_i8");
    // MATCH(CONST_I16, "const_i16");
    // MATCH(CONST_I32, "const_i32");
    // MATCH(CONST_I64, "const_i64");
    // MATCH(CONST_ISIZE, "const_isize");

    // MATCH(CONST_UINT, "const_uint");
    // MATCH(CONST_U8, "const_u8");
    // MATCH(CONST_U16, "const_u16");
    // MATCH(CONST_U32, "const_u32");
    // MATCH(CONST_U64, "const_u64");
    // MATCH(CONST_USIZE, "const_usize");

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
    MATCH(INIT, "init");
    MATCH(UPDATE, "update");

    MATCH(LOAD, "load");
    MATCH(STORE, "store");
    MATCH(LEA, "lea");

    // Control Flow:
    MATCH(COND_JUMP, "cond_jmp");
    MATCH(JUMP, "jmp");
    MATCH(RETURN, "ret");

    MATCH(PHI, "phi");

    // High level control flow:
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
      throw_invalid_argument(
        "Opcode could not be converted to std::string_view.");
      break;
  }

  return str;
}
} // namespace mir

auto operator<<(std::ostream& t_os, const mir::Opcode t_op) -> std::ostream&
{
  t_os << mir::opcode2str(t_op);

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::Literal& t_val) -> std::ostream&
{
  std::visit(
    [&](auto&& t_value) {
      t_os << t_value << ":" << t_val.m_type;
    },
    t_val.m_value);

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::SsaVar& t_var) -> std::ostream&
{
  // TODO: Think about conditional printing of the type as well?

  t_os << std::format("%{}", t_var.m_id);

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::SsaVarPtr& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}

auto operator<<(std::ostream& t_os, const mir::Label& t_label) -> std::ostream&
{
  t_os << std::format("<{}>", t_label.label());

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::Operand& t_operand)
  -> std::ostream&
{
  auto print{[&](auto&& t_elem) {
    t_os << t_elem;
  }};

  std::visit(print, t_operand);

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::Instruction& t_inst)
  -> std::ostream&
{
  using mir::opcode2str;
  using mir::Operand;

  const auto& [id, opcode, operands, result, comment] = t_inst;

  // Format: "{id}: {result =} {opcode} {operand}, {operand}, {etc}"
  std::stringstream ss{};

  // If the result is present, prepend it to the opcode.
  std::string assign_str{};
  if(result) {
    assign_str = std::format("{} = ", to_string(*result));
  }

  const auto opcode_str{opcode2str(opcode)};
  ss << std::format("{}: {}{} ", id, assign_str, opcode_str);

  // Loop over operands and print them.
  std::string_view sep{};
  for(const Operand& operand : operands) {
    ss << sep << operand;

    sep = ", ";
  }

  // Add printing of a comment if not empty.
  if(!comment.empty()) {
    // We left align in a column of 80 characters.
    t_os << std::format("{:<80} ; {}", ss.view(), comment);
  } else {
    t_os << ss.view();
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::BasicBlock& t_bblock)
  -> std::ostream&
{
  using mir::Instruction;

  const auto& [label, instructions, _1, _2] = t_bblock;

  t_os << std::format("{}:\n", label);

  for(const Instruction& inst : instructions) {
    t_os << "\t" << inst << '\n';
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::Function& t_fn) -> std::ostream&
{
  using mir::BasicBlock;
  using mir::SsaVarPtr;

  const auto& [name, params, bblocks, return_type] = t_fn;

  t_os << std::format("function {}", name);

  t_os << '(';
  std::string_view sep{};
  for(const SsaVarPtr& ptr : params) {
    t_os << sep << ptr;

    sep = ", ";
  }
  t_os << ") -> " << return_type << '\n';

  // TODO: Print return type.

  for(const BasicBlock& bblock : bblocks) {
    t_os << bblock << "\n";
  }

  t_os << "}\n";

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::FunctionPtr& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}

auto operator<<(std::ostream& t_os, const mir::Module& t_mod) -> std::ostream&
{
  using mir::FunctionPtr;

  const auto& [name, functions] = t_mod;

  // Module declaration header.
  t_os << std::format("module {}\n\n", name);

  // Print the functions part of the module.
  std::string_view sep{};
  for(const FunctionPtr& fn : functions) {
    t_os << sep << fn;

    // Add a newline between functions.
    sep = "\n";
  }

  return t_os;
}

auto operator<<(std::ostream& t_os, const mir::ModulePtr& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}
