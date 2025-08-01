#ifndef CROW_CROW_MIR_MIR_PASS_MIR_PASS_HPP
#define CROW_CROW_MIR_MIR_PASS_MIR_PASS_HPP

// Absolute Includes:
#include "crow/mir/mir.hpp"

namespace mir::mir_pass {
// Structs:
struct MirPassParams {
  ModulePtr m_module;
  // TODO: SymbolTable.
};

// Classes:
class MirPass {
  public:
  MirPass() = default;

  // TODO: Think about this.
  virtual auto on_module(ModulePtr& t_module) -> void;
  virtual auto on_function(FunctionPtr& t_fn) -> void;
  virtual auto on_block(BasicBlock& t_block) -> void;
  virtual auto on_instruction(Instruction& t_instr) -> void = 0;

  virtual auto run_pass(MirPassParams t_params) -> void;

  virtual ~MirPass() = default;
};

} // namespace mir::mir_pass

#endif // CROW_CROW_MIR_MIR_PASS_MIR_PASS_HPP
