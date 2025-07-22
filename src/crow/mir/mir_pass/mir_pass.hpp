#ifndef MIR_PASS_HPP
#define MIR_PASS_HPP

// Absolute Includes:
#include "mir/mir.hpp"

namespace mir::mir_pass {
class MirPass {
  protected:
  ModulePtr m_module;

  // clang-format off
	// TODO: Add symbol table, containing references to MIR entities (functions, variables, structs).
  // clang-format on
  public:
  MirPass() = default;

  virtual auto run(ModulePtr t_module) -> void = 0;

  virtual ~MirPass() = default;
};

} // namespace mir::mir_pass

#endif // MIR_PASS_HPP
