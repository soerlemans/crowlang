#include "clir_builder.hpp"

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"
#include "lib/stdexcept/stdexcept.hpp"
#include "lib/string_util.hpp"

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

  // Get relevant members.
  const auto init_expr{t_if->init_expr()};
  const auto cond{t_if->condition()};
  const auto then{t_if->then()};
  const auto alt{t_if->then()};

  // Generate IR for init of another var.
  traverse(init_expr);

  // Resolve condition, should assign result of operation to a SSA var.
  traverse(cond);
  const auto last_var{m_factory->require_last_var()};

  auto& if_instr{m_factory->add_instruction(Opcode::IF)};
  if_instr.add_operand({last_var});

  // Then block:
  auto& then_block{m_factory->add_block("then_block")};
  if_instr.add_operand({&then_block});

  traverse(then);
  const auto then_jump{m_factory->create_instruction(Opcode::JUMP)};

  // Alt block:
  auto& alt_block{m_factory->add_block("alt_block")};
  if_instr.add_operand({&alt_block});

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

  // An expression is optional for a return statement.
  auto expr{t_ret->expr()};
  if(expr) {
    traverse(expr);
    const auto last_var{m_factory->require_last_var()};

    auto& ret{m_factory->add_instruction(Opcode::RETURN)};
    ret.add_operand({last_var});
  } else {
    // Add the return with no operand.
    m_factory->add_instruction(Opcode::RETURN);
  }

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

  const auto id{t_fn->identifier()};
  const auto params{t_fn->params()};

  // const auto return_type{t_fn->m_return_type()};
  const auto body{t_fn->identifier()};

  fn.m_name = id;

  // Add the function to the current module.
  m_factory->add_function(std::move(fn));
  m_factory->add_block("main");

  m_factory->push_env();

  // TODO: Maybe make a helper method for this?
  for(const auto& node : *params) {
    // Gain a raw ptr (non owning).
    // If the AST changes the assertion will be triggered.
    auto* param{dynamic_cast<Parameter*>(node.get())};
    if(!param) {
      using lib::stdexcept::unexpected_nullptr;

      unexpected_nullptr("Failed to dynamic_cast to Parameter*.");
    }

    // Init the parameter variables.
    const auto name{param->identifier()};
    const auto type{param->get_type()};

    auto source_line{param->position().m_line};
    lib::strip_whitespace(source_line);
    lib::trim_whitespace(source_line);
    source_line += '.';

    auto& init_instr{m_factory->add_init(name, type)};
    init_instr.m_comment = source_line;
  }

  // Traverse the body.
  traverse(t_fn->body());
  m_factory->pop_env();

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
  // The let and var keywords function the same in SSA.
  const auto name{t_let->identifier()};
  const auto type{t_let->get_type()};

  const auto init_expr{t_let->init_expr()};

  auto source_line{t_let->position().m_line};
  lib::strip_whitespace(source_line);
  lib::trim_whitespace(source_line);
  source_line += '.';

  traverse(init_expr);
  // TODO: Get last var?

  auto& init_instr{m_factory->add_init(name, type)};
  init_instr.m_comment = source_line;

  return {};
}

auto ClirBuilder::visit(Var* t_var) -> Any
{
  // The let and var keywords function the same in SSA.
  const auto name{t_var->identifier()};
  const auto type{t_var->get_type()};

  const auto init_expr{t_var->init_expr()};

  auto source_line{t_var->position().m_line};
  lib::strip_whitespace(source_line);
  lib::trim_whitespace(source_line);
  source_line += '.';

  traverse(init_expr);
  // TODO: Get last var?

  auto& init_instr{m_factory->add_init(name, type)};
  init_instr.m_comment = source_line;

  return {};
}

auto ClirBuilder::visit(Variable* t_var) -> Any
{
  const auto name{t_var->identifier()};

  // TODO: add casting of a variable if it differs from.
  // The source type.

  m_factory->add_update(name);

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
  // Dummy harcoded value for now.
  m_factory->add_instruction(Opcode::ICMP_LT);

  return {};
}

auto ClirBuilder::visit(Increment* t_inc) -> Any
{
  const auto left{t_inc->left()};
  traverse(left);
  const auto last_var{m_factory->require_last_var()};

  // TODO: Deduce type, of left.
  auto& dec_instr{m_factory->add_instruction(Opcode::IADD)};
  dec_instr.add_operand({last_var});

  // TODO: Deduce native type.
  Literal lit{NativeType::INT, 1};
  dec_instr.add_operand({lit});

  return {};
}

auto ClirBuilder::visit(Decrement* t_dec) -> Any
{
  const auto left{t_dec->left()};
  traverse(left);
  const auto last_var{m_factory->require_last_var()};

  // TODO: Deduce type, of left.
  auto& dec_instr{m_factory->add_instruction(Opcode::ISUB)};
  dec_instr.add_operand({last_var});

  // TODO: Deduce type, of left.
  Literal lit{NativeType::INT, 1};
  dec_instr.add_operand({lit});

  return {};
}

auto ClirBuilder::visit(UnaryPrefix* t_up) -> Any
{
  using ast::node::operators::UnaryPrefixOp;

  const auto op{t_up->op()};
  const auto left{t_up->left()};

  switch(op) {
    case UnaryPrefixOp::PLUS:
      // TODO: No op.
      break;

    case UnaryPrefixOp::MINUS:
      m_factory->add_instruction(Opcode::ISUB);

      // TODO: Traverse left.
      break;

    default:
      // TODO: THROW!
      break;
  }

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

auto ClirBuilder::visit(String* t_str) -> Any
{
  const std::string value{t_str->get()};

  // Add the literal, which assigns an SSA var for it.
  m_factory->add_literal(NativeType::STRING, {value});

  return {};
}

auto ClirBuilder::visit(Boolean* t_bool) -> Any
{
  const bool value{t_bool->get()};

  // Add the literal, which assigns an SSA var for it.
  m_factory->add_literal(NativeType::BOOL, {value});

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
  // Traverse all nodes.
  for(NodePtr& node : *t_list) {
    traverse(node);
  }

  return {};
}

// Implementation:
auto ClirBuilder::get_call_args(ast::node::NodeListPtr t_list) -> SsaVarVec
{
  SsaVarVec vec{};

  for(const auto& ptr : *t_list) {
    // Traverse to generate a last var that we can get.
    traverse(ptr);

    // Get the refs.
    const auto& last_var{m_factory->require_last_var()};
    vec.push_back(last_var);
  }

  return vec;
}

auto ClirBuilder::translate(NodePtr t_ast) -> ModulePtr
{
  ModulePtr ptr{nullptr};

  // Initialize the module factory.
  m_factory = std::make_unique<ClirModuleFactory>();

  // Traverse the AST using the module factory to create the CLIR module.
  traverse(t_ast);

  // Obtain the CLIR module created by the module factory.
  ptr = m_factory->get_module();

  // Clear the environment, as we are done with it.
  m_factory->clear_env();

  // Free the factory.
  m_factory.reset();

  return ptr;
}
} // namespace clir::clir_builder
