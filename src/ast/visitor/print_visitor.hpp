#ifndef CROW_AST_VISITOR_PRINT_VISITOR_HPP
#define CROW_AST_VISITOR_PRINT_VISITOR_HPP

// STL Includes:
#include <iostream>

// Includes:
#include "../node/include.hpp"

// Local Includes:
#include "node_visitor.hpp"


namespace ast::visitor {
/*! Visitor made for printing the AST Node per node
 * Has a unique overload for every print
 */
class PrintVisitor : public NodeVisitor {
  private:
  //! This class is made for pretty printing the AST
  class Printer {
    private:
    int& m_counter;

    public:
    Printer(int& t_counter): m_counter{t_counter}
    {
      m_counter++;
    }

    auto print_if(node::NodePtr t_ptr, PrintVisitor* t_this,
                  std::string_view t_str_vw) -> void
    {
      if(t_ptr) {
        print(t_str_vw);
        t_ptr->accept(t_this);
      }
    }

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

    ~Printer()
    {
      m_counter--;
    }
  };

  // Variables:
  int m_counter{0};

  public:
  PrintVisitor() = default;

  auto visit(node::control::If* t_if) -> void override;
  auto visit(node::control::Continue* t_continue) -> void override;
  auto visit(node::control::Break* t_break) -> void override;
  auto visit(node::control::Return* t_return) -> void override;

  auto visit(node::functions::Function* t_fn) -> void override;
  auto visit(node::functions::FunctionCall* t_fn_call) -> void override;

  auto visit(node::lvalue::Variable* t_var) -> void override;

  auto visit(node::operators::Arithmetic* t_arithmetic) -> void override;
  auto visit(node::operators::Assignment* t_assignment) -> void override;
  auto visit(node::operators::Comparison* t_comparison) -> void override;

  auto visit(node::operators::Increment* t_increment) -> void override;
  auto visit(node::operators::Decrement* t_decrement) -> void override;

  auto visit(node::operators::Not* t_not) -> void override;
  auto visit(node::operators::And* t_and) -> void override;
  auto visit(node::operators::Or* t_or) -> void override;

  auto visit(node::operators::Ternary* t_ternary) -> void override;

  auto visit(node::operators::UnaryPrefix* t_unary_prefix) -> void override;

  auto visit(node::packaging::Import* t_import) -> void override;
  auto visit(node::packaging::Package* t_pkg) -> void override;

  auto visit(node::rvalue::Float* t_float) -> void override;
  auto visit(node::rvalue::Integer* t_int) -> void override;
  auto visit(node::rvalue::String* t_str) -> void override;

  auto visit(node::List* t_list) -> void override;
  auto visit(node::Nil* t_nil) -> void override;

  ~PrintVisitor() override = default;
};
} // namespace ast::visitor

#endif // CROW_AST_VISITOR_PRINT_VISITOR_HPP
