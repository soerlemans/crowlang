#ifndef CROW_CROW_CHECK_SYMBOL_HELPER_HPP
#define CROW_CROW_CHECK_SYMBOL_HELPER_HPP

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"

// Local Includes:
#include "symbol/symbol.hpp"
#include "symbol/symbol_data.hpp"

namespace check {
// Using Declarations:
using ast::node::NodeListPtr;
using ast::node::NodePtr;
using ast::node::node_traits::typing::NativeTypeOpt;
using ast::visitor::Any;
using ast::visitor::NodeVisitor;
using symbol::SymbolData;
using symbol::SymbolDataList;

// Classes:
/*!
 * Helper class for dealing with @ref SymbolData in a @ref NodeVisitor context.
 */
class SymbolHelper : public NodeVisitor {
  protected:
  auto get_symbol_data(NodePtr t_ptr) -> SymbolData;
  auto get_resolved_type(NodePtr t_ptr) -> SymbolData;
  auto get_native_type(NodePtr t_ptr) -> NativeTypeOpt;
  auto get_type_list(NodeListPtr t_list) -> SymbolDataList;
  auto get_resolved_type_list(NodeListPtr t_list) -> SymbolDataList;

  public:
  SymbolHelper() = default;

  virtual ~SymbolHelper() = default;
};
} // namespace check

#endif // CROW_CROW_CHECK_SYMBOL_HELPER_HPP
