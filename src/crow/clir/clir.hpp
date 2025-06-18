#ifndef CROW_CROW_CLIR_CLIR_HPP
#define CROW_CROW_CLIR_CLIR_HPP

/*!
 * @file CLIR is short for CrowLang Intermediate Representation.
 * We implement the IR as a series of structs that closely mimic the AST.
 * And its layout.
 */

// STL Includes:
#include <vector>
#include <ostream>

// Absolute Includes:
#include "lib/types.hpp"

namespace clir {
// Forward Declarations:
struct Value;
struct Instruction;
struct BasicBlock;

// Aliases:
using ValueSeq = std::vector<Value>;
using InstructionSeq = std::vector<Instruction>;
using BasicBlockSeq = std::vector<BasicBlock>;
using CfgSeq = std::vector<BasicBlock*>;

// Enums:
enum class Opcode {
  // Arithmetic:
  Addition,
  Subtraction,
  Multiplication,
  Division,
  Remainder,

  // I have no clue what im doing with this IR, so I just need to write stuff.
  // And figure everything out in hindsight.
  Assign,
  Trunc,


  // Comparison:
  LessThan,
  LessThanEqual,
  Equal,
  NotEqual,
  GreaterThan,
  GReaterThanEqual,

  // Logical:
  And,
  Or,
  Not,

  // Memory handling:
  Load,
  Store,
  Alloca,
  AddressOf,
  Deref,

  // Control Flow:
  ConditionalBranch,
  Goto,
  Break,
  Continue,
  Return,

  Switch, // Jump table.

  // High level control flow:
  If,
  Loop,
  Match,

  Nop,
};

enum class ValueType {
  STRING,
  BOOLEAN,
  INTEGER,
  FLOAT,
  VOID
};

// Structs:
struct Operand {
  u64 m_id; // SSA-style temp.
  std::string m_type;
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
  BasicBlockSeq blocks;
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
auto operator<<(std::ostream& t_os, const clir::BasicBlock& t_inst)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Function& t_inst)
  -> std::ostream&;

#endif // CROW_CROW_CLIR_CLIR_HPP
