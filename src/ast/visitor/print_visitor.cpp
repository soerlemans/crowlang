#include "print_visitor.hpp"

// STL Includes:
#include <iomanip>
#include <ios>
#include <sstream>


// Macros:
#define COUNT_INIT()  \
  do {                \
    CountGuard guard; \
  } while(false)

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


#define PPRINT_ID(t_ptr)        PPRINT("| Identifier: ", t_ptr->identifier())
#define PPRINT_INIT_EXPR(t_ptr) PPRINT_IF("Init Expr", t_ptr->init_expr())
#define PPRINT_COND(t_ptr)      PPRINT_IF("Condition", t_ptr->condition())
#define PPRINT_EXPR(t_ptr)      PPRINT_IF("Expr", t_ptr->expr())
#define PPRINT_BODY(t_ptr)      PPRINT_IF("Body", t_ptr->body())
#define PPRINT_PARAMS(t_ptr)    PPRINT_IF("Params", t_ptr->body())
#define PPRINT_TYPE(t_ptr)      PPRINT("| Type: ", t_ptr->type())

//! Helper macro for resovling trait printing at compile time
#define PPRINT_IF_DERIVED(t_ptr, t_type, t_macro)              \
  do {                                                         \
    if constexpr(std::derived_from<decltype(t_ptr), t_type>) { \
      t_macro(t_ptr);                                          \
    }                                                          \
    while(false)

#define PPRINT_TRAITS(t_ptr)                              \
  do {                                                    \
    PPRINT_IF_DERIVED(t_ptr, Identifier, PPRINT_ID);      \
    PPRINT_IF_DERIVED(t_ptr, InitExpr, PPRINT_INIT_EXPR); \
    PPRINT_IF_DERIVED(t_ptr, Condition, PPRINT_COND);     \
    PPRINT_IF_DERIVED(t_ptr, Expr, PPRINT_EXPR);          \
    PPRINT_IF_DERIVED(t_ptr, Body, PPRINT_BODY);          \
    PPRINT_IF_DERIVED(t_ptr, Params, PPRINT_PARAMS);      \
    PPRINT_IF_DERIVED(t_ptr, Type, PPRINT_TYPE);          \
  } while(false)


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
using namespace ast::node::node_traits;

// Methods:
auto PrintVisitor::print_if(std::string_view t_str_vw, NodePtr t_ptr) -> void
{
  if(t_ptr) {
    print(t_str_vw);
    t_ptr->accept(this);
  }
}

// Control:
auto PrintVisitor::visit(If* t_if) -> void
{
  COUNT_INIT();

  PPRINT("If");
  print_if("Init", t_if->init_expr());
  PPRINT_COND(t_if);
  print_if("Then", t_if->then());
  print_if("Alt", t_if->alt());
}

auto PrintVisitor::visit(node::control::Loop* t_loop) -> void
{
  COUNT_INIT();

  PPRINT("Loop");
  print_if("Init", t_loop->init_expr());
  PPRINT_COND(t_loop);
  PPRINT_EXPR(t_loop);
  PPRINT_BODY(t_loop);
}

auto PrintVisitor::visit([[maybe_unused]] Continue* t_continue) -> void
{
  COUNT_INIT();

  PPRINT("Continue");
}

auto PrintVisitor::visit([[maybe_unused]] Break* t_break) -> void
{
  COUNT_INIT();

  PPRINT("Break");
}

auto PrintVisitor::visit(Return* t_return) -> void
{
  COUNT_INIT();

  PPRINT("Return");
  PPRINT_EXPR(t_return);
}

// Function:
auto PrintVisitor::visit(Function* t_fn) -> void
{
  COUNT_INIT();

  PPRINT("Function");
  // pprint_traits(printer, t_fn);
}

auto PrintVisitor::visit(FunctionCall* t_fn_call) -> void
{
  COUNT_INIT();

  PPRINT("Function call");
  PPRINT("| Identifier: ", t_fn_call->identifier());
  print_if("Arguments: ", t_fn_call->args());
}

auto PrintVisitor::visit(node::functions::ReturnType* t_rt) -> void
{
  COUNT_INIT();

  PPRINT("Return type");
  PPRINT("| Type: ", t_rt->type());
}

// Lvalue:
auto PrintVisitor::visit(Let* t_let) -> void
{
  COUNT_INIT();

  std::stringstream ss;

  PPRINT("Let: ", t_let->identifier());
  PPRINT_INIT_EXPR(t_let);
}

auto PrintVisitor::visit(Variable* t_var) -> void
{
  COUNT_INIT();

  PPRINT("Variable: ", t_var->identifier());
}

// Operators:
auto PrintVisitor::visit(Arithmetic* t_arithmetic) -> void
{
  COUNT_INIT();

  PPRINT_BINOP("ARITHMETIC", t_arithmetic);
  PPRINT("| OP: TODO!");
}

auto PrintVisitor::visit(Assignment* t_assignment) -> void
{
  COUNT_INIT();

  PPRINT_BINOP("Assignment", t_assignment);
}

auto PrintVisitor::visit(Comparison* t_comparison) -> void
{
  COUNT_INIT();

  PPRINT_BINOP("Comparison", t_comparison);
}

auto PrintVisitor::visit(Increment* t_increment) -> void
{
  COUNT_INIT();

  PPRINT("Increment");
  PPRINT("| Prefix: ", t_increment->prefix());
}

auto PrintVisitor::visit(Decrement* t_decrement) -> void
{
  COUNT_INIT();

  PPRINT("Decrement");
  PPRINT("| Prefix: ", t_decrement->prefix());
}

auto PrintVisitor::visit(UnaryPrefix* t_unary_prefix) -> void
{
  COUNT_INIT();

  PPRINT("Unary prefix");
  PPRINT_UNOP("Unary prefix", t_unary_prefix);
  PPRINT("| OP: TODO!");
}

// Logical:
auto PrintVisitor::visit(Not* t_not) -> void
{
  COUNT_INIT();

  PPRINT_UNOP("Not", t_not);
}

auto PrintVisitor::visit(And* t_and) -> void
{
  COUNT_INIT();

  PPRINT_BINOP("And", t_and);
}

auto PrintVisitor::visit(Or* t_or) -> void
{
  COUNT_INIT();

  PPRINT_BINOP("Or", t_or);
}

auto PrintVisitor::visit(Ternary* t_ternary) -> void
{
  COUNT_INIT();

  PPRINT("Ternary");
  PPRINT_COND(t_ternary);
  print_if("Then", t_ternary->then());
  print_if("Alt", t_ternary->alt());
}

// Packaging:
auto PrintVisitor::visit(Import* t_import) -> void
{
  COUNT_INIT();

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
  COUNT_INIT();

  PPRINT("Module Declaration");
  PPRINT_ID(t_mod);
}

// Rvalue:
auto PrintVisitor::visit(Float* t_float) -> void
{
  COUNT_INIT();

  PPRINT("Float: ", t_float->get());
}

auto PrintVisitor::visit(Integer* t_int) -> void
{
  COUNT_INIT();

  PPRINT("Integer: ", t_int->get());
}

auto PrintVisitor::visit(String* t_str) -> void
{
  COUNT_INIT();

  PPRINT("String: ", t_str->get());
}

auto PrintVisitor::visit(Boolean* t_bool) -> void
{
  COUNT_INIT();

  PPRINT("Boolean: ", t_bool->get());
}

// Typing:
auto PrintVisitor::visit(MethodDecl* t_md) -> void
{
  COUNT_INIT();

  PPRINT("Method Declaration");
  PPRINT_ID(t_md);
  PPRINT_TYPE(t_md);
}

auto PrintVisitor::visit(Interface* t_ifc) -> void
{
  COUNT_INIT();

  PPRINT("Interface");
  PPRINT_ID(t_ifc);
  print_if("Methods: ", t_ifc->methods());
}

auto PrintVisitor::visit(MemberDecl* t_md) -> void
{
  COUNT_INIT();

  PPRINT("Member Declaration");
  PPRINT_ID(t_md);
  PPRINT_TYPE(t_md);
}

auto PrintVisitor::visit(Struct* t_struct) -> void
{
  COUNT_INIT();

  PPRINT("Struct");
  PPRINT_ID(t_struct);
  PPRINT_BODY(t_struct);
}

auto PrintVisitor::visit(DefBlock* t_db) -> void
{
  COUNT_INIT();

  PPRINT("DefBlock");
  PPRINT_ID(t_db);
  PPRINT_BODY(t_db);
}

auto PrintVisitor::visit(DotExpr* t_dot_expr) -> void
{
  COUNT_INIT();

  PPRINT("DotExpr");
  PPRINT_ID(t_dot_expr);
  PPRINT_EXPR(t_dot_expr);
}

auto PrintVisitor::visit(List* t_list) -> void
{
  COUNT_INIT();

  PPRINT("List");
  for(NodePtr& node : *t_list) {
    node->accept(this);
  }
}

auto PrintVisitor::visit([[maybe_unused]] Nil* t_nil) -> void
{
  COUNT_INIT();

  PPRINT("Nil");
}
