#include "print_visitor.hpp"


// Macros:
#define PPRINT_INIT() \
  Printer printer     \
  {                   \
    m_counter         \
  }

#define PPRINT(...) printer.print(__VA_ARGS__)

//! Pretty print if a member is not a nullptr
#define PPRINT_IF(t_str, t_ptr) printer.print_if(t_ptr, this, "| " t_str)

#define PPRINT_UNOP(t_str, t_ptr) \
  PPRINT(t_str);                  \
  PPRINT_IF("Left", t_ptr->left());

#define PPRINT_BINOP(t_str, t_ptr)  \
  PPRINT(t_str);                    \
  PPRINT_IF("Left", t_ptr->left()); \
  PPRINT_IF("Right", t_ptr->right());

// Using statements:
using namespace ast::visitor;
using namespace ast::node;
using namespace ast::node::control;
using namespace ast::node::functions;
using namespace ast::node::lvalue;
using namespace ast::node::operators;
using namespace ast::node::rvalue;

auto PrintVisitor::visit(If* t_if) -> void
{
  PPRINT_INIT();

  PPRINT("If");
  PPRINT_IF("Then", t_if->then());
  PPRINT_IF("Alt", t_if->alt());
}

auto PrintVisitor::visit([[maybe_unused]] Continue* t_continue) -> void
{
  PPRINT_INIT();

  PPRINT("Continue");
}

auto PrintVisitor::visit([[maybe_unused]] Break* t_break) -> void
{
  PPRINT_INIT();

  PPRINT("Break");
}

auto PrintVisitor::visit([[maybe_unused]] Return* t_return) -> void
{
  PPRINT_INIT();

  PPRINT("Return");
}

auto PrintVisitor::visit(Function* t_fn) -> void
{
  PPRINT_INIT();

  PPRINT("FUNCTION");
  PPRINT("| Name", t_fn->identifier());
  PPRINT_IF("Params", t_fn->params());
  PPRINT_IF("Body", t_fn->body());
}

auto PrintVisitor::visit(FunctionCall* t_fn_call) -> void
{
  PPRINT_INIT();

  PPRINT("Function call");
  PPRINT("| Name: ", t_fn_call->identifier());
  PPRINT_IF("Arguments: ", t_fn_call->args());
}

auto PrintVisitor::visit(Variable* t_var) -> void
{
  PPRINT_INIT();

  PPRINT("Variable: ", t_var->identifier());
}

auto PrintVisitor::visit(Float* t_float) -> void
{
  PPRINT_INIT();

  PPRINT("Float: ", t_float->get());
}

auto PrintVisitor::visit(Integer* t_int) -> void
{
  PPRINT_INIT();

  PPRINT("Integer: ", t_int->get());
}

auto PrintVisitor::visit(String* t_str) -> void
{
  PPRINT_INIT();

  PPRINT("String: ", t_str->get());
}

auto PrintVisitor::visit(Arithmetic* t_arithmetic) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("ARITHMETIC", t_arithmetic)
  PPRINT("| OP: TODO!");
}

auto PrintVisitor::visit(Assignment* t_assignment) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("Assignment", t_assignment);
}

auto PrintVisitor::visit(Comparison* t_comparison) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("Comparison", t_comparison);
}

auto PrintVisitor::visit(Increment* t_increment) -> void
{
  PPRINT_INIT();

  PPRINT("Increment");
  PPRINT("| Prefix: ", t_increment->prefix());
}

auto PrintVisitor::visit(Decrement* t_decrement) -> void
{
  PPRINT_INIT();

  PPRINT("Decrement");
  PPRINT("| Prefix: ", t_decrement->prefix());
}

auto PrintVisitor::visit(Not* t_not) -> void
{
  PPRINT_INIT();

  PPRINT_UNOP("Not", t_not);
}

auto PrintVisitor::visit(And* t_and) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("And", t_and);
}

auto PrintVisitor::visit(Or* t_or) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("Or", t_or);
}

auto PrintVisitor::visit(Grouping* t_grouping) -> void
{
  PPRINT_INIT();

  PPRINT_UNOP("Grouping", t_grouping)
}

auto PrintVisitor::visit(Ternary* t_ternary) -> void
{
  PPRINT_INIT();

  PPRINT("Ternary");
  PPRINT_IF("Condition", t_ternary->condition());
  PPRINT_IF("Then", t_ternary->then());
  PPRINT_IF("Alt", t_ternary->alt());
}

auto PrintVisitor::visit(UnaryPrefix* t_unary_prefix) -> void
{
  PPRINT_INIT();

  PPRINT("Unary prefix");
  PPRINT_UNOP("Unary prefix", t_unary_prefix)
  PPRINT("| OP: TODO");
}

auto PrintVisitor::visit(List* t_list) -> void
{
  PPRINT_INIT();

  PPRINT("List");
  for(NodePtr& node : *t_list) {
    node->accept(this);
  }
}

auto PrintVisitor::visit([[maybe_unused]] Nil* t_nil) -> void
{
  PPRINT_INIT();

  PPRINT("NIL");
}
