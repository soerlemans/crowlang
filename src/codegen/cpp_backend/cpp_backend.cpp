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
  return {};
}

// Functions:
auto CppBackend::visit([[maybe_unused]] Parameter* t_param) -> Any
{
  return {};
}

auto CppBackend::visit(Function* t_fn) -> Any
{
  write("auto {}", "Test");

  return {};
}

AST_VISITOR_STUB(CppBackend, Call)
AST_VISITOR_STUB(CppBackend, ReturnType)

// Lvalue:
AST_VISITOR_STUB(CppBackend, Let)
AST_VISITOR_STUB(CppBackend, Var)
AST_VISITOR_STUB(CppBackend, Variable)

// Operators:
auto CppBackend::visit(Arithmetic* t_arith) -> Any
{
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

  m_ofs.open(tmp_dir);

  traverse(t_ast);

  m_ofs.close();
}

auto CppBackend::compile(const fs::path t_path) -> void
{}
} // namespace codegen::cpp_backend
