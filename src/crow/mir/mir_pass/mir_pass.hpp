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
  protected:
  ModulePtr m_module;

  // clang-format off
	// TODO: Add symbol table, containing references to MIR entities (functions, variables, structs).
  // clang-format on
  public:
  MirPass() = default;

  // TODO: Think about this.
  virtual auto on_function() -> void = 0;
  virtual auto on_block() -> void = 0;
  virtual auto on_instruction() -> void = 0;

  virtual auto run(ModulePtr t_module) -> void = 0;

  virtual ~MirPass() = default;
};

} // namespace mir::mir_pass

#endif // CROW_CROW_MIR_MIR_PASS_MIR_PASS_HPP
