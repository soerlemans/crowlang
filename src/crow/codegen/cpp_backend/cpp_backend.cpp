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
#include "prototype_generator.hpp"
#include "type_data2cpp_type.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;

NODE_USING_ALL_NAMESPACES()

// Methods:
// Protected:
auto CppBackend::prologue() -> std::string
{
  std::stringstream ss;

  // Crow's native types often translate.
  // To C++ fixed width integers and floats.
  ss << "#include <cstdint>\n";
  // ss << "#include <stdfloat>\n"; // Uncomment when support by clang libc++.

  return ss.str();
}

auto CppBackend::epilogue() -> std::string
{
  std::stringstream ss;

  return ss.str();
}

auto CppBackend::prototypes(NodePtr t_ast) -> std::string
{
  PrototypeGenerator generator{};

  return generator.generate(t_ast);
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

auto CppBackend::visit(Loop* t_loop) -> Any
{
  const auto init_expr{resolve(t_loop->init_expr())};
  const auto cond{resolve(t_loop->condition())};

  const auto post_expr{resolve(t_loop->expr())};
  const auto body{resolve(t_loop->body())};

  std::stringstream ss;

  // FIXME: The eval_expr in the loop_statement grammar.
  // Can contain multiple semicolons.
  // Same applies to post_expr as postcrement and assignment add a semicolon.
  // This can mess up the code generation.

  // clang-format off
  // Here is an ugly temporary solution/workaround:
  ss << "{\n"
     << std::format("{};\n", init_expr)
     << std::format("for(;{}; [&]() {{ return {} }}() ) {{\n", cond, post_expr)
     << body
     << "}\n"
     << "}\n";

  /* TODO: Get the more elegant solution to work.
  ss << std::format("for({}; {}; {}) {{\n", init_expr, cond, expr)
     << body
     << "}\n";
  */
  // clang-format on

  return ss.str();
}

auto CppBackend::visit([[maybe_unused]] Continue* t_continue) -> Any
{
  return std::format("continue;\n");
}

auto CppBackend::visit([[maybe_unused]] Break* t_break) -> Any
{
  return std::format("break;\n");
}

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

auto CppBackend::visit([[maybe_unused]] Call* t_call) -> Any
{
  // const auto identifier{resolve(t_call->identifier())};

  // FIXME: This wont work for a raw function or method call.
  // As when we assign it directly to a variable it will work but not else.
  // As we need to append a semicolon.

  // return std::format("{}()", identifier);

  return {}; // TODO: Implement correctly.
}

AST_VISITOR_STUB(CppBackend, ReturnType)

// Lvalue:
auto CppBackend::visit(Let* t_let) -> Any
{
  const auto identifier{t_let->identifier()};
  const auto init_expr{resolve(t_let->init_expr())};

  const auto type_variant{t_let->get_type()};
  const auto type{type_data2cpp_type(type_variant)};

  return std::format("const {} {}{{ {} }};\n", type, identifier, init_expr);
}

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

auto CppBackend::visit(Increment* t_inc) -> Any
{
  const auto left{resolve(t_inc->left())};

  return std::format("{}++;\n", left);
}

auto CppBackend::visit(Decrement* t_dec) -> Any
{
  const auto left{resolve(t_dec->left())};

  return std::format("{}--;\n", left);
}

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

  // Generate header includes basic typedefinitions and similar.
  ofs << "// Prologue:\n";
  ofs << prologue() << '\n';

  // Generate forward declarations, to make code position independent.
  ofs << "// Protoypes:\n";
  ofs << prototypes(t_ast) << '\n';

  // Generate C++ code.
  ofs << "// C++ code:\n";
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
