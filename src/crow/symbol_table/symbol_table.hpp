#ifndef CROW_CROW_SYMBOL_TABLE_SYMBOL_TABLE_HPP
#define CROW_CROW_SYMBOL_TABLE_SYMBOL_TABLE_HPP

/*!
 * @file symbol_table.hpp
 *
 * In order to deal with a symbol that needs to looked up across.
 * Multiple compiler passes.
 */

// STL Include:
#include <expected>
#include <map>
#include <memory>
#include <optional>
#include <stack>
#include <string>

// Absolute includes:
#include "lib/stdtypes.hpp"


// Local Includes:
#include "symbol_register.hpp"
#include "symbol_tree.hpp"

namespace symbol_table {
// Forward Declarations:
class SymbolTable;

// Aliases:
using SymbolTablePtr = std::shared_ptr<SymbolTable>;

// Classes:
/*!
 * The @ref SymbolTable is a wrapper class of the @ref SymbolTree .
 * And the @ref SymbolRegister .
 * The @ref SymbolTree keeps track of the symbols.
 * And their position in the nested scopes.
 * And the registery is a direct index based lookup.
 * This allows us to decouple the symbol structuring, of the associated type.
 * Allowing us to reuse the @ref SymbolTree across different compiler passes.
 */
template<typename RegisterType>
class SymbolTable {
  private:
  using SymbolRegister = SymbolRegister<RegisterType>;

  SymbolTreePtr m_tree;
  SymbolRegister m_register;

  public:
  explicit SymbolTable(SymbolTreePtr t_tree, SymbolRegister&& t_register)
    : m_tree{t_tree}, m_register{std::move(t_register)}
  {}

  auto lookup(std::string_view t_symbol_name) const -> SymbolTableResult
  {}

  auto lookup_toplevel(std::string_view t_symbol_name) const
    -> SymbolTableResult
  {}

  auto tree() -> SymbolTreePtr
  {
    return m_tree;
  }

  virtual ~SymbolTable() = default;
};
} // namespace symbol_table

// Functions:
auto operator<<(std::ostream& t_os,
                const symbol_table::SymbolTable& t_symbol_table)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, const symbol_table::SymbolTablePtr& t_ptr)
  -> std::ostream&;


#endif // CROW_CROW_SYMBOL_TABLE_SYMBOL_TABLE_HPP
