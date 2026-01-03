#ifndef CROW_CROW_CODEGEN_CPP_BACKEND_CPP_BACKEND_HPP
#define CROW_CROW_CODEGEN_CPP_BACKEND_CPP_BACKEND_HPP

// STL Includes:
#include <stack>

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/codegen/backend_interface.hpp"
#include "crow/codegen/cpp_backend/clang_frontend_invoker.hpp"
#include "crow/codegen/cpp_backend/interop/cpp_interop_backend_interface.hpp"
#include "lib/filesystem.hpp"
#include "lib/stdtypes.hpp"

namespace codegen::cpp_backend {
// Using:
namespace node = ast::node;
namespace fs = std::filesystem;

using ast::node::NodePtr;
using ast::visitor::NodeVisitor;
using interop::CppInteropBackendPtr;
using visitor::Any;

using InteropBackends = std::vector<CppInteropBackendPtr>;
using TerminateStack = std::stack<bool>;

// Enums:
enum class CouldTerminate {
  ALLOW, //< Allow an expression to terminate if needed.
  NO     //< Dont allow nested expression resolution to terminate.
};

// Classes:
/*!
 * @brief Tree walk codegenerator generating safe C++ code.
 * The generated C++ is stored in a cross platform temporary location.
 * This generated C++ code is lated compiled using clang.
 * Or any compiler of choice.
 */
class CppBackend : public NodeVisitor, public BackendInterface {
  private:
  // CXX compiler front end.
  ClangFrontendInvoker m_inv;

  // Global symbol table used for quick symbol lookup.
  // Currently unused as the idea was to use it for interop.
  // SymbolTablePtr m_symbol_table;

  InteropBackends m_interop_backends;

  // TODO: Move terminate functionality in its own class to separate concerns.
  TerminateStack m_terminate;

  // Counter that is used to create unique identifier names.
  // Is incremented after each usage to prevent collision.
  u64 m_id_defer_count;

  protected:
  /*!
   * Generate the prologue for the generated C++ code.
   */
  auto prologue() -> std::string;

  /*!
   * Generate the epilogue for the generated C++ code.
   */
  auto epilogue() -> std::string;

  /*!
   * Determines if we are currently nested inside an expression.
   * Indicating if a semicolon should be inserted or not.
   */
  auto should_terminate() -> bool;

  /*!
   * Conditionally add a semicolon.
   */
  [[nodiscard("Pure method must use results")]]
  auto terminate() -> std::string_view;

  /*!
   * Resolve the given AST node to C++ code.
   *
   * @param[in] t_ptr AST node to convert to C++ code.
   * @param[in] t_terminate If the next direct node should end with a semicolon.
   *
   * @warn Throws an exception if it fails at converting the @ref Any.
   */
  [[nodiscard("Pure method must use results.")]]
  auto resolve(NodePtr t_ptr, bool t_terminate = true) -> std::string;

  public:
  CppBackend();

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
  auto visit(node::function::FunctionCall* t_fn_call) -> Any override;
  auto visit(node::function::ReturnType* t_rt) -> Any override;

  // Lvalue:
  auto visit(node::lvalue::Let* t_let) -> Any override;
  auto visit(node::lvalue::Var* t_var) -> Any override;
  auto visit(node::lvalue::Variable* t_var) -> Any override;

  // Meta:
  auto visit(node::meta::Attribute* t_attr) -> Any override;
  auto visit(node::meta::LetDecl* t_ldecl) -> Any override;
  auto visit(node::meta::VarDecl* t_vdecl) -> Any override;
  auto visit(node::meta::FunctionDecl* t_fdecl) -> Any override;

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

  auto visit(node::operators::Ternary* t_ternary) -> Any override;

  // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_module) -> Any override;

  // Rvalue:
  auto visit(node::rvalue::Float* t_float) -> Any override;
  auto visit(node::rvalue::Integer* t_int) -> Any override;
  auto visit(node::rvalue::String* t_str) -> Any override;
  auto visit(node::rvalue::Boolean* t_bool) -> Any override;

  // Typing:
  auto visit(node::typing::Method* t_meth) -> Any override;
  auto visit(node::typing::MethodCall* t_meth_call) -> Any override;
  auto visit(node::typing::Interface* t_ifc) -> Any override;
  auto visit(node::typing::MemberDecl* t_meth) -> Any override;
  auto visit(node::typing::Struct* t_struct) -> Any override;
  auto visit(node::typing::Self* t_self) -> Any override;
  auto visit(node::typing::Member* t_member) -> Any override;
  auto visit(node::typing::MemberAccess* t_access) -> Any override;

  // Misc:
  auto visit(node::List* t_list) -> Any override;
  auto visit(node::NodeInterface* t_node) -> Any override;

  // Util:
  //! CPP backend as of writing needs to refactor interop.
  auto register_interop_backend(InteropBackendType t_type) -> void override;

  /*!
   * Transpile the @ref t_ast to valid C++ code and write it to @ref t_out.
   */
  auto codegen(NodePtr t_ast, const fs::path& t_out) -> void;

  auto compile(CompileParams& t_params) -> void override;

  virtual ~CppBackend() = default;
};
} // namespace codegen::cpp_backend

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_CPP_BACKEND_HPP
