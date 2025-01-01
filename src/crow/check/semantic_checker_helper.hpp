#ifndef CROW_CROW_CHECK_SEMANTIC_CHECKER_HELPER_HPP
#define CROW_CROW_CHECK_SEMANTIC_CHECKER_HELPER_HPP

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/container/text_position.hpp"

// Local Includes:
#include "env_state.hpp"
#include "symbol/symbol.hpp"
#include "symbol/symbol_data.hpp"
#include "symbol_table/symbol_table.hpp"
#include "type_promoter.hpp"

namespace check {
// Using Declarations:
using ast::node::NodeListPtr;
using ast::node::NodePtr;
using ast::node::node_traits::typing::NativeTypeOpt;
using ast::visitor::Any;
using ast::visitor::NodeVisitor;
using container::TextPosition;
using symbol::SymbolData;
using symbol::SymbolDataList;
using symbol_table::SymbolTable;

// Classes:
/*!
 * Helper class for dealing with @ref SymbolData in a @ref NodeVisitor context.
 * Other utility methods are added to this class.
 */
class SemanticCheckerHelper : public NodeVisitor {
  private:
  EnvState m_env_state;
  SymbolTable m_symbol_table;
  TypePromoter m_type_promoter;

  protected:
  // Environment related methods:
  auto clear_env() -> void;
  auto push_env() -> void;
  auto pop_env() -> void;

  /*!
   * Add symbol to current @ref EnvSate.
   * Also add the symbol to the global @ref SymbolTable.
   */
  auto add_symbol(std::string_view t_id, const SymbolData& t_data) -> bool;
  auto get_symbol(std::string_view t_id) const -> SymbolData;

  //! Handle type conversion for conditionals.
  auto handle_condition(const SymbolData& t_data,
                        const TextPosition& t_pos) const -> void;

  //! Handle type promotion between two different types.
  auto promote(const SymbolData& t_lhs, const SymbolData& rhs,
               bool enforce_lhs = false) const -> NativeTypeOpt;

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
} // namespace check

#endif // CROW_CROW_CHECK_SEMANTIC_CHECKER_HELPER_HPP
