#ifndef CROW_CROW_CLIR_CLIR_HPP
#define CROW_CROW_CLIR_CLIR_HPP

/*!
 * @file CLIR is short for CrowLang Intermediate Representation.
 * We implement the IR as a series of structs that closely mimic the AST.
 * And its layout.
 */

// STL Includes:
#include <list>
#include <memory>
#include <ostream>
#include <variant>
#include <vector>

// Absolute Includes:
#include "crow/ast/node/node_traits/typing/typing.hpp"
#include "lib/types.hpp"

namespace clir {
// Forward Declarations:
struct Literal;
struct SsaVar;
struct Label;
struct Instruction;
struct BasicBlock;
struct Function;
struct Module;

// Aliases:
using ast::node::node_traits::typing::NativeType;

// We use lists for instructions and basic blocks.
// This is to prevent any iterator or reference invalidation.
// During the building of the IR.
// Or the modifying of it afterwards.
using CfgSeq = std::list<BasicBlock*>;
using InstructionSeq = std::list<Instruction>;
using BasicBlockSeq = std::list<BasicBlock>;
using FunctionSeq = std::list<Function>;
using ModuleSeq = std::list<Module>;

using ModulePtr = std::shared_ptr<Module>;

using Operand = std::variant<Literal, SsaVar, Label>;
using OperandSeq = std::vector<Operand>;

using SsaVarPtr = std::shared_ptr<SsaVar>;

using BasicBlockIter = BasicBlockSeq::iterator;
using FunctionIter = FunctionSeq::iterator;


// Enums:
// I have no clue what im doing with this IR, so I just need to write stuff.
// And figure everything out in hindsight.
/*!
 * The opcodes which are supported for IR.
 */
enum class Opcode : u32 {
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
  FDIV, // %<dest> = fdiv <src> <div>
  FNEG, // %<dest> = fneg <src>

  // Float Comparison:
  FCMP_LT,  // %<dest> = fcmp_lt <lhs> <rhs>
  FCMP_LTE, // %<dest> = fcmp_lte <lhs> <rhs>
  FCMP_EQ,  // %<dest> = fcmp_eq <lhs> <rhs>
  FCMP_NQ,  // %<dest> = fcmp_nq <lhs> <rhs>
  FCMP_GT,  // %<dest> = fcmp_gt <lhs> <rhs>
  FCMP_GTE, // %<dest> = fcmp_gte <lhs> <rhs>

  // Trunc, // Trunc an integer, maybe use??

  // Memory handling:
  // clang-format off
  ASSIGN,    // %<dest> = assign <src> ; dest = src.
  LOAD,      // %<dest> = load <src> ; dest = *src.
  STORE,     // %<dest> = store <src> ; *dest = src.
  ALLOCA,    // %<dest> = alloca <count>; Allocate memory on the heap.
  LEA,       // %<dest> = lea <src> ; dest = &src Load a calculated address, like load effective address.
  // clang-format on

  // Control Flow:
  COND_JUMP, // cond_jmp <condition> <label_true> <label_false>
  JUMP,      // jmp <label>
  CONTINUE,  // continue
  BREAK,     // break
  RETURN,    // ret %<var>

  // SSA specific, select Literal based on the control path.
  PHI,

  // High level control flow:
  IF, // if <condition> <label_true> <label_false>
  ELSE,
  LOOP, // Maybe just call it a while? (for wont exist).
  MATCH,
  SWITCH, // Jump table.

  // Struct operations:
  CONSTRUCT,
  INSERT,
  EXTRACT,

  // Call a function.
  CALL,

  NOP,
};

enum class SsaVarType {
  SSA,      // Temporary SSA variable that is being referenced.
  GLOBAL,   // Global variable reference.
  AGGREGATE // Struct or other high level data structure.
};

// Structs:
struct Literal {
  u64 m_id;
  NativeType m_type;
};

struct SsaVar {
  u64 m_id;

	// TODO: Embed typing information from 
  std::string m_name; // Name of a struct or alias.
};

//! Used for jump operations.
struct Label {
  BasicBlock* m_target;

  auto label() const -> std::string_view;
};

struct Instruction {
  u64 m_id;
  Opcode m_opcode;
  OperandSeq m_operands;

  SsaVarPtr m_result;
};

struct BasicBlock {
  std::string m_label;
  InstructionSeq m_instructions;

  // TODO: The control flow graphs, should maybe be a map keyed by label?
  CfgSeq m_successors;
  CfgSeq m_predecessors;
};

struct Function {
  std::string m_name;
  // TODO: Sequence of parameters.
  // TODO: Include return type.
  BasicBlockSeq m_blocks;
};

struct Module {
  std::string m_name;
  FunctionSeq m_functions;
};

// Functions:
auto opcode2str(Opcode t_opcode) -> std::string_view;
} // namespace clir

// Functions:
auto operator<<(std::ostream& t_os, const clir::Opcode t_op) -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Literal& t_lit)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::SsaVar& t_var) -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Label& t_label)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Operand& t_operand)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Instruction& t_inst)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::BasicBlock& t_bblock)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Function& t_fn)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::Module& t_mod) -> std::ostream&;
auto operator<<(std::ostream& t_os, const clir::ModulePtr& t_mod)
  -> std::ostream&;

#endif // CROW_CROW_CLIR_CLIR_HPP
