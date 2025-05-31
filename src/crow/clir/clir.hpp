#ifndef CLIR_HPP
#define CLIR_HPP

/*!
 * @file CLIR is short for CrowLang Intermediate Representation.
 * We implement the IR as a series of structs that closely mimic the AST.
 * And its layout.
 */

// STL Includes:
#include <vector>

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
  // Arithmetic
  Addition,
  Subtraction,
  Multiplication,
  Division,

  // Comparison
  LessThan,
  LessThanEqual,
  Equal,
  NotEqual,
  GreaterThan,
  GReaterThanEqual,

	// Logical

	//
  Load,
  Store,

	// Control Flow:
  ConditionalBranch,
  Goto,
  Return
};

enum class ValueType {

};

// Structs:
struct Value {
  u64 m_id; // SSA-style temp.
  std::string m_type;
};

struct Instruction {
  Opcode m_opcode;
  ValueSeq m_operands;
  Value m_result;
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
} // namespace clir

#endif // CLIR_HPP
