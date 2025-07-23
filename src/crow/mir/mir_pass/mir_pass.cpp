#include "mir_pass.hpp"

namespace mir::mir_pass {
auto MirPass::run(MirPassParams t_params) -> void
{
  auto& [module_] = t_params;

	// TODO: Set symboltable?

  on_module(module_);
};
} // namespace mir::mir_pass
