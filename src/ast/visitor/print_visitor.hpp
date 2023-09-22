#ifndef CROW_AST_VISITOR_PRINT_VISITOR_HPP
#define CROW_AST_VISITOR_PRINT_VISITOR_HPP

// STL Includes:
#include <iostream>

// Local Includes:
#include "node_visitor.hpp"

// Includes:
#include "../node/include.hpp"


namespace ast::visitor {
/*! Visitor made for printing the AST Node per node
 * Has a unique overload for every print
 */
class PrintVisitor : public NodeVisitor {
  private:
  int m_counter{0};

  friend class CountGuard;

  auto print_if(std::string_view t_str, ast::node::NodePtr t_ptr) -> void;

  template<typename... Args>
  auto print(Args&&... t_args) -> void
  {
    // Construct the prefix
    std::cout << std::string(m_counter, ' ') << "-> ";

    // Print the arguments
    (std::cout << ... << t_args);

    // Create the indentation level denoter
    std::cout << " - (" << m_counter << ")\n";
  }

  template<typename Derived, typename Base, typename Fn>
  auto when_derived(const Fn t_fn) -> void
  {
    if constexpr(std::derived_from<Derived, Base>) {
      t_fn();
    }
  }

  template<typename Ptr>
  auto print_traits(Ptr t_ptr) -> void
  {
    using namespace ast::node::node_traits;
    using N = decltype(*t_ptr);

    when_derived<N, Identifier>([&] {
      print("| Identifier: ", t_ptr->identifier());
    });

    when_derived<N, InitExpr>([&] {
      // print_if("Init Expr", t_ptr->init_expr());
    });
  }

  public:
  PrintVisitor() = default;

  // Control:
  auto visit(node::control::If* t_if) -> void override;
  auto visit(node::control::Loop* t_loop) -> void override;
  auto visit(node::control::Continue* t_continue) -> void override;
  auto visit(node::control::Break* t_break) -> void override;
  auto visit(node::control::Return* t_return) -> void override;

  // Function:
  auto visit(node::functions::Function* t_fn) -> void override;
  auto visit(node::functions::FunctionCall* t_fn_call) -> void override;
  auto visit(node::functions::ReturnType* t_rt) -> void override;

  //
  auto visit(node::lvalue::Let* t_let) -> void override;
  auto visit(node::lvalue::Variable* t_var) -> void override;

  // Operators:
  auto visit(node::operators::Arithmetic* t_arithmetic) -> void override;
  auto visit(node::operators::Assignment* t_assignment) -> void override;
  auto visit(node::operators::Comparison* t_comparison) -> void override;

  auto visit(node::operators::Increment* t_increment) -> void override;
  auto visit(node::operators::Decrement* t_decrement) -> void override;

  auto visit(node::operators::UnaryPrefix* t_unary_prefix) -> void override;

  // Logical:
  auto visit(node::operators::Not* t_not) -> void override;
  auto visit(node::operators::And* t_and) -> void override;
  auto visit(node::operators::Or* t_or) -> void override;

  auto visit(node::operators::Ternary* t_ternary) -> void override;

  // Packaging:
  auto visit(node::packaging::Import* t_import) -> void override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> void override;

  // Rvalue:
  auto visit(node::rvalue::Float* t_float) -> void override;
  auto visit(node::rvalue::Integer* t_int) -> void override;
  auto visit(node::rvalue::String* t_str) -> void override;
  auto visit(node::rvalue::Boolean* t_bool) -> void override;

  // Typing:
  auto visit(ast::node::typing::MethodDecl* t_md) -> void override;
  auto visit(ast::node::typing::Interface* t_ifc) -> void override;
  auto visit(ast::node::typing::MemberDecl* t_md) -> void override;
  auto visit(ast::node::typing::Struct* t_struct) -> void override;
  auto visit(ast::node::typing::DefBlock* t_db) -> void override;
  auto visit(ast::node::typing::DotExpr* t_dot_expr) -> void override;

  auto visit(node::List* t_list) -> void override;
  auto visit(node::Nil* t_nil) -> void override;

  ~PrintVisitor() override = default;
};
} // namespace ast::visitor

#endif // CROW_AST_VISITOR_PRINT_VISITOR_HPP
