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
ClirBuilder::ClirBuilder(): m_factory{nullptr}
{}

auto ClirBuilder::visit(If* t_if) -> Any
{
  return {};
}

auto ClirBuilder::visit(Loop* t_loop) -> Any
{
  return {};
}

auto ClirBuilder::visit(Continue* t_continue) -> Any
{
  return {};
}

auto ClirBuilder::visit(Break* t_break) -> Any
{
  return {};
}

auto ClirBuilder::visit(Defer* t_defer) -> Any
{
  return {};
}

auto ClirBuilder::visit(Return* t_ret) -> Any
{
  return {};
}

// Functions:
auto ClirBuilder::visit(Parameter* t_param) -> Any
{
  return {};
}

auto ClirBuilder::visit(ast::node::function::Function* t_fn) -> Any
{
  Function fn{};

  const auto name{t_fn->identifier()};

  fn.m_name = name;

  m_factory->create_function(std::move(fn));

  // TODO: Walk through body and add to current function.

  return {};
}

auto ClirBuilder::visit(Call* t_call) -> Any
{
  return {};
}

auto ClirBuilder::visit([[maybe_unused]] ReturnType* t_rt) -> Any
{
  return {};
}

// Lvalue:
auto ClirBuilder::visit(Let* t_let) -> Any
{
  return {};
}

auto ClirBuilder::visit(Var* t_var) -> Any
{
  return {};
}

auto ClirBuilder::visit(Variable* t_var) -> Any
{
  return {};
}

// Operators:
auto ClirBuilder::visit(Arithmetic* t_arith) -> Any
{
  return {};
}

auto ClirBuilder::visit(Assignment* t_assign) -> Any
{
  return {};
}

auto ClirBuilder::visit(Comparison* t_comp) -> Any
{
  return {};
}

auto ClirBuilder::visit(Increment* t_inc) -> Any
{
  return {};
}

auto ClirBuilder::visit(Decrement* t_dec) -> Any
{
  return {};
}

auto ClirBuilder::visit(UnaryPrefix* t_up) -> Any
{
  return {};
}

// Logical:
auto ClirBuilder::visit(Not* t_not) -> Any
{
  return {};
}

auto ClirBuilder::visit(And* t_and) -> Any
{
  return {};
}

auto ClirBuilder::visit(Or* t_or) -> Any
{
  return {};
}

auto ClirBuilder::visit([[maybe_unused]] Ternary* t_ternary) -> Any
{
  return {};
}

// Packaging:
STUB(Import)

auto ClirBuilder::visit(ModuleDecl* t_module) -> Any
{
  // For now we just assume there is only one.
  const auto module_name{t_module->identifier()};

  // TODO: Add check to see if the module name has already been set.
  m_factory->set_module_name(module_name);

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
  ModulePtr ptr{nullptr};

  // Initialize the module factory.
  m_factory = std::make_unique<ModuleFactory>();

  // Traverse the AST using the module factory to create the CLIR module.
  traverse(t_ast);

  // Obtain the CLIR module created by the module factory.
  ptr = m_factory->get_module();

  // Free the factory.
  m_factory.reset();

  return ptr;
}
} // namespace clir::clir_builder
