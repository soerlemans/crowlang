#ifndef FDECL_HPP
#define FDECL_HPP

/*!
 * @file Forward declarations for any operations on CLIR.
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
} // namespace clir

#endif // FDECL_HPP
