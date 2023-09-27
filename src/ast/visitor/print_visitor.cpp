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

//! Defines a PrintVisitor method, that will print all traits
#define DEF_PV_METHOD(t_type)                                   \
  auto PrintVisitor::visit([[maybe_unused]] t_type* t_ptr)->Any \
  {                                                             \
    COUNTG_INIT();                                              \
                                                                \
    print(#t_type);                                             \
    print_traits(t_ptr);                                        \
                                                                \
    return {};                                                  \
  }

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

PrintVisitor::PrintVisitor(std::ostream& t_os): m_os{t_os}
{}

// Control:
DEF_PV_METHOD(If)
DEF_PV_METHOD(Loop)
DEF_PV_METHOD(Continue)
DEF_PV_METHOD(Break)
DEF_PV_METHOD(Return)

// Function:
DEF_PV_METHOD(Function)

auto PrintVisitor::visit(FunctionCall* t_fn_call) -> Any
{
  COUNTG_INIT();

  print("Function call");
  print("| Identifier: ", t_fn_call->identifier());
  print_if("Arguments: ", t_fn_call->args());

  return {};
}

DEF_PV_METHOD(ReturnType)

// Lvalue:
DEF_PV_METHOD(Const)
DEF_PV_METHOD(Let)

auto PrintVisitor::visit(Variable* t_var) -> Any
{
  COUNTG_INIT();

  print("Variable: ", t_var->identifier());

  return {};
}

// Operators:
auto PrintVisitor::visit(Arithmetic* t_arithmetic) -> Any
{
  COUNTG_INIT();

  print("Arithmetic");
  print_traits(t_arithmetic);
  // print("| OP: TODO!");

  return {};
}

auto PrintVisitor::visit(Assignment* t_assignment) -> Any
{
  COUNTG_INIT();

  print("Assignment");
  print_traits(t_assignment);
  // print("| OP: TODO!");

  return {};
}

auto PrintVisitor::visit(Comparison* t_comparison) -> Any
{
  COUNTG_INIT();

  print("Comparison");
  print_traits(t_comparison);
  // print("| OP: TODO!");

  return {};
}

auto PrintVisitor::visit(Increment* t_inc) -> Any
{
  COUNTG_INIT();

  print("Increment");
  print("| Prefix: ", t_inc->prefix());
  print_traits(t_inc);

  return {};
}

auto PrintVisitor::visit(Decrement* t_dec) -> Any
{
  COUNTG_INIT();

  print("Decrement");
  print("| Prefix: ", t_dec->prefix());
  print_traits(t_dec);

  return {};
}

auto PrintVisitor::visit(UnaryPrefix* t_unary_prefix) -> Any
{
  COUNTG_INIT();

  print("UnaryPrefix");
  print_traits(t_unary_prefix);
  print("| OP: TODO!");

  return {};
}

// Logical:
DEF_PV_METHOD(Not)
DEF_PV_METHOD(And)
DEF_PV_METHOD(Or)

auto PrintVisitor::visit(Ternary* t_ternary) -> Any
{
  COUNTG_INIT();

  print("Ternary");
  print_traits(t_ternary);

  return {};
}

// Packaging:
auto PrintVisitor::visit(Import* t_import) -> Any
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

  return {};
}

DEF_PV_METHOD(ModuleDecl)

// Rvalue:
auto PrintVisitor::visit(Float* t_float) -> Any
{
  COUNTG_INIT();

  print("Float: ", t_float->get());

  return {};
}

auto PrintVisitor::visit(Integer* t_int) -> Any
{
  COUNTG_INIT();

  print("Integer: ", t_int->get());

  return {};
}

auto PrintVisitor::visit(String* t_str) -> Any
{
  COUNTG_INIT();

  print("String: ", t_str->get());

  return {};
}

auto PrintVisitor::visit(Boolean* t_bool) -> Any
{
  COUNTG_INIT();

  print("Boolean: ", t_bool->get());

  return {};
}

// Typing:
DEF_PV_METHOD(MethodDecl)
DEF_PV_METHOD(Interface)
DEF_PV_METHOD(MemberDecl)
DEF_PV_METHOD(Struct)
DEF_PV_METHOD(Impl)
DEF_PV_METHOD(DotExpr)

// Misc:
auto PrintVisitor::visit(List* t_list) -> Any
{
  COUNTG_INIT();

  print("List");
  for(NodePtr& node : *t_list) {
    node->accept(this);
  }

  return {};
}

auto PrintVisitor::visit([[maybe_unused]] Nil* t_nil) -> Any
{
  COUNTG_INIT();

  print("Nil");

  return {};
}
