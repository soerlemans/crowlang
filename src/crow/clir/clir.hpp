#ifndef CROW_CROW_CLIR_CLIR_HPP
#define CROW_CROW_CLIR_CLIR_HPP

/*!
 * @file CLIR is short for CrowLang Intermediate Representation.
 * We implement the IR as a series of structs that closely mimic the AST.
 * And its layout.
 */

// STL Includes:
#include <ostream>
#include <vector>

// Absolute Includes:
#include "lib/types.hpp"

namespace clir {
// Forward Declarations:
struct Value;
struct Instruction;
struct BasicBlock;
struct Function;
struct Module;


// Aliases:
using ValueSeq = std::vector<Value>;
using CfgSeq = std::vector<BasicBlock*>;
using InstructionSeq = std::vector<Instruction>;
using BasicBlockSeq = std::vector<BasicBlock>;
using FunctionSeq = std::vector<Function>;
using ModuleSeq = std::vector<Module>;

// Enums:
// I have no clue what im doing with this IR, so I just need to write stuff.
// And figure everything out in hindsight.
enum class Opcode {
  // Integer arithmetic:
  IADD,
  ISUB,
  IMUL,
  IDIV,
  IMOD,
  INEG,

  // Integer comparison:
  ICMP_LT,
  ICMP_LTE,
  ICMP_EQ,
  ICMP_NQ,
  ICMP_GT,
  ICMP_GTE,

  // Float Arithmetic:
  FADD,
  FSUB,
  FMUL,
  FDIV,
  FNEG,

  // Float Comparison:
  FCMP_LT,
  FCMP_LTE,
  FCMP_EQ,
  FCMP_NQ,
  FCMP_GT,
  FCMP_GTE,

  // Trunc, // Trunc an integer, maybe use??

  // Memory handling:
  // clang-format off
  ASSIGN,    // %assign <dest> <src> ; dest = src.
  LOAD,      // %load <dest> <src> ; dest = *src.
  STORE,     // %store <dest> <src> ; *dest = src.
  ALLOCA,    // %alloca ; Allocate memory on the heap.
  LEA,       // %lea <dest> <src> ; dest = &src Load a calculated address, like load effective address.
  // clang-format on

  // Control Flow:
  COND_JUMP, // %cond_jmp <condition> <label_true> <label_false>
  JUMP,      // %jmp <label>
  RETURN,    // %ret

  // SSA specific, select value based on the control path.
  PHI,

  // Struct operations:
  CONSTRUCT,
  INSERT,
  EXTRACT,

  SWITCH, // Jump table.

  // High level control flow:
  IF,
  ELSE,
  LOOP,
  MATCH,

  // Call a function.
  CALL,

  NOP,
};

enum class ValueType {
  // TODO: Maybe use NativeType map?
  // Also need to add support for structs.
  // Also support for aliases.
  // Also support for pointers.
  STRING,
  BOOLEAN,
  INTEGER,
  FLOAT,
  VOID
};

struct Value {
  u64 m_id;
  // std::string m_name; // Name of a struct or alias.
  ValueType m_type;
};

// Structs:
struct Operand {
  u64 m_id; // SSA-style temp.
  Value m_value;
};

struct Instruction {
  u64 m_id;
  Opcode m_opcode;
  ValueSeq m_operands;
  Operand m_result;
};

struct BasicBlock {
  std::string m_label;
  InstructionSeq m_instructions;

  CfgSeq m_successors;
  CfgSeq m_predecessors;
};

struct Function {
  std::string name;
  // TODO: Sequence of parameters.
  BasicBlockSeq blocks;
};

struct Module {
  FunctionSeq m_functions;
};

// Functions:
auto opcode2str(Opcode t_opcode) -> std::string_view;

} // namespace clir

// Functions:
auto operator<<(std::ostream& t_os, const clir::Opcode& t_op) -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Operand& t_operand)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Instruction& t_inst)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::BasicBlock& t_bblock)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Function& t_fn)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Module& t_mod) -> std::ostream&;

#endif // CROW_CROW_CLIR_CLIR_HPP
