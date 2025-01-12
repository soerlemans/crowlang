#include "cpp_backend.hpp"

// STL Includes:
#include <format>
#include <fstream>
#include <sstream>
#include <string_view>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"
#include "crow/exception/error.hpp"
#include "lib/types.hpp"

// Local Includes:
#include "clang_frontend_invoker.hpp"
#include "prototype_generator.hpp"
#include "type_variant2cpp_type.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;
using namespace std::literals::string_view_literals;

NODE_USING_ALL_NAMESPACES()

// Methods:
// Protected:
auto CppBackend::prologue() -> std::string
{
  std::stringstream ss;

  // Crow's native types often translate.
  // To C++ fixed width integers and floats.
  ss << "// STL Includes:\n";
  ss << "#include <cstdint>\n";
  // ss << "#include <stdfloat>\n"; // TODO: Uncommnet when supported by clang.
  ss << "\n";

  // FIXME: Temporary input for printing purposes.
  ss << "// Stdlibcrow Includes:\n";
  ss << R"(#include "stdlibcrow/io.hpp")" << '\n';
  ss << R"(#include "stdlibcrow/internal/defer.hpp")" << '\n';
  ss << "\n\n";

  ss << "// Aliases:\n";
  ss << "namespace stdinternal = stdlibcrow::internal;\n";

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

auto CppBackend::should_terminate() -> bool
{
  return m_terminate.top();
}

auto CppBackend::terminate() -> std::string_view
{
  auto terminate{";\n"sv};

  // Remove semicolon if we should not terminate.
  [[unlikely]]
  if(!should_terminate()) {
    terminate = "\n";
  }

  return terminate;
}

// TODO: Add inline option for direct resolution.
auto CppBackend::resolve(NodePtr t_ptr, const bool t_terminate) -> std::string
{
  using exception::error;

  std::stringstream ss;

  if(t_ptr) {
    // Keep track of if the current node we are traversing should be terminated.
    m_terminate.push(t_terminate);
    const auto any{traverse(t_ptr)};
    m_terminate.pop();

    try {
      ss << std::any_cast<std::string>(any);
    } catch(std::bad_any_cast& exception) {
      error(exception.what());
    }
  }

  return ss.str();
}

// Public:
CppBackend::CppBackend()
  : m_symbol_table{}, m_interop_backends{}, m_terminate{}, m_id_defer_count{0}
{}

// Control:
auto CppBackend::visit(If* t_if) -> Any
{
  const auto init_expr{resolve(t_if->init_expr(), false)};
  const auto cond{resolve(t_if->condition())};

  const auto then{resolve(t_if->then())};
  const auto alt{resolve(t_if->alt())};

  std::stringstream ss;

  ss << std::format("if({} {}) {{\n", init_expr, cond) << then;

  // Dont create else branch if we dont have a statement for it.
  if(!alt.empty()) {
    ss << "} else {\n" << alt;
  }

  ss << "}\n";

  return ss.str();
}

auto CppBackend::visit(Loop* t_loop) -> Any
{
  const auto init_expr{resolve(t_loop->init_expr(), false)};
  const auto cond{resolve(t_loop->condition())};

  const auto post_expr{resolve(t_loop->expr(), false)};
  const auto body{resolve(t_loop->body())};

  std::stringstream ss;

  // clang-format off
  ss << std::format("for({};{}; {} )", init_expr, cond, post_expr)
     << "{\n"
     << body
     << "}\n";
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

auto CppBackend::visit(Defer* t_defer) -> Any
{
  std::stringstream ss;

  const auto body{resolve(t_defer->body())};

  ss << std::format(
    "const stdinternal::Defer defer_object{}{{ [&](){{ {} }} }};\n",
    m_id_defer_count, body);

  m_id_defer_count++;

  return ss.str();
}

auto CppBackend::visit(Return* t_ret) -> Any
{
  const auto expr{resolve(t_ret->expr(), false)};

  return std::format("return {};\n", expr);
}

// Functions:
auto CppBackend::visit(Parameter* t_param) -> Any
{
  const auto id{t_param->identifier()};
  const auto type{t_param->type()};

  return std::format("{} {}", type, id);
}

auto CppBackend::visit(Function* t_fn) -> Any
{
  const auto identifier{t_fn->identifier()};

  const auto fn_type{t_fn->get_type().function()};
  const auto ret_type{type_variant2cpp_type(fn_type->m_return_type)};

  std::stringstream param_ss{};

  auto sep{""sv};
  const auto params{t_fn->params()};
  for(const auto& param : *params) {
    param_ss << sep << resolve(param);

    sep = ", ";
  }

  std::stringstream ss{};

  // clang-format off
  ss << std::format("auto {}({}) -> {}\n", identifier, param_ss.str(), ret_type)
     << "{\n"
     << resolve(t_fn->body())
     << "}\n";
  // clang-format on

  return ss.str();
}

auto CppBackend::visit(Call* t_call) -> Any
{
  // FIXME: When get non shitty import resolution.
  // const auto identifier{t_call->identifier()};
  auto identifier{t_call->identifier()};
  const auto args{t_call->args()};

  // Temporary measures (I fucking hope).
  if(identifier == "print") {
    identifier = "stdlibcrow::print";
  } else if(identifier == "println") {
    identifier = "stdlibcrow::println";
  }

  // FIXME: This wont work for a raw function or method call.
  // As when we assign it directly to a variable it will work but not else.
  // As we need to append a semicolon.

  // FIXME: Figure out a way to detect if this function call is inline.
  // Or if this function is being called without as a statement.
  // (I hope this is doable).

  std::stringstream ss{};
  std::string_view sep{""};

  for(const auto& ptr : *args) {
    const auto argument{resolve(ptr, false)};
    ss << sep << argument;

    sep = ", ";
  }

  const auto arguments{ss.str()};

  return std::format("{}({}){}", identifier, arguments, terminate());
}

auto CppBackend::visit([[maybe_unused]] ReturnType* t_rt) -> Any
{
  // Currently we do not dynamically compute return types.
  // So for now converting a type_variant2cpp_type() is good enough.

  return {};
}

// Lvalue:
// TODO: Reduce code duplication between the Let and Var methods.
auto CppBackend::visit(Let* t_let) -> Any
{
  const auto identifier{t_let->identifier()};
  const auto init_expr{resolve(t_let->init_expr())};

  const auto type_variant{t_let->get_type()};
  const auto type{type_variant2cpp_type(type_variant)};

  const auto terminate_str{terminate()};

  return std::format("const {} {}{{ {} }}{}", type, identifier, init_expr,
                     terminate_str);
}

auto CppBackend::visit(Var* t_var) -> Any
{
  const auto identifier{t_var->identifier()};
  const auto init_expr{resolve(t_var->init_expr())};

  const auto type_variant{t_var->get_type()};
  const auto type{type_variant2cpp_type(type_variant)};

  const auto terminate_str{terminate()};

  return std::format("{} {}{{ {} }}{}", type, identifier, init_expr,
                     terminate_str);
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
  const auto terminate_str{terminate()};

  return std::format("{}++{}", left, terminate_str);
}

auto CppBackend::visit(Decrement* t_dec) -> Any
{
  const auto left{resolve(t_dec->left())};
  const auto terminate_str{terminate()};

  return std::format("{}--{}", left, terminate_str);
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

  return std::format("\"{}\"", value);
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

auto CppBackend::compile(AstPack t_pack, path t_stem) -> void
{
  const auto tmp_dir{lib::temporary_directory()};
  const path tmp_src{tmp_dir / t_stem.concat(".cpp")};

  const auto& [ast, symbol_table] = t_pack;
  m_symbol_table = symbol_table;

  // Log filepath's:
  DBG_INFO("tmp_dir: ", tmp_dir);
  DBG_INFO("tmp_src: ", tmp_src);

  // Generate C++ source file.
  codegen(ast, tmp_src);

  // Invoke clang frontend to generate a binary.
  ClangFrontendInvoker inv{};
  inv.compile(tmp_src);

  // Clear members, for next compilation.
  m_symbol_table.reset();
  m_terminate = {};
  m_id_defer_count = 0;
}
} // namespace codegen::cpp_backend
