#include "cpp_backend.hpp"

// STL Includes:
#include <iostream>
#include <optional>
#include <vector>

// Library Includes:
#include <boost/filesystem.hpp>

// Includes:
#include "../../ast/node/include_nodes.hpp"
#include "../../debug/log.hpp"
#include "../../lib/types.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;

NODE_USING_ALL_NAMESPACES()

// Methods:
CppBackend::CppBackend()
{}

// Control:
auto CppBackend::visit(If* t_if) -> Any
{}

auto CppBackend::visit(Loop* t_loop) -> Any
{}

AST_VISITOR_STUB(CppBackend, Continue)
AST_VISITOR_STUB(CppBackend, Break)

auto CppBackend::visit(Return* t_ret) -> Any
{}

// Functions:
auto CppBackend::visit([[maybe_unused]] Parameter* t_param) -> Any
{}

auto CppBackend::visit(Function* t_fn) -> Any
{}

AST_VISITOR_STUB(CppBackend, Call)
AST_VISITOR_STUB(CppBackend, ReturnType)

// Lvalue:
AST_VISITOR_STUB(CppBackend, Let)
AST_VISITOR_STUB(CppBackend, Var)
AST_VISITOR_STUB(CppBackend, Variable)

// Operators:
auto CppBackend::visit(Arithmetic* t_arith) -> Any
{}

AST_VISITOR_STUB(CppBackend, Assignment)

auto CppBackend::visit(Comparison* t_comp) -> Any
{}

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
{}

auto CppBackend::visit(Integer* t_int) -> Any
{}

// TODO: Implement
auto CppBackend::visit([[maybe_unused]] String* t_str) -> Any
{
  return {};
}

auto CppBackend::visit(Boolean* t_bool) -> Any
{}

// Typing:
AST_VISITOR_STUB(CppBackend, MethodDecl)
AST_VISITOR_STUB(CppBackend, Interface)
AST_VISITOR_STUB(CppBackend, MemberDecl)
AST_VISITOR_STUB(CppBackend, Struct)
AST_VISITOR_STUB(CppBackend, Impl)
AST_VISITOR_STUB(CppBackend, DotExpr)

// Util:
auto CppBackend::codegen(NodePtr t_ast) -> void
{
  using namespace boost::filesystem;

  path temp = unique_path();
  path temp_dir = temp_directory_path();

  DBG_PRINTLN(temp.native());
  DBG_PRINTLN(temp_dir.native());
}

auto CppBackend::compile(const fs::path t_path) -> void
{}
} // namespace codegen::cpp_backend
