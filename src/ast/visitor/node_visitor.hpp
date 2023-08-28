#ifndef CROW_AST_VISITOR_NODE_VISITOR_HPP
#define CROW_AST_VISITOR_NODE_VISITOR_HPP

// Includes:
#include "../node/fdecl.hpp"


namespace ast::visitor {
// Classes:
/*! Implementation of the Visitor design pattern for Nodes
 * This creates a recursive dependency on the different kind of nodes
 * So all nodes need to be forward declared in this header
 */
class NodeVisitor {
  private:
  public:
  NodeVisitor() = default;

  virtual auto visit(node::control::If* t_if) -> void = 0;
  virtual auto visit(node::control::Continue* t_continue) -> void = 0;
  virtual auto visit(node::control::Break* t_break) -> void = 0;
  virtual auto visit(node::control::Return* t_return) -> void = 0;

  virtual auto visit(node::functions::Function* t_fn) -> void = 0;
  virtual auto visit(node::functions::FunctionCall* t_fn_call) -> void = 0;

  virtual auto visit(node::lvalue::Variable* t_var) -> void = 0;

  virtual auto visit(node::rvalue::Float* t_float) -> void = 0;
  virtual auto visit(node::rvalue::Integer* t_int) -> void = 0;
  virtual auto visit(node::rvalue::String* t_str) -> void = 0;

  virtual auto visit(node::operators::Arithmetic* t_arithmetic) -> void = 0;
  virtual auto visit(node::operators::Assignment* t_assignment) -> void = 0;
  virtual auto visit(node::operators::Comparison* t_comparison) -> void = 0;

  virtual auto visit(node::operators::Increment* t_increment) -> void = 0;
  virtual auto visit(node::operators::Decrement* t_decrement) -> void = 0;

  virtual auto visit(node::operators::Not* t_not) -> void = 0;
  virtual auto visit(node::operators::And* t_and) -> void = 0;
  virtual auto visit(node::operators::Or* t_or) -> void = 0;

  virtual auto visit(node::operators::Grouping* t_grouping) -> void = 0;
  virtual auto visit(node::operators::Ternary* t_ternary) -> void = 0;

  virtual auto visit(node::operators::UnaryPrefix* t_unary_prefix) -> void = 0;

  virtual auto visit(node::List* t_list) -> void = 0;
  virtual auto visit(node::Nil* t_nil) -> void = 0;

  virtual auto visit(node::NodeInterface* t_node) -> void;

  virtual ~NodeVisitor() = default;
};
} // namespace visitor

#endif // CROW_AST_VISITOR_NODE_VISITOR_HPP
