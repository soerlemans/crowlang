#ifndef CROW_CROW_CODEGEN_CPP_BACKEND_PROTOTYPE_GENERATOR_HPP
#define CROW_CROW_CODEGEN_CPP_BACKEND_PROTOTYPE_GENERATOR_HPP

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
/*!
 * TODO:
 * Currently the prototype generator is a node visitor.
 * As traversing the AST is a costly operation.
 * It is best that we replace this by walking the symbol table.
 */
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

  // Lvalue:
  auto visit(node::lvalue::Let* t_let) -> Any override;
  auto visit(node::lvalue::Var* t_var) -> Any override;

  // Meta:
  auto visit(node::meta::FunctionDecl* t_fdecl) -> Any override;
  auto visit(node::meta::LetDecl* t_ldecl) -> Any override;
  auto visit(node::meta::VarDecl* t_vdecl) -> Any override;

  // Module:
  auto visit(node::packaging::ModuleDecl* t_module) -> Any override;

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

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_PROTOTYPE_GENERATOR_HPP
