#ifndef CROW_CROW_SEMANTIC_SEMANTIC_CHECKER_HELPER_HPP
#define CROW_CROW_SEMANTIC_SEMANTIC_CHECKER_HELPER_HPP

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/container/text_position.hpp"
#include "crow/types/semantic/semantic.hpp"
#include "crow/types/semantic/symbol.hpp"

// Local Includes:
#include "symbol_env_state.hpp"
#include "symbol_table/symbol_table_factory.hpp"
#include "type_promoter.hpp"

namespace semantic {
// Using Declarations:
using ast::node::NodeListPtr;
using ast::node::NodePtr;
using ast::visitor::Any;
using ast::visitor::NodeVisitor;
using container::TextPosition;
using symbol::SymbolData;
using symbol::SymbolDataList;
using symbol_table::SymbolTable;
using symbol_table::SymbolTableFactory;
using symbol_table::SymbolTablePtr;
using types::core::NativeTypeOpt;

// TODO: Currently we have to manually clear_env() in order to reset the state.
// Of @ref EnvState and @ref SymbolTableFactory().
// It is better to use a shared interface which we use std::shared_ptr.
// To create and destruct, this is more self contained and memory efficient.

// Classes:
/*!
 * Helper class for dealing with @ref SymbolData in a @ref NodeVisitor context.
 * Other utility methods are added to this class.
 */
class SemanticCheckerHelper : public NodeVisitor {
  private:
  SymbolEnvState m_symbol_state;
  SymbolTableFactory m_symbol_table_factory;
  TypePromoter m_type_promoter;

  protected:
  // Environment related methods:
  auto push_env() -> void;
  auto pop_env() -> void;
  auto clear_env() -> void;

  /*!
   * Add symbol to current @ref EnvSate.
   * Also add the symbol to the global @ref SymbolTable.
   */
  [[nodiscard("Returned boolean indicates error value, must be checked.")]]
  auto add_symbol(std::string_view t_id, const SymbolData& t_data) -> bool;
  auto get_symbol(std::string_view t_id) const -> SymbolData;

  auto retrieve_symbol_table() const -> SymbolTablePtr;

  // Helper methods for type promotion:
  //! Handle type conversion for conditionals.
  auto handle_condition(const SymbolData& t_data,
                        const TextPosition& t_pos) const -> void;

  //! Handle type promotion between two different types.
  auto promote(const SymbolData& t_lhs, const SymbolData& rhs,
               bool enforce_lhs = false) const -> NativeTypeOpt;

  // Helper methods for dealing with SymbolData:
  // NodeVisitor visitation is not marked const so these methods cant be const.
  auto get_symbol_data(NodePtr t_ptr) -> SymbolData;
  auto get_resolved_type(NodePtr t_ptr) -> SymbolData;
  auto get_native_type(NodePtr t_ptr) -> NativeTypeOpt;
  auto get_type_list(NodeListPtr t_list) -> SymbolDataList;
  auto get_resolved_type_list(NodeListPtr t_list) -> SymbolDataList;

  public:
  SemanticCheckerHelper() = default;

  virtual ~SemanticCheckerHelper() = default;
};
} // namespace semantic

#endif // CROW_CROW_SEMANTIC_SEMANTIC_CHECKER_HELPER_HPP
