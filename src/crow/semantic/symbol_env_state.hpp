#ifndef CROW_CROW_SEMANTIC_SYMBOL_ENV_STATE_HPP
#define CROW_CROW_SEMANTIC_SYMBOL_ENV_STATE_HPP

// STL Includes:
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

// Absolute Includes:
#include "crow/container/env_state.hpp"
#include "crow/diagnostic/diagnostic.hpp"
#include "crow/types/semantic/semantic.hpp"

namespace semantic {
// Using:
using symbol::SymbolData;

// Enums:
enum class SymbolStatus {
  DECLARED,
  DEFINED,
};

// Structs:
struct Symbol {
  SymbolStatus m_status;
  SymbolData m_data;
};

// Classes:
/*!
 * Keep track of the current state of the environment and its Symbols.
 * This is a Scoped @ref SymbolTable, that only keeps track of the symbols.
 * That are currently in scope when traversing the AST.
 * Used in @ref SemanticChecker.
 */
class SymbolEnvState : public container::EnvState<Symbol> {
  public:
  using BaseEnvState = container::EnvState<Symbol>;

  SymbolEnvState() = default;

  //! Expect means it is required and if we dont find it error.
  auto get_value(std::string_view t_key) const -> const Symbol&;

  auto get_status(std::string_view t_key) const -> SymbolStatus;
  auto get_data(std::string_view t_key) const -> SymbolData;

  virtual ~SymbolEnvState() = default;
};

// Functions:
auto symbol_status2str(SymbolStatus t_status) -> std::string_view;
} // namespace semantic

// Functions:
auto operator<<(std::ostream& t_os, const semantic::Symbol& t_symbol)
  -> std::ostream&;

#endif // CROW_CROW_SEMANTIC_SYMBOL_ENV_STATE_HPP
