#include "clir_builder.hpp"

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"

// Macros:
#define STUB(t_type)                                              \
  auto ClirBuilder::visit([[maybe_unused]] t_type* t_ptr) -> Any  \
  {                                                               \
    DBG_CRITICAL("Method for type ", #t_type, " not overriden!"); \
                                                                  \
    return {};                                                    \
  }

namespace clir::clir_builder {
// Using statements:
NODE_USING_ALL_NAMESPACES()

// Methods:
ClirBuilder::ClirBuilder(): m_module{nullptr}
{}

auto ClirBuilder::visit(If* t_if) -> Any
{}

auto ClirBuilder::visit(Loop* t_loop) -> Any
{}

auto ClirBuilder::visit(Continue* t_continue) -> Any
{}

auto ClirBuilder::visit(Break* t_break) -> Any
{}

auto ClirBuilder::visit(Defer* t_defer) -> Any
{}

auto ClirBuilder::visit(Return* t_ret) -> Any
{}

// Functions:
auto ClirBuilder::visit(Parameter* t_param) -> Any
{}

auto ClirBuilder::visit(ast::node::function::Function* t_fn) -> Any
{
  Function fn{};

  const auto name{t_fn->identifier()};

  fn.m_name = name;

  // TODO: Clean this mess up?
  m_module->m_functions.push_back(std::move(fn));

  return {};
}

auto ClirBuilder::visit(Call* t_call) -> Any
{}

auto ClirBuilder::visit([[maybe_unused]] ReturnType* t_rt) -> Any
{}

// Lvalue:
auto ClirBuilder::visit(Let* t_let) -> Any
{}

auto ClirBuilder::visit(Var* t_var) -> Any
{}

auto ClirBuilder::visit(Variable* t_var) -> Any
{}

// Operators:
auto ClirBuilder::visit(Arithmetic* t_arith) -> Any
{}

auto ClirBuilder::visit(Assignment* t_assign) -> Any
{}

auto ClirBuilder::visit(Comparison* t_comp) -> Any
{}

auto ClirBuilder::visit(Increment* t_inc) -> Any
{}

auto ClirBuilder::visit(Decrement* t_dec) -> Any
{}

auto ClirBuilder::visit(UnaryPrefix* t_up) -> Any
{}

// Logical:
auto ClirBuilder::visit(Not* t_not) -> Any
{}

auto ClirBuilder::visit(And* t_and) -> Any
{}

auto ClirBuilder::visit(Or* t_or) -> Any
{}

auto ClirBuilder::visit([[maybe_unused]] Ternary* t_ternary) -> Any
{}

// Packaging:
STUB(Import)

auto ClirBuilder::visit(ModuleDecl* t_module) -> Any
{
  // For now we just assume there is only one.
  const auto module_name{t_module->identifier()};

  // TODO: Check if the module name is already set and then error?
  m_module->m_name = module_name;

  return {};
}

// RValue:
auto ClirBuilder::visit([[maybe_unused]] Float* t_float) -> Any
{}

auto ClirBuilder::visit(Integer* t_int) -> Any
{}

auto ClirBuilder::visit([[maybe_unused]] String* t_str) -> Any
{}

auto ClirBuilder::visit([[maybe_unused]] Boolean* t_bool) -> Any
{}

// Typing:
STUB(MethodDecl)
STUB(Interface)
STUB(MemberDecl)
STUB(Struct)
STUB(Impl)
STUB(DotExpr)

// Misc:
auto ClirBuilder::visit(List* t_list) -> Any
{
  // TODO: Implement.

  // Traverse all nodes.
  for(NodePtr& node : *t_list) {
    traverse(node);
  }

  // TODO: Return nothing?
  return {};
}

// Implementation:
auto ClirBuilder::translate(NodePtr t_ast) -> ModulePtr
{
  ModulePtr ptr{};

  // TODO: Create a ModuleFactory for the CLIR.
  m_module = std::make_shared<Module>();

  traverse(t_ast);

  ptr = m_module;
  m_module = nullptr;

  return ptr;
}
} // namespace clir::clir_builder
