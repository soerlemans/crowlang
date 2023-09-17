#include "print_visitor.hpp"

// STL Includes:
#include <iomanip>
#include <ios>
#include <sstream>


// Macros:
#define PPRINT_INIT() \
  Printer printer     \
  {                   \
    m_counter         \
  }

#define PPRINT(...) printer.print(__VA_ARGS__)

//! Pretty print if a member is not a nullptr
#define PPRINT_IF(t_str, t_ptr) printer.print_if(t_ptr, this, "| " t_str)

#define PPRINT_UNOP(t_str, t_ptr)     \
  do {                                \
    PPRINT(t_str);                    \
    PPRINT_IF("Left", t_ptr->left()); \
  } while(false)

#define PPRINT_BINOP(t_str, t_ptr)      \
  do {                                  \
    PPRINT(t_str);                      \
    PPRINT_IF("Left", t_ptr->left());   \
    PPRINT_IF("Right", t_ptr->right()); \
  } while(false)

#define PPRINT_ID(t_ptr) PPRINT("| Identifier: ", t_ptr->identifier())
// #define PPRINT_INIT(t_ptr) PPRINT_IF("Init", t_ptr->init())
#define PPRINT_COND(t_ptr)      PPRINT_IF("Condition", t_ptr->condition())
#define PPRINT_EXPR(t_ptr)      PPRINT_IF("Expr", t_ptr->expr())
#define PPRINT_BODY(t_ptr)      PPRINT_IF("Body", t_ptr->body())
#define PPRINT_PARAMS(t_ptr)    PPRINT_IF("Params", t_ptr->body())
#define PPRINT_TYPE_EXPR(t_ptr) PPRINT_IF("Type Expr", t_ptr->type())

// Using statements:
using namespace ast::visitor;
using namespace ast::node;
using namespace ast::node::control;
using namespace ast::node::functions;
using namespace ast::node::lvalue;
using namespace ast::node::operators;
using namespace ast::node::packaging;
using namespace ast::node::rvalue;
using namespace ast::node::typing;

// Control:
auto PrintVisitor::visit(If* t_if) -> void
{
  PPRINT_INIT();

  PPRINT("If");
  PPRINT_IF("Init", t_if->init());
  PPRINT_COND(t_if);
  PPRINT_IF("Then", t_if->then());
  PPRINT_IF("Alt", t_if->alt());
}

auto PrintVisitor::visit(node::control::Loop* t_loop) -> void
{
  PPRINT_INIT();

  PPRINT("Loop");
  PPRINT_IF("Init", t_loop->init());
  PPRINT_COND(t_loop);
  PPRINT_EXPR(t_loop);
  PPRINT_BODY(t_loop);
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
  PPRINT_EXPR(t_return);
}

// Function:
auto PrintVisitor::visit(Function* t_fn) -> void
{
  PPRINT_INIT();

  PPRINT("Function");
  PPRINT_ID(t_fn);
  PPRINT_PARAMS(t_fn);
  PPRINT_BODY(t_fn);
}

auto PrintVisitor::visit(FunctionCall* t_fn_call) -> void
{
  PPRINT_INIT();

  PPRINT("Function call");
  PPRINT("| Identifier: ", t_fn_call->identifier());
  PPRINT_IF("Arguments: ", t_fn_call->args());
}

auto PrintVisitor::visit(node::functions::ReturnType* t_rt) -> void
{
  PPRINT_INIT();

  PPRINT("Return type");
  PPRINT_IF("Type: ", t_rt->type());
  PPRINT_TYPE_EXPR(t_rt);
}

// Lvalue:
auto PrintVisitor::visit(Let* t_let) -> void
{
  PPRINT_INIT();

  std::stringstream ss;

  PPRINT("Let: ", t_let->identifier());
  PPRINT_IF("Init: ", t_let->init());
}

auto PrintVisitor::visit(Variable* t_var) -> void
{
  PPRINT_INIT();

  PPRINT("Variable: ", t_var->identifier());
}

// Operators:
auto PrintVisitor::visit(Arithmetic* t_arithmetic) -> void
{
  PPRINT_INIT();

  PPRINT_BINOP("ARITHMETIC", t_arithmetic);
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

auto PrintVisitor::visit(UnaryPrefix* t_unary_prefix) -> void
{
  PPRINT_INIT();

  PPRINT("Unary prefix");
  PPRINT_UNOP("Unary prefix", t_unary_prefix);
  PPRINT("| OP: TODO!");
}

// Logical:
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

auto PrintVisitor::visit(Ternary* t_ternary) -> void
{
  PPRINT_INIT();

  PPRINT("Ternary");
  PPRINT_COND(t_ternary);
  PPRINT_IF("Then", t_ternary->then());
  PPRINT_IF("Alt", t_ternary->alt());
}

// Packaging:
auto PrintVisitor::visit(Import* t_import) -> void
{
  PPRINT_INIT();

  PPRINT("Import");

  for(const auto& pair : t_import->imports()) {
    std::stringstream ss;
    if(pair.second) {
      ss << " Identifier: " << pair.second.value();
    }

    PPRINT("| Pkg: ", std::quoted(pair.first), ss.str());
  }
}

auto PrintVisitor::visit(ModuleDecl* t_mod) -> void
{
  PPRINT_INIT();

  PPRINT("Module Declaration");
  PPRINT_ID(t_mod);
}

// Rvalue:
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

auto PrintVisitor::visit(Boolean* t_bool) -> void
{
  PPRINT_INIT();

  PPRINT("Boolean: ", t_bool->get());
}

// Typing:
auto PrintVisitor::visit(DotExpr* t_dot_expr) -> void
{
  PPRINT_INIT();

  PPRINT("DotExpr");
  PPRINT_ID(t_dot_expr);
  PPRINT_EXPR(t_dot_expr);
}

auto PrintVisitor::visit(Impl* t_impl) -> void
{
  PPRINT_INIT();

  PPRINT("Impl");
  PPRINT_ID(t_impl);
  PPRINT_BODY(t_impl);
}

auto PrintVisitor::visit(Interface* t_ifc) -> void
{
  PPRINT_INIT();

  PPRINT("Interface");
  PPRINT_ID(t_ifc);
  PPRINT_IF("Methods: ", t_ifc->methods());
}

auto PrintVisitor::visit(MethodDecl* t_md) -> void
{
  PPRINT_INIT();

  PPRINT("Method Declaration");
  PPRINT_ID(t_md);
  PPRINT_TYPE_EXPR(t_md);
}

auto PrintVisitor::visit(Struct* t_struct) -> void
{
  PPRINT_INIT();

  PPRINT("Struct");
  PPRINT_ID(t_struct);
  PPRINT_BODY(t_struct);
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
