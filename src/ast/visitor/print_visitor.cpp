#include "print_visitor.hpp"

// STL Includes:
#include <iomanip>
#include <ios>
#include <sstream>


// Macros:
#define COUNTG_INIT() \
  CountGuard guard    \
  {                   \
    m_counter         \
  }

#define PPRINT_UNOP(t_str, t_ptr)    \
  do {                               \
    print(t_str);                    \
    print_if("Left", t_ptr->left()); \
  } while(false)

#define PPRINT_BINOP(t_str, t_ptr)     \
  do {                                 \
    print(t_str);                      \
    print_if("Left", t_ptr->left());   \
    print_if("Right", t_ptr->right()); \
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

// Friend classes:
namespace {
class CountGuard {
  private:
  int& m_counter;

  public:
  CountGuard(int& t_counter): m_counter{t_counter}
  {
    m_counter++;
  }

  ~CountGuard()
  {
    m_counter--;
  }
};
} // namespace

// Methods:
auto PrintVisitor::print_if(std::string_view t_str, NodePtr t_ptr) -> void
{
  if(t_ptr) {
    print(t_str);
    t_ptr->accept(this);
  }
}

// Control:
auto PrintVisitor::visit(If* t_if) -> void
{
  COUNTG_INIT();

  print("If");
  print_if("Init", t_if->init_expr());
  print_if("Then", t_if->then());
  print_if("Alt", t_if->alt());
}

auto PrintVisitor::visit(node::control::Loop* t_loop) -> void
{
  COUNTG_INIT();

  print("Loop");
  print_if("Init", t_loop->init_expr());
  print_traits(t_loop);
}

auto PrintVisitor::visit([[maybe_unused]] Continue* t_continue) -> void
{
  COUNTG_INIT();

  print("Continue");
}

auto PrintVisitor::visit([[maybe_unused]] Break* t_break) -> void
{
  COUNTG_INIT();

  print("Break");
}

auto PrintVisitor::visit(Return* t_return) -> void
{
  COUNTG_INIT();

  print("Return");
  print_traits(t_return);
}

// Function:
auto PrintVisitor::visit(Function* t_fn) -> void
{
  COUNTG_INIT();

  print("Function");
  print_traits(t_fn);
}

auto PrintVisitor::visit(FunctionCall* t_fn_call) -> void
{
  COUNTG_INIT();

  print("Function call");
  print("| Identifier: ", t_fn_call->identifier());
  print_if("Arguments: ", t_fn_call->args());
}

auto PrintVisitor::visit(node::functions::ReturnType* t_rt) -> void
{
  COUNTG_INIT();

  print("Return type");
  print("| Type: ", t_rt->type());
}

// Lvalue:
auto PrintVisitor::visit(Let* t_let) -> void
{
  COUNTG_INIT();

  print_traits(t_let);
}

auto PrintVisitor::visit(Variable* t_var) -> void
{
  COUNTG_INIT();

  print("Variable: ", t_var->identifier());
}

// Operators:
auto PrintVisitor::visit(Arithmetic* t_arithmetic) -> void
{
  COUNTG_INIT();

  PPRINT_BINOP("ARITHMETIC", t_arithmetic);
  print("| OP: TODO!");
}

auto PrintVisitor::visit(Assignment* t_assignment) -> void
{
  COUNTG_INIT();

  PPRINT_BINOP("Assignment", t_assignment);
}

auto PrintVisitor::visit(Comparison* t_comparison) -> void
{
  COUNTG_INIT();

  PPRINT_BINOP("Comparison", t_comparison);
}

auto PrintVisitor::visit(Increment* t_increment) -> void
{
  COUNTG_INIT();

  print("Increment");
  print("| Prefix: ", t_increment->prefix());
}

auto PrintVisitor::visit(Decrement* t_decrement) -> void
{
  COUNTG_INIT();

  print("Decrement");
  print("| Prefix: ", t_decrement->prefix());
}

auto PrintVisitor::visit(UnaryPrefix* t_unary_prefix) -> void
{
  COUNTG_INIT();

  print("Unary prefix");
  PPRINT_UNOP("Unary prefix", t_unary_prefix);
  print("| OP: TODO!");
}

// Logical:
auto PrintVisitor::visit(Not* t_not) -> void
{
  COUNTG_INIT();

  PPRINT_UNOP("Not", t_not);
}

auto PrintVisitor::visit(And* t_and) -> void
{
  COUNTG_INIT();

  PPRINT_BINOP("And", t_and);
}

auto PrintVisitor::visit(Or* t_or) -> void
{
  COUNTG_INIT();

  PPRINT_BINOP("Or", t_or);
}

auto PrintVisitor::visit(Ternary* t_ternary) -> void
{
  COUNTG_INIT();

  print("Ternary");
  // PPRINT_COND(t_ternary);
  print_if("Then", t_ternary->then());
  print_if("Alt", t_ternary->alt());
}

// Packaging:
auto PrintVisitor::visit(Import* t_import) -> void
{
  COUNTG_INIT();

  print("Import");

  for(const auto& pair : t_import->imports()) {
    std::stringstream ss;
    if(pair.second) {
      ss << " Identifier: " << pair.second.value();
    }

    print("| Pkg: ", std::quoted(pair.first), ss.str());
  }
}

auto PrintVisitor::visit(ModuleDecl* t_mod) -> void
{
  COUNTG_INIT();

  print("Module Declaration");
  print_traits(t_mod);
}

// Rvalue:
auto PrintVisitor::visit(Float* t_float) -> void
{
  COUNTG_INIT();

  print("Float: ", t_float->get());
}

auto PrintVisitor::visit(Integer* t_int) -> void
{
  COUNTG_INIT();

  print("Integer: ", t_int->get());
}

auto PrintVisitor::visit(String* t_str) -> void
{
  COUNTG_INIT();

  print("String: ", t_str->get());
}

auto PrintVisitor::visit(Boolean* t_bool) -> void
{
  COUNTG_INIT();

  print("Boolean: ", t_bool->get());
}

// Typing:
auto PrintVisitor::visit(MethodDecl* t_md) -> void
{
  COUNTG_INIT();

  print("Method Declaration");
  print_traits(t_md);
}

auto PrintVisitor::visit(Interface* t_ifc) -> void
{
  COUNTG_INIT();

  print("Interface");
  print_traits(t_ifc);
  print_if("Methods: ", t_ifc->methods());
}

auto PrintVisitor::visit(MemberDecl* t_md) -> void
{
  COUNTG_INIT();

  print("Member Declaration");
  print_traits(t_md);
}

auto PrintVisitor::visit(Struct* t_struct) -> void
{
  COUNTG_INIT();

  print("Struct");
  print_traits(t_struct);
  print_traits(t_struct);
}

auto PrintVisitor::visit(DefBlock* t_db) -> void
{
  COUNTG_INIT();

  print("DefBlock");
  print_traits(t_db);
  print_traits(t_db);
}

auto PrintVisitor::visit(DotExpr* t_dot_expr) -> void
{
  COUNTG_INIT();

  print("DotExpr");
  print_traits(t_dot_expr);
  print_traits(t_dot_expr);
}

auto PrintVisitor::visit(List* t_list) -> void
{
  COUNTG_INIT();

  print("List");
  for(NodePtr& node : *t_list) {
    node->accept(this);
  }
}

auto PrintVisitor::visit([[maybe_unused]] Nil* t_nil) -> void
{
  COUNTG_INIT();

  print("Nil");
}
