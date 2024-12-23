#ifndef CROW_CROW_CHECK_CHECK_HPP
#define CROW_CROW_CHECK_CHECK_HPP

// STL Includes:
#include <iostream>
#include <list>
#include <memory>
#include <optional>

namespace check::symbol {
// Forward Declarations:
class SymbolData;

struct StructType;
struct FnType;
struct VarType;

// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using VarTypePtr = std::shared_ptr<VarType>;

using SymbolDataList = std::list<SymbolData>;
} // namespace check::symbol

// Functions:
auto operator<<(std::ostream& t_os, check::symbol::StructTypePtr t_struct)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, check::symbol::FnTypePtr t_fn)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, check::symbol::VarTypePtr t_var)
  -> std::ostream&;

auto operator<<(std::ostream& t_os, const check::symbol::SymbolDataList& t_list)
  -> std::ostream&;

#endif // CROW_CROW_CHECK_CHECK_HPP
