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
  // We need to create two new blocks an if and else branch.
  auto& main_block{m_factory->last_block()};

  // These will be processed after each block is created.
  // TODO: InitExpr.
  // TODO: Add condition for if to main_block
  const auto cond{t_if->condition()};
  const auto then{t_if->then()};
  const auto alt{t_if->then()};

  // Resolve condition.
  traverse(cond);

  // Then block:
  auto& then_block{m_factory->add_block("then_block")};
  traverse(then);
  const auto then_jump{m_factory->create_instruction(Opcode::JUMP)};

  // Alt block:
  auto& alt_block{m_factory->add_block("alt_block")};
  traverse(alt);
  const auto alt_jump{m_factory->create_instruction(Opcode::JUMP)};

  // Final block after the if statement.
  auto& final_block{m_factory->add_block("final_block")};

  // Insert jumps at the end of the blocks.
  m_factory->insert_jump(then_jump, then_block, final_block);
  m_factory->insert_jump(alt_jump, alt_block, final_block);

  return {};
}

auto ClirBuilder::visit(Loop* t_loop) -> Any
{
  return {};
}

auto ClirBuilder::visit(Continue* t_continue) -> Any
{
  m_factory->add_instruction(Opcode::CONTINUE);

  return {};
}

auto ClirBuilder::visit(Break* t_break) -> Any
{
  m_factory->add_instruction(Opcode::BREAK);

  return {};
}

auto ClirBuilder::visit(Defer* t_defer) -> Any
{
  // Defer statements are inserted at the end.
  // Of a return statement or any other break in return.

  return {};
}

auto ClirBuilder::visit(Return* t_ret) -> Any
{
  auto& block{m_factory->last_block()};

  auto expr{t_ret->expr()};
  traverse(expr);

  m_factory->add_instruction(Opcode::RETURN);
	// TODO: Add last result.


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
  const auto body{t_fn->identifier()};

  fn.m_name = name;

  // Add the function to the current module.
  m_factory->add_function(std::move(fn));
  m_factory->add_block("main");

  // Traverse the body.
  traverse(t_fn->body());

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
  auto& block{m_factory->last_block()};

  // Dummy harcoded value for now.
  m_factory->add_instruction(Opcode::ICMP_LT);

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
{
  return {};
}

auto ClirBuilder::visit(Integer* t_int) -> Any
{
  return {};
}

auto ClirBuilder::visit([[maybe_unused]] String* t_str) -> Any
{
  return {};
}

auto ClirBuilder::visit([[maybe_unused]] Boolean* t_bool) -> Any
{
  return {};
}

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
