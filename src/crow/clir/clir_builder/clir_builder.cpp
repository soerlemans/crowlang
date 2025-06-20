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
{}

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
STUB(ModuleDecl)

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
{}

// Implementation:
auto translate(NodePtr t_ast) -> Module
{
  // TODO: Implementate.

  return {};
}
} // namespace clir::clir_builder
