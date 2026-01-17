#ifndef ACRIS_ACRIS_SYMBOL_TABLE_SYMBOL_TABLE_HPP
#define ACRIS_ACRIS_SYMBOL_TABLE_SYMBOL_TABLE_HPP

/*!
 * @file symbol_table.hpp
 *
 * In order to deal with a symbol that needs to looked up across.
 * Multiple compiler passes.
 */

// STL Include:
#include <expected>
#include <iomanip>
#include <map>
#include <memory>
#include <optional>
#include <stack>
#include <string>
#include <string_view>

// Absolute includes:
#include "lib/iomanip/iomanip.hpp"
#include "lib/stdprint.hpp"
#include "lib/stdtypes.hpp"

// Local Includes:
#include "symbol_register/symbol_register.hpp"
#include "symbol_tree/symbol_tree.hpp"

namespace symbol_table {
// Forward Declarations:
template<typename RegisterType>
class SymbolTable;

// Using Declarations:
using symbol_tree::SymbolTreeResult;

// Aliases:
template<typename RegisterType>
using SymbolTablePtr = std::shared_ptr<SymbolTable<RegisterType>>;

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
  using Register = symbol_register::SymbolRegister<RegisterType>;
  using SymbolTreePtr = symbol_tree::SymbolTreePtr;

  SymbolTreePtr m_tree;
  Register m_register;

  public:
  explicit SymbolTable(SymbolTreePtr t_tree, Register t_register)
    : m_tree{t_tree}, m_register{std::move(t_register)}
  {}

  //! Regular recursive lookup of a symbol name.
  // auto lookup(std::string_view t_symbol_name) const -> SymbolTreeResult
  // {
  // }

  //! Toplevel lookup of a symbol name.
  // auto lookup_toplevel(std::string_view t_symbol_name) const ->
  // SymbolTreeResult
  // {
  // }

  auto tree() -> SymbolTreePtr
  {
    return m_tree;
  }

  auto register_() -> Register&
  {
    return m_register;
  }

  virtual ~SymbolTable() = default;
};
} // namespace symbol_table

// Functions:
template<typename RegisterType>
inline auto operator<<(
  std::ostream& t_os,
  const symbol_table::SymbolTable<RegisterType>& t_symbol_table)
  -> std::ostream&
{
  const auto& tree{t_symbol_table.tree()};
  const auto& register_{t_symbol_table.register_()};
  t_os << "SymbolTable{ tree: " << tree << ", register: " << register_ << '}';

  return t_os;
}

template<typename RegisterType>
inline auto operator<<(std::ostream& t_os,
                       const symbol_table::SymbolTablePtr<RegisterType>& t_ptr)
  -> std::ostream&
{
  using lib::stdprint::detail::print_smart_ptr;

  return print_smart_ptr(t_os, t_ptr);
}

#endif // ACRIS_ACRIS_SYMBOL_TABLE_SYMBOL_TABLE_HPP
