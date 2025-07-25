#ifndef CROW_CROW_SEMANTIC_SEMANTIC_CHECKER_HPP
#define CROW_CROW_SEMANTIC_SEMANTIC_CHECKER_HPP

// STL Includes:
#include <string_view>

// Absolute includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/container/text_position.hpp"
#include "crow/types/semantic/semantic.hpp"
#include "crow/types/semantic/symbol.hpp"

// Local Includes:
#include "symbol_env_state.hpp"
#include "symbol_table/symbol_table_factory.hpp"
#include "type_promoter.hpp"

/*!
 * @file
 *
 * Contains class responsible for type checking the ast.
 * This class will also annotate the AST and perform type promotion.
 * As well as generate a global @ref SymbolTable.
 * Which can be used for symbol lookup.
 */

namespace semantic {
// Using Statements:
using namespace ast;

// Using Declarations:
using ast::node::NodeListPtr;
using ast::node::NodePtr;
using ast::visitor::Any;
using ast::visitor::NodeVisitor;
using container::TextPosition;
using semantic::symbol_table::SymbolTablePtr;
using symbol::SymbolData;
using symbol::SymbolDataList;
using symbol_table::SymbolTable;
using symbol_table::SymbolTableFactory;
using symbol_table::SymbolTablePtr;
using types::core::NativeType;
using types::core::NativeTypeOpt;

// Classes:
// TODO: Add check for checking if the AST only has a single module declaration.
// We should either way, have some kind of entity which merges multiple
// translation units.
// Into a single Module Unit.
// Maybe force module declarations to be at the top of the file?
// To be considered when enforcing modules.
/*!
 * The semantic checker validates the semantic validity of the AST.
 * This performs type inference and type checking.
 * This also checks that we are not assigning to any constant variables.
 * We also check if arguments have the right types for any functions.
 *
 * We also create a symbol table after semantic analysis.
 * As we need to create it anyway when looking up symbols.
 */
class SemanticChecker : public NodeVisitor {
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
   *
   * @return false means inserting the symbol failed.
   */
  [[nodiscard("Returned boolean indicates error value, must be checked.")]]
  auto add_symbol(std::string_view t_id, const SymbolData& t_data) -> bool;

  [[nodiscard("Pure method must use result.")]]
  auto get_symbol_data_from_env(std::string_view t_id) const -> SymbolData;

  auto retrieve_symbol_table() const -> SymbolTablePtr;

  // Helper methods for type promotion:
  //! Handle type conversion for conditionals.
  auto handle_condition(const SymbolData& t_data,
                        const TextPosition& t_pos) const -> void;

  //! Handle type promotion between two different types.
  auto promote(const SymbolData& t_lhs, const SymbolData& rhs,
               bool enforce_lhs = false) const -> NativeTypeOpt;

  // Helper methods for dealing with resolving nodes to SymbolData:
  // NodeVisitor visitation is not marked const so these methods cant be const.
  auto get_symbol_data(NodePtr t_ptr) -> SymbolData;
  auto get_resolved_type(NodePtr t_ptr) -> SymbolData;
  auto get_native_type(NodePtr t_ptr) -> NativeTypeOpt;
  auto get_type_list(NodeListPtr t_list) -> SymbolDataList;
  auto get_resolved_type_list(NodeListPtr t_list) -> SymbolDataList;

  public:
  SemanticChecker();

  // Control:
  auto visit(node::control::If* t_if) -> Any override;
  auto visit(node::control::Loop* t_loop) -> Any override;
  auto visit(node::control::Continue* t_continue) -> Any override;
  auto visit(node::control::Break* t_break) -> Any override;
  auto visit(node::control::Defer* t_defer) -> Any override;
  auto visit(node::control::Return* t_return) -> Any override;

  // Function:
  auto visit(node::function::Parameter* t_param) -> Any override;
  auto visit(node::function::Function* t_fn) -> Any override;
  auto visit(node::function::Call* t_fn_call) -> Any override;
  auto visit(node::function::ReturnType* t_rt) -> Any override;

  // Lvalue:
  auto decl_expr(node::node_traits::DeclExpr* t_decl) -> SymbolData;
  auto visit(node::lvalue::Let* t_let) -> Any override;
  auto visit(node::lvalue::Var* t_var) -> Any override;
  auto visit(node::lvalue::Variable* t_var) -> Any override;

  // Operators:
  auto visit(node::operators::Arithmetic* t_arith) -> Any override;
  auto visit(node::operators::Assignment* t_assign) -> Any override;
  auto visit(node::operators::Comparison* t_comp) -> Any override;

  auto visit(node::operators::Increment* t_inc) -> Any override;
  auto visit(node::operators::Decrement* t_dec) -> Any override;

  auto visit(node::operators::UnaryPrefix* t_up) -> Any override;

  // Logical:
  auto visit(node::operators::Not* t_not) -> Any override;
  auto visit(node::operators::And* t_and) -> Any override;
  auto visit(node::operators::Or* t_or) -> Any override;

  // auto visit(node::operators::Ternary* t_ternary) -> Any override;

  // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> Any override;

  // Rvalue:
  auto visit(node::rvalue::Float* t_float) -> Any override;
  auto visit(node::rvalue::Integer* t_int) -> Any override;
  auto visit(node::rvalue::String* t_str) -> Any override;
  auto visit(node::rvalue::Boolean* t_bool) -> Any override;

  // Typing:
  auto visit(node::typing::MethodDecl* t_md) -> Any override;
  auto visit(node::typing::Interface* t_ifc) -> Any override;
  auto visit(node::typing::MemberDecl* t_md) -> Any override;
  auto visit(node::typing::Struct* t_struct) -> Any override;
  auto visit(node::typing::Impl* t_impl) -> Any override;
  auto visit(node::typing::DotExpr* t_dot_expr) -> Any override;

  auto check(NodePtr t_ast) -> SymbolTablePtr;

  virtual ~SemanticChecker() = default;
};
} // namespace semantic

#endif // CROW_CROW_SEMANTIC_SEMANTIC_CHECKER_HPP
