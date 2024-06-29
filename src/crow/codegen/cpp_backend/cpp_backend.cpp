#include "cpp_backend.hpp"

// STL Includes:
#include <format>
#include <fstream>
#include <sstream>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"
#include "crow/exception/error.hpp"
#include "lib/types.hpp"

// Local Includes:
#include "clang_frontend_invoker.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;

NODE_USING_ALL_NAMESPACES()

// Methods:
// Protected:
auto CppBackend::header() -> std::string
{
  std::stringstream ss;

  // TODO: Include necessary includes and boiler plate, for the generated code
  // to work.

  return ss.str();
}

auto CppBackend::prototypes() -> std::string
{
  std::stringstream ss;

  return ss.str();
}

auto CppBackend::resolve(NodePtr t_ptr) -> std::string
{
  using exception::error;

  std::stringstream ss;

  if(t_ptr) {
    const auto any{traverse(t_ptr)};

    try {
      ss << std::any_cast<std::string>(any);
    } catch(std::bad_any_cast& exception) {
      error(exception.what());
    }
  }

  return ss.str();
}

// Public:
// Control:
auto CppBackend::visit([[maybe_unused]] If* t_if) -> Any
{
  const auto init_expr{resolve(t_if->init_expr())};
  const auto cond{resolve(t_if->condition())};

  const auto then{resolve(t_if->init_expr())};
  const auto alt{resolve(t_if->init_expr())};

  std::stringstream ss;

  // clang-format off
	ss << std::format("if({}; {}) {{\n", init_expr, cond)
		 << then
		 << "} else {\n"
		 << alt
		 << "}\n";
  // clang-format on

  return ss.str();
}

auto CppBackend::visit([[maybe_unused]] Loop* t_loop) -> Any
{
  return {};
}

AST_VISITOR_STUB(CppBackend, Continue)
AST_VISITOR_STUB(CppBackend, Break)

auto CppBackend::visit(Return* t_ret) -> Any
{
  std::stringstream ss;

  ss << std::format("return {};\n", resolve(t_ret->expr()));

  return ss.str();
}

// Functions:
auto CppBackend::visit([[maybe_unused]] Parameter* t_param) -> Any
{
  return {};
}

auto CppBackend::visit(Function* t_fn) -> Any
{
  const auto identifier{t_fn->identifier()};

  // TODO: Some day resolve the TypeVariant, for now every method returns int.
  const auto ret_type{"int"};

  std::stringstream ss;

  // clang-format off
  ss << std::format("auto {}() -> {}\n", identifier, ret_type)
     << "{\n"
		 << resolve(t_fn->body())
		 << "}\n";
  // clang-format on

  return ss.str();
}

auto CppBackend::visit(Call* t_call) -> Any
{

	return {};
}

AST_VISITOR_STUB(CppBackend, ReturnType)

// Lvalue:
AST_VISITOR_STUB(CppBackend, Let)

auto CppBackend::visit(Var* t_var) -> Any
{
  const auto identifier{t_var->identifier()};
  const auto init_expr{resolve(t_var->init_expr())};

  return std::format("auto {}{{ {} }};\n", identifier, init_expr);
}

auto CppBackend::visit(Variable* t_var) -> Any
{
  const auto identifier{t_var->identifier()};

  return std::format("{}", identifier);
}

// Operators:
auto CppBackend::visit(Arithmetic* t_arith) -> Any
{

  const auto op{t_arith->op2str()};

  const auto left{resolve(t_arith->left())};
  const auto right{resolve(t_arith->right())};

  // We surround the sub expressions in parenthesis to enforce the precedence,
  // Of Crow over C++.
  return std::format("({}) {} ({})", left, op, right);
}

auto CppBackend::visit(Assignment* t_assign) -> Any
{

  const auto op{t_assign->op2str()};

  const auto left{resolve(t_assign->left())};
  const auto right{resolve(t_assign->right())};

  return std::format("{} {} {};\n", left, op, right);
}

auto CppBackend::visit(Comparison* t_comp) -> Any
{
  const auto op{t_comp->op2str()};

  const auto left{resolve(t_comp->left())};
  const auto right{resolve(t_comp->right())};

  return std::format("({}) {} ({})", left, op, right);
}

AST_VISITOR_STUB(CppBackend, Increment)
AST_VISITOR_STUB(CppBackend, Decrement)

auto CppBackend::visit(UnaryPrefix* t_up) -> Any
{
  const auto op{t_up->op2str()};
  const auto left{resolve(t_up->left())};

  return std::format("({}{})", op, left);
}

// Logical:
auto CppBackend::visit(Not* t_not) -> Any
{
  const auto left{resolve(t_not->left())};

  return std::format("(!{})", left);
}

auto CppBackend::visit(And* t_and) -> Any
{
  const auto left{resolve(t_and->left())};
  const auto right{resolve(t_and->right())};

  return std::format("({}) && ({})", left, right);
}

auto CppBackend::visit(Or* t_or) -> Any
{
  const auto left{resolve(t_or->left())};
  const auto right{resolve(t_or->right())};

  return std::format("({}) || ({})", left, right);
}

auto CppBackend::visit([[maybe_unused]] Ternary* t_ternary) -> Any
{
  // const auto left{resolve(t_or->left())};
  // const auto right{resolve(t_or->right())};

  //  return std::format("({}) ? ({}) : ({})", left, right);

  return {};
}


// Packaging:
AST_VISITOR_STUB(CppBackend, Import)
AST_VISITOR_STUB(CppBackend, ModuleDecl)

// RValue:
auto CppBackend::visit([[maybe_unused]] Float* t_float) -> Any
{
  const auto value{t_float->get()};

  return std::format("{}", value);
}

auto CppBackend::visit(Integer* t_int) -> Any
{
  const auto value{t_int->get()};

  return std::format("{}", value);
}

auto CppBackend::visit([[maybe_unused]] String* t_str) -> Any
{
  const auto value{t_str->get()};

  return std::format("{}", value);
}

auto CppBackend::visit([[maybe_unused]] Boolean* t_bool) -> Any
{
  const auto value{t_bool->get()};

  return std::format("{}", value);
}

// Typing:
AST_VISITOR_STUB(CppBackend, MethodDecl)
AST_VISITOR_STUB(CppBackend, Interface)
AST_VISITOR_STUB(CppBackend, MemberDecl)
AST_VISITOR_STUB(CppBackend, Struct)
AST_VISITOR_STUB(CppBackend, Impl)
AST_VISITOR_STUB(CppBackend, DotExpr)

// Misc:
auto CppBackend::visit(List* t_list) -> Any
{
  std::stringstream ss;

  for(NodePtr& node : *t_list) {
    ss << resolve(node);
  }

  return ss.str();
}

// Util:
auto CppBackend::codegen(NodePtr t_ast, const path& t_out) -> void
{
  std::ofstream ofs{t_out};

  // Generate C++ code.
  ofs << resolve(t_ast);
}

auto CppBackend::compile(NodePtr t_ast) -> void
{
  const auto tmp_dir{lib::temporary_directory()};
  const path tmp_src{tmp_dir / "main.cpp"};

  // Log stuff:
  DBG_INFO("tmp_dir: ", tmp_dir);
  DBG_INFO("tmp_src: ", tmp_src);

  // Generate C++ source file.
  codegen(t_ast, tmp_src);

  // Invoke clang frontend to generate a binary.
  ClangFrontendInvoker inv{};
  inv.compile(tmp_src);
}
} // namespace codegen::cpp_backend
