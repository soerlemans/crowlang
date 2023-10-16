#ifndef CROW_CHECK_SYMBOL_TYPES_HPP
#define CROW_CHECK_SYMBOL_TYPES_HPP

// STL Includes:
#include <optional>

// Local Includes:
#include "native_types.hpp"


namespace check {
// Forward Declarations:
class SymbolData;

struct StructType;
struct FnType;
struct VarType;

// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using VarTypePtr = std::shared_ptr<VarType>;

using TypeList = std::vector<SymbolData>;
using NativeTypeOpt = std::optional<NativeType>;
} // namespace check

// Functions:
auto operator<<(std::ostream& t_os, check::NativeTypeOpt t_opt)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, check::StructTypePtr t_struct)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, check::FnTypePtr t_fn) -> std::ostream&;
auto operator<<(std::ostream& t_os, check::VarTypePtr t_var) -> std::ostream&;

#endif // CROW_CHECK_SYMBOL_TYPES_HPP
