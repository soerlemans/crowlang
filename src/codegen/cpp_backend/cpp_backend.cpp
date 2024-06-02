#include "cpp_backend.hpp"

// STL Includes:
#include <iostream>
#include <optional>
#include <vector>

// Includes:
#include "../../ast/node/include_nodes.hpp"
#include "../../debug/log.hpp"
#include "../../lib/temporary_directory.hpp"
#include "../../lib/types.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;

NODE_USING_ALL_NAMESPACES()

// Methods:
// Control:
auto CppBackend::visit(If* t_if) -> Any
{
  // const auto condition{traverse(t_if->init_expr())};

  return {};
}

auto CppBackend::visit(Loop* t_loop) -> Any
{
  return {};
}

AST_VISITOR_STUB(CppBackend, Continue)
AST_VISITOR_STUB(CppBackend, Break)

auto CppBackend::visit(Return* t_ret) -> Any
{
  // const auto result
  //  traverse(t_ret->expr());

  // write("return {};", );

  return {};
}

// Functions:
auto CppBackend::visit([[maybe_unused]] Parameter* t_param) -> Any
{
  return {};
}

auto CppBackend::visit(Function* t_fn) -> Any
{
  const auto identifier{t_fn->identifier()};

  write("auto {}() -> void", identifier);
  write("{}", "{");

  // Generate code for the body.
  traverse(t_fn->body());

  write("{}", "}");

  return {};
}

AST_VISITOR_STUB(CppBackend, Call)
AST_VISITOR_STUB(CppBackend, ReturnType)

// Lvalue:
AST_VISITOR_STUB(CppBackend, Let)

auto CppBackend::visit(Var* t_var) -> Any
{
  const auto identifier{t_var->identifier()};

  write("auto {}{{", identifier);
  traverse(t_var->init_expr());
  write("}};");

  return {};
}

auto CppBackend::visit(Variable* t_var) -> Any
{
  return {};
}

// Operators:
auto CppBackend::visit(Arithmetic* t_arith) -> Any
{
  using ast::node::operators::ArithmeticOp;

  switch(t_arith->op()) {
    case ArithmeticOp::POWER:
      write("{}", "+");
      break;
    case ArithmeticOp::MULTIPLY:
      break;
    case ArithmeticOp::DIVIDE:
      break;
    case ArithmeticOp::MODULO:
      break;

    case ArithmeticOp::ADD:
      break;
    case ArithmeticOp::SUBTRACT:
      break;

    default:
      // TODO: Throw.
      break;
  }

  return {};
}

AST_VISITOR_STUB(CppBackend, Assignment)

auto CppBackend::visit(Comparison* t_comp) -> Any
{
  return {};
}

AST_VISITOR_STUB(CppBackend, Increment)
AST_VISITOR_STUB(CppBackend, Decrement)
AST_VISITOR_STUB(CppBackend, UnaryPrefix)

// Logical:
AST_VISITOR_STUB(CppBackend, Not)
AST_VISITOR_STUB(CppBackend, And)

auto CppBackend::visit([[maybe_unused]] Or* t_or) -> Any
{
  return {};
}

AST_VISITOR_STUB(CppBackend, Ternary)

// Packaging:
AST_VISITOR_STUB(CppBackend, Import)
AST_VISITOR_STUB(CppBackend, ModuleDecl)

// RValue:
auto CppBackend::visit(Float* t_float) -> Any
{

  return {};
}

auto CppBackend::visit(Integer* t_int) -> Any
{
  return {};
}

// TODO: Implement
auto CppBackend::visit([[maybe_unused]] String* t_str) -> Any
{
  return {};
}

auto CppBackend::visit(Boolean* t_bool) -> Any
{
  return {};
}

// Typing:
AST_VISITOR_STUB(CppBackend, MethodDecl)
AST_VISITOR_STUB(CppBackend, Interface)
AST_VISITOR_STUB(CppBackend, MemberDecl)
AST_VISITOR_STUB(CppBackend, Struct)
AST_VISITOR_STUB(CppBackend, Impl)
AST_VISITOR_STUB(CppBackend, DotExpr)

// Util:
/*!
 * Transpile the AST to valid C++ code.
 * The C++ source is stored in a temporary directory.
 */
auto CppBackend::codegen(NodePtr t_ast) -> void
{
  const auto tmp_dir{lib::temporary_directory()};
  DBG_INFO("tmp_dir: ", std::quoted(tmp_dir.native()));

  const auto tmp_src{tmp_dir / "main.cpp"};

  m_ofs.open(tmp_src);

  traverse(t_ast);

  m_ofs.close();
}

auto CppBackend::compile(const fs::path t_path) -> void
{}
} // namespace codegen::cpp_backend
