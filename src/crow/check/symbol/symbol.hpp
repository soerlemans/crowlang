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

using TypeList = std::list<SymbolData>;
} // namespace check

// Functions:
auto operator<<(std::ostream& t_os, check::StructTypePtr t_struct)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, check::FnTypePtr t_fn) -> std::ostream&;
auto operator<<(std::ostream& t_os, check::VarTypePtr t_var) -> std::ostream&;

auto operator<<(std::ostream& t_os, const check::TypeList& t_list)
  -> std::ostream&;

#endif // CROW_CROW_CHECK_CHECK_HPP
