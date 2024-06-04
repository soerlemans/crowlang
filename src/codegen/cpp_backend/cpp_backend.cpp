#include "cpp_backend.hpp"

// Includes:
#include "../../ast/node/include_nodes.hpp"
#include "../../debug/log.hpp"
#include "../../lib/types.hpp"

// Local Includes:
#include "clang_frontend_invoker.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using namespace ast::visitor;

NODE_USING_ALL_NAMESPACES()

// Methods:
// Control:
auto CppBackend::visit([[maybe_unused]] If* t_if) -> Any
{
  // const auto condition{traverse(t_if->init_expr())};

  return {};
}

auto CppBackend::visit([[maybe_unused]] Loop* t_loop) -> Any
{
  return {};
}

AST_VISITOR_STUB(CppBackend, Continue)
AST_VISITOR_STUB(CppBackend, Break)

auto CppBackend::visit(Return* t_ret) -> Any
{
  write("{}", "return");
  traverse(t_ret->expr());
  write("{}", ";");

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

  // TODO: Some day resolve the TypeVariant, for now every method returns int.
  const auto ret_type{"int"};

  write("auto {}() -> {}", identifier, ret_type);
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
  const auto identifier{t_var->identifier()};

  write("{}", identifier);

  return {};
}

// Operators:
auto CppBackend::visit(Arithmetic* t_arith) -> Any
{
  using ast::node::operators::ArithmeticOp;

  // TODO: Cleanup/Move else where!
  switch(t_arith->op()) {
    case ArithmeticOp::POWER:
      break;

    case ArithmeticOp::MULTIPLY:
      break;

    case ArithmeticOp::DIVIDE:
      break;
    case ArithmeticOp::MODULO:
      break;

    case ArithmeticOp::ADD:
      traverse(t_arith->left());
      write("{}", "+");
      traverse(t_arith->right());
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

auto CppBackend::visit([[maybe_unused]] Comparison* t_comp) -> Any
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
// TODO: Implement
auto CppBackend::visit([[maybe_unused]] Float* t_float) -> Any
{

  return {};
}

auto CppBackend::visit(Integer* t_int) -> Any
{
  const auto value{t_int->get()};

  write("{}", value);

  return {};
}

// TODO: Implement
auto CppBackend::visit([[maybe_unused]] String* t_str) -> Any
{
  return {};
}

// TODO: Implement
auto CppBackend::visit([[maybe_unused]] Boolean* t_bool) -> Any
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
auto CppBackend::codegen(NodePtr t_ast, const path& t_out) -> void
{
  m_ofs.open(t_out);

  // Generate C++ code.
  traverse(t_ast);

  m_ofs.close();
}

auto CppBackend::compile(NodePtr t_ast) -> void
{
  const auto tmp_dir{lib::temporary_directory()};

  const auto tmp_src{tmp_dir / "main.cpp"};
  const auto tmp_obj{tmp_dir / "main.o"};

  const path bin{"main.out"};

  // Log stuff
  DBG_INFO("tmp_dir: ", tmp_dir);
  DBG_INFO("tmp_src: ", tmp_src);
  DBG_INFO("tmp_obj: ", tmp_obj);
  DBG_INFO("bin", bin);

  // Generate C++ source file.
  codegen(t_ast, tmp_src);

  // Invoke clang frontend to generate a binary.
  ClangFrontendInvoker inv{};
  inv.object(tmp_src, tmp_obj);
  // inv.link(tmp_obj, bin);

  DBG_CRITICAL("Binary was generated!: ", bin);
}
} // namespace codegen::cpp_backend
