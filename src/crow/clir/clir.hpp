#ifndef CLIR_HPP
#define CLIR_HPP

/*!
 * @file CLIR is short for CrowLang Intermediate Representation.
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
  Add,
  Sub,
  Mul,
  Div,
  Ret
};

enum class LiteralType {
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
  std::string m_name;
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
