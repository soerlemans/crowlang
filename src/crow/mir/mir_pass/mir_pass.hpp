#ifndef MIR_PASS_HPP
#define MIR_PASS_HPP

// Absolute Includes:
#include "mir/mir.hpp"

namespace mir::mir_pass {
class MirPass {
  public:
  MirPass() = default;

  virtual ~MirPass() = default;
};

} // namespace mir::mir_pass

#endif // MIR_PASS_HPP
