#include "cpp_backend.hpp"

// STL Includes:
#include <format>
#include <fstream>
#include <sstream>
#include <string_view>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/codegen/cpp_backend/interop/python_backend/python_backend.hpp"
#include "crow/debug/log.hpp"
#include "lib/stdexcept/stdexcept.hpp"
#include "lib/stdtypes.hpp"

// Local Includes:
#include "clang_frontend_invoker.hpp"
#include "type2cpp.hpp"

namespace codegen::cpp_backend {
// Using:
using namespace ast::visitor;
using namespace std::literals::string_view_literals;

NODE_USING_ALL_NAMESPACES()

// Methods:
// Protected:
auto CppBackend::prologue() -> std::string
{
  std::stringstream ss{};

  // Crow's native types often translate.
  // To C++ fixed width integers and floats.
  ss << "// STL Includes:\n";
  ss << "#include <cstdint>\n";
  // ss << "#include <stdfloat>\n"; // TODO: Uncommnet when supported by clang.
  ss << "\n";

  // FIXME: Temporary input for printing purposes.
  ss << "// Stdlibcrow Includes:\n";
  ss << R"(#include "stdlibcrow/io.hpp")" << '\n';
  ss << R"(#include "stdlibcrow/internal/defer.hpp")" << "\n\n";

  // Loop through the interop backends and add the prologue from each backend.
  for(auto& ptr : m_interop_backends) {
    ss << ptr->prologue();
  }

  ss << "\n\n";

  ss << "// Aliases:\n";
  ss << "namespace stdinternal = stdlibcrow::internal;\n";

  return ss.str();
}

auto CppBackend::epilogue() -> std::string
{
  std::stringstream ss{};

  // Loop through the interop backends and add the epilogue.
  for(auto& ptr : m_interop_backends) {
    ss << ptr->epilogue();
  }

  return ss.str();
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
  std::stringstream ss{};

  if(t_ptr) {
    // Keep track of if the current node we are traversing should be terminated.
    m_terminate.push(t_terminate);
    const auto any{traverse(t_ptr)};
    m_terminate.pop();

    try {
      ss << std::any_cast<std::string>(any);
    } catch(std::bad_any_cast& exception) {
      lib::stdexcept::throw_bad_any_cast(exception.what());
    }
  }

  return ss.str();
}

// Public:
CppBackend::CppBackend()
  : m_inv{}, m_interop_backends{}, m_terminate{}, m_id_defer_count{0}
{}

// Control:
auto CppBackend::visit(If* t_if) -> Any
{
  const auto init_expr{resolve(t_if->init_expr(), false)};
  const auto cond{resolve(t_if->condition())};

  const auto then{resolve(t_if->then())};
  const auto alt{resolve(t_if->alt())};

  std::stringstream ss{};

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

  std::stringstream ss{};

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
  std::stringstream ss{};

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
  const auto type{type_variant2cpp(t_param->get_type())};

  return std::format("{} {}", type, id);
}

auto CppBackend::visit(Function* t_fn) -> Any
{
  using node::node_traits::AttributeType;

  const auto identifier{t_fn->identifier()};

  const auto fn_type{t_fn->get_type().as_function()};
  const auto ret_type{type_variant2cpp(fn_type->m_return_type)};

  std::stringstream param_ss{};

  auto sep{""sv};
  const auto params{t_fn->params()};
  for(const auto& param : *params) {
    param_ss << sep << resolve(param);

    sep = ", ";
  }

  std::stringstream ss{};

  // Attribute insertion:
  const auto attrs{t_fn->get_attributes()};
  for(const auto& attr : attrs) {
    if(attr.m_type == AttributeType::INLINE) {
      ss << "inline\n";
    }
  }

  // clang-format off
  ss << std::format("auto {}({}) -> {}\n", identifier, param_ss.str(), ret_type)
     << "{\n"
     << resolve(t_fn->body())
     << "}\n";
  // clang-format on

  // FIXME: We should do this by looping through the toplevel.
  // Of the SymbolTable instead.
  // Register function to interop backend.
  for(auto& ptr : m_interop_backends) {
    ptr->register_function(identifier);
  }

  return ss.str();
}

auto CppBackend::visit(FunctionCall* t_call) -> Any
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
  std::stringstream ss{};

  // Currently we do not dynamically compute return types.
  // So for now converting a type_variant2cpp() is good enough.

  return ss.str();
}

// Lvalue:
// TODO: Reduce code duplication between the Let and Var methods.
auto CppBackend::visit(Let* t_let) -> Any
{
  const auto identifier{t_let->identifier()};
  const auto init_expr{resolve(t_let->init_expr(), false)};

  const auto type_variant{t_let->get_type()};
  const auto type{type_variant2cpp(type_variant)};

  const auto terminate_str{terminate()};

  return std::format("const {} {}{{ {} }}{}", type, identifier, init_expr,
                     terminate_str);
}

auto CppBackend::visit(Var* t_var) -> Any
{
  const auto identifier{t_var->identifier()};
  const auto init_expr{resolve(t_var->init_expr(), false)};

  const auto type_variant{t_var->get_type()};
  const auto type{type_variant2cpp(type_variant)};

  const auto terminate_str{terminate()};

  return std::format("{} {}{{ {} }}{}", type, identifier, init_expr,
                     terminate_str);
}

auto CppBackend::visit(Variable* t_var) -> Any
{
  const auto identifier{t_var->identifier()};

  return std::format("{}", identifier);
}

// Meta:
auto CppBackend::visit(Attribute* t_attr) -> Any
{
  using node::node_traits::AttributeType;

  std::stringstream ss{};

  const auto id{t_attr->identifier()};
  const auto params{t_attr->params()};
  const auto body{t_attr->body()};

  // TODO: This should probably be somewhere else.
  // Also we should not allow the extern attribute, inside of function bodies.
  const auto attrs{t_attr->get_attributes()};
  for(const auto& attr : attrs) {
    switch(attr.m_type) {
      case AttributeType::EXTERN:
        // clang-format off
      ss << R"(extern "C" {)" << "\n"
				 << resolve(body)
				 << "}\n";
        // clang-format on
        break;

      default:
        // Walk the body like normal.
        ss << resolve(body);
        break;
    }
  }

  return ss.str();
}

auto CppBackend::visit(LetDecl* t_ldecl) -> Any
{
  const auto identifier{t_ldecl->identifier()};

  const auto type_variant{t_ldecl->get_type()};
  const auto type{type_variant2cpp(type_variant)};

  return std::format("extern const {} {};\n", type, identifier);
}

auto CppBackend::visit(VarDecl* t_vdecl) -> Any
{
  const auto identifier{t_vdecl->identifier()};

  const auto type_variant{t_vdecl->get_type()};
  const auto type{type_variant2cpp(type_variant)};

  return std::format("extern {} {};\n", type, identifier);
}

auto CppBackend::visit(FunctionDecl* t_fdecl) -> Any
{
  const auto identifier{t_fdecl->identifier()};

  const auto fn_type{t_fdecl->get_type().as_function()};
  const auto ret_type{type_variant2cpp(fn_type->m_return_type)};

  std::stringstream param_ss{};

  auto sep{""sv};
  const auto params{t_fdecl->params()};
  for(const auto& param : *params) {
    param_ss << sep << resolve(param);

    sep = ", ";
  }

  return std::format("auto {}({}) -> {};\n", identifier, param_ss.str(),
                     ret_type);
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

  const auto left{resolve(t_assign->left(), false)};
  const auto right{resolve(t_assign->right(), false)};

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

auto CppBackend::visit(AddressOf* t_addr_of) -> Any
{
  const auto left{resolve(t_addr_of->left())};

  return std::format("&({})", left);
}

auto CppBackend::visit(Dereference* t_deref) -> Any
{
  const auto left{resolve(t_deref->left())};

  return std::format("*({})", left);
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

  return std::string{};
}

// Packaging:
AST_VISITOR_STUB(CppBackend, Import)

auto CppBackend::visit([[maybe_unused]] ModuleDecl* t_module) -> Any
{
  // Have prototypegenerator handle this?

  // TODO: Do something with this.
  // Wrap everything in namespace?
  // Also make main a special module?

  // DBG_WARNING("CppBackend: ModuleDecl needs to be implemented.");

  return std::string{};
}

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

// User Types:
auto CppBackend::visit(Method* t_meth) -> Any
{
  using node::node_traits::AttributeType;

  const auto identifier{t_meth->identifier()};
  const auto receiver_type{t_meth->get_receiver()};

  const auto meth_type{t_meth->get_type().as_function()};
  const auto ret_type{type_variant2cpp(meth_type->m_return_type)};

  std::stringstream param_ss{};

  auto sep{""sv};
  const auto params{t_meth->params()};
  for(const auto& param : *params) {
    param_ss << sep << resolve(param);

    sep = ", ";
  }

  std::stringstream ss{};

  // Attribute insertion:
  const auto attrs{t_meth->get_attributes()};
  for(const auto& attr : attrs) {
    if(attr.m_type == AttributeType::INLINE) {
      ss << "inline\n";
    }
  }

  // clang-format off
  ss << std::format("auto {}::{}({}) -> {}\n", receiver_type, identifier, param_ss.str(), ret_type)
     << "{\n"
     << resolve(t_meth->body())
     << "}\n";
  // clang-format on

  // FIXME: We should do this by looping through the toplevel.
  // Of the SymbolTable instead.
  // Register function to interop backend.
  // for(auto& ptr : m_interop_backends) {
  //   ptr->register_function(identifier);
  // }

  return ss.str();
}

auto CppBackend::visit(MethodCall* t_meth_call) -> Any
{
  // FIXME: When get non shitty import resolution.
  // const auto identifier{t_meth_call->identifier()};
  auto identifier{t_meth_call->identifier()};
  const auto args{t_meth_call->args()};

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


AST_VISITOR_STUB(CppBackend, Interface)

auto CppBackend::visit(MemberDecl* t_member) -> Any
{
  const auto identifier{t_member->identifier()};
  const auto type{type_variant2cpp(t_member->get_type())};

  return std::format("{} {};\n", type, identifier);
}

auto CppBackend::visit(Struct* t_struct) -> Any
{
  const auto identifier{t_struct->identifier()};
  const auto members{t_struct->body()};

  const auto struct_type{t_struct->get_type().as_struct()};
  const auto& methods{struct_type->m_methods};

  std::stringstream ss{};

  ss << std::format("struct {} {{\n", identifier);
  ss << resolve(members);


  ss << "// Methods:\n";

  for(auto& [meth_identifier, method] : methods) {
    const auto meth_type{method.as_function()};

    const auto ret_type{type_variant2cpp(meth_type->m_return_type)};

    std::stringstream param_ss{};

    auto sep{""sv};
    const auto params{meth_type->m_params};
    for(const auto& param : params) {
      param_ss << sep << type_variant2cpp(param);

      sep = ", ";
    }

    ss << std::format("auto {}({}) -> {};\n", meth_identifier, param_ss.str(),
                      ret_type);
  }

  ss << "};\n";

  return ss.str();
}

auto CppBackend::visit([[maybe_unused]] Self* t_self) -> Any
{
  return std::string{"(*this)"};
}

auto CppBackend::visit(Member* t_member) -> Any
{
  const auto identifier{t_member->identifier()};

  return std::format("{}", identifier);
}

auto CppBackend::visit(MemberAccess* t_access) -> Any
{
  const auto lhs{resolve(t_access->left())};
  const auto rhs{resolve(t_access->right(), false)};

  return std::format("{}.{}{}", lhs, rhs, terminate());
}

// Misc:
auto CppBackend::visit(List* t_list) -> Any
{
  std::stringstream ss{};

  for(NodePtr& node : *t_list) {
    ss << resolve(node);
  }

  return ss.str();
}

auto CppBackend::visit([[maybe_unused]] NodeInterface* t_node) -> Any
{
  // We only call this method if we have not overriden.
  // The visit method for that AST node.
  RUNTIME_ERROR("Unimplemented visit() method for AST node.");

  return {};
}

// Util:
auto CppBackend::register_interop_backend(const InteropBackendType t_type)
  -> void
{
  namespace py_interop = cpp_backend::interop::python_backend;

  CppInteropBackendPtr ptr{};

  switch(t_type) {
    case InteropBackendType::PYTHON_INTEROP_BACKEND:
      ptr = std::make_shared<py_interop::PythonBackend>();

      // Add compiler flags for compiling python3 support.
      m_inv.add_flags("-shared -fPIC $(python3 -m pybind11 --includes)");

      // TODO: Find a cleaner way to utilize environment variables.
      // Maybe register environment variables for later usage.

      // Set the out file (SRC_STEM is set in ClangFrontendInvoker).
      // clang-format off
      // m_inv.set_out("crowlang_${SRC_STEM:-cpython}_export$(python3-config --extension-suffix)");
      // clang-format on
      m_inv.set_out("crowlang_export$(python3-config "
                    "--extension-suffix)");
      break;

      // case InteropBackendType::LUA_INTEROP_BACKEND:
      //   break;

      // Fallthrough all the way to default.
    case InteropBackendType::C_INTEROP_BACKEND:
      [[fallthrough]];
    case InteropBackendType::LUA_INTEROP_BACKEND:
      [[fallthrough]];
    case InteropBackendType::JS_INTEROP_BACKEND: {
      const auto err_msg{std::format(
        "Unsupported interopability backend \"{}\" for C++ backend.",
        interopbackendtype2str(t_type))};
      throw std::invalid_argument{err_msg};
      break;
    }

    default: {
      const auto err_msg{
        std::format("Unknown interopability backend \"{}\" for C++ backend",
                    interopbackendtype2str(t_type))};
      throw std::invalid_argument{err_msg};
      break;
    }
  }

  // Add the backend at the end.
  m_interop_backends.emplace_back(ptr);
}

auto CppBackend::codegen(NodePtr t_ast, const fs::path& t_out) -> void
{
  std::ofstream ofs{t_out};

  // Generate header includes basic typedefinitions and similar.
  ofs << "// Prologue:\n";
  ofs << prologue() << '\n';

  // Generate forward declarations, to make code position independent.
  // ofs << "// Protoypes:\n";
  // ofs << "// TODO: Implement." << '\n';

  // Generate C++ code.
  ofs << "// C++ code:\n";
  ofs << resolve(t_ast);

  ofs << "// Epilogue:\n";
  ofs << epilogue() << '\n';
}

auto CppBackend::compile(CompileParams& t_params) -> void
{
  const auto& [ast, mir, build_dir, source_path] = t_params;

  fs::path stem{source_path.stem()};
  const fs::path tmp_src{build_dir / stem.concat(".cpp")};

  // Log filepath's:
  DBG_INFO("build_dir: ", build_dir);
  DBG_INFO("tmp_src: ", tmp_src);

  // Generate C++ source file.
  codegen(ast, tmp_src);

  // Invoke clang frontend to generate a binary.
  m_inv.compile(tmp_src);

  // Clear members, for next compilation.
  m_terminate = {};
  m_id_defer_count = 0;
}
} // namespace codegen::cpp_backend
