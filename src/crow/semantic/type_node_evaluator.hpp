#ifndef TYPE_NODE_EVALUATOR_HPP
#define TYPE_NODE_EVALUATOR_HPP

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/types/semantic/symbol_data.hpp"

// Local Includes:
#include "symbol_env_state.hpp"

namespace semantic {
// Using:
using ast::node::NodePtr;
using ast::visitor::Any;
using ast::visitor::NodeVisitor;
using types::symbol::SymbolData;

namespace node = ast::node;

// Classes.
class TypeNodeEvaluator : public NodeVisitor {
  private:
  SymbolEnvState& m_symbol_state;

  public:
  TypeNodeEvaluator(SymbolEnvState& t_symbol_state);

  auto str2type(const std::string_view t_type_id) -> SymbolData;

  // Builtin Types:
  virtual auto visit(node::builtin_types::Pointer* t_ptr) -> Any;
  virtual auto visit(node::builtin_types::TypeName* t_type) -> Any;

  virtual auto evaluate(NodePtr t_ast) -> SymbolData;

  virtual ~TypeNodeEvaluator() = default;
};
} // namespace semantic

#endif // TYPE_NODE_EVALUATOR_HPP
