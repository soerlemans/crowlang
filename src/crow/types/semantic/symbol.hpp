#ifndef CROW_CROW_TYPES_SEMANTIC_SYMBOL_HPP
#define CROW_CROW_TYPES_SEMANTIC_SYMBOL_HPP

// STL Includes:
#include <iosfwd>
#include <list>
#include <memory>
#include <optional>

namespace semantic::symbol {
// Forward Declarations:
class SymbolData;

struct StructType;
struct FnType;
struct PointerType;
struct VarType;

// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using PointerTypePtr = std::shared_ptr<PointerType>;
using VarTypePtr = std::shared_ptr<VarType>;

using SymbolDataList = std::list<SymbolData>;
} // namespace semantic::symbol

// Functions:
auto operator<<(std::ostream& t_os, semantic::symbol::StructTypePtr t_struct)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, semantic::symbol::FnTypePtr t_fn)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, semantic::symbol::PointerTypePtr t_ptr)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, semantic::symbol::VarTypePtr t_var)
  -> std::ostream&;

auto operator<<(std::ostream& t_os,
                const semantic::symbol::SymbolDataList& t_list)
  -> std::ostream&;

#endif // CROW_CROW_TYPES_SEMANTIC_SYMBOL_HPP
