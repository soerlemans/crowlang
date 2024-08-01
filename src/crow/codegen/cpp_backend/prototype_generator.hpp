#ifndef PROTOTYPE_GENERATOR_HPP
#define PROTOTYPE_GENERATOR_HPP

// STL Includes:
#include <string>

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast;

// Using Declarations:
using node::NodePtr;
using visitor::Any;
using visitor::NodeVisitor;

// Classes:
class PrototypeGenerator : public NodeVisitor {
  protected:
  /*!
   * Convert the given AST node to C++ code.
   *
   * @note Throws an exception if it fails at converting the @ref Any.
   */
  [[nodiscard("Pure method must use results.")]]
  auto resolve(NodePtr t_ptr) -> std::string;

  public:
  PrototypeGenerator() = default;

  // Function:
  auto visit(node::function::Parameter* t_param) -> Any override;
  auto visit(node::function::Function* t_fn) -> Any override;

  // Typing:
  auto visit(node::typing::Struct* t_struct) -> Any override;

  // Misc:
  auto visit(node::List* t_list) -> Any override;

  // Util:
  /*!
   * Generate the prototypes.
   */
  [[nodiscard("Pure method must use results.")]]
  auto generate(NodePtr t_ast) -> std::string;

  virtual ~PrototypeGenerator() = default;
};
} // namespace codegen::cpp_backend

#endif // PROTOTYPE_GENERATOR_HPP
