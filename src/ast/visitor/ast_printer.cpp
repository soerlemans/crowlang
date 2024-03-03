#include "ast_printer.hpp"

// STL Includes:
#include <iomanip>
#include <ios>
#include <sstream>


// Macros:
//! TODO: Comment.
#define COUNTG_INIT() \
  CountGuard guard    \
  {                   \
    m_counter         \
  }

/*!
 * Defines a @ref AstPrinter method, that will print all traits.
 *
 * @param[in] t_type Type of Node to accept.
 */
#define DEFINE_PRINTER_METHOD(t_type)                         \
  auto AstPrinter::visit([[maybe_unused]] t_type* t_ptr)->Any \
  {                                                           \
    COUNTG_INIT();                                            \
                                                              \
    print(#t_type);                                           \
    print_traits(t_ptr);                                      \
                                                              \
    return {};                                                \
  }

namespace ast::visitor {
// Using statements:
NODE_USING_ALL_NAMESPACES()

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
auto AstPrinter::print_if(std::string_view t_str, NodePtr t_ptr) -> void
{
  if(t_ptr) {
    print(t_str);
    traverse(t_ptr);
  }
}

AstPrinter::AstPrinter(std::ostream& t_os): m_os{t_os}
{}

// Control:
DEFINE_PRINTER_METHOD(If)
DEFINE_PRINTER_METHOD(Loop)
DEFINE_PRINTER_METHOD(Continue)
DEFINE_PRINTER_METHOD(Break)
DEFINE_PRINTER_METHOD(Return)

// Function:
DEFINE_PRINTER_METHOD(Parameter)
DEFINE_PRINTER_METHOD(Function)

auto AstPrinter::visit(Call* t_fn_call) -> Any
{
  COUNTG_INIT();

  print("Function call");
  print("| Identifier: ", t_fn_call->identifier());
  print_if("Arguments: ", t_fn_call->args());

  return {};
}

DEFINE_PRINTER_METHOD(ReturnType)

// Lvalue:
DEFINE_PRINTER_METHOD(Let)
DEFINE_PRINTER_METHOD(Var)

auto AstPrinter::visit(Variable* t_var) -> Any
{
  COUNTG_INIT();

  print("Variable: ", t_var->identifier());
  print_traits(t_var);

  return {};
}

// Operators:
auto AstPrinter::visit(Arithmetic* t_arith) -> Any
{
  COUNTG_INIT();

  print("Arithmetic");
  print_traits(t_arith);
  // print("| OP: TODO!");

  return {};
}

auto AstPrinter::visit(Assignment* t_assign) -> Any
{
  COUNTG_INIT();

  print("Assignment");
  print_traits(t_assign);
  // print("| OP: TODO!");

  return {};
}

auto AstPrinter::visit(Comparison* t_comp) -> Any
{
  COUNTG_INIT();

  print("Comparison");
  print_traits(t_comp);
  // print("| OP: TODO!");

  return {};
}

auto AstPrinter::visit(Increment* t_inc) -> Any
{
  COUNTG_INIT();

  print("Increment");
  print("| Prefix: ", t_inc->prefix());
  print_traits(t_inc);

  return {};
}

auto AstPrinter::visit(Decrement* t_dec) -> Any
{
  COUNTG_INIT();

  print("Decrement");
  print("| Prefix: ", t_dec->prefix());
  print_traits(t_dec);

  return {};
}

auto AstPrinter::visit(UnaryPrefix* t_up) -> Any
{
  COUNTG_INIT();

  print("UnaryPrefix");
  print_traits(t_up);
  print("| OP: TODO!");

  return {};
}

// Logical:
DEFINE_PRINTER_METHOD(Not)
DEFINE_PRINTER_METHOD(And)
DEFINE_PRINTER_METHOD(Or)

auto AstPrinter::visit(Ternary* t_ternary) -> Any
{
  COUNTG_INIT();

  print("Ternary");
  print_traits(t_ternary);

  return {};
}

// Packaging:
auto AstPrinter::visit(Import* t_import) -> Any
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

DEFINE_PRINTER_METHOD(ModuleDecl)

// Rvalue:
auto AstPrinter::visit(Float* t_float) -> Any
{
  COUNTG_INIT();

  print("Float: ", t_float->get());

  return {};
}

auto AstPrinter::visit(Integer* t_int) -> Any
{
  COUNTG_INIT();

  print("Integer: ", t_int->get());

  return {};
}

auto AstPrinter::visit(String* t_str) -> Any
{
  COUNTG_INIT();

  print("String: ", t_str->get());

  return {};
}

auto AstPrinter::visit(Boolean* t_bool) -> Any
{
  COUNTG_INIT();

  print("Boolean: ", t_bool->get());

  return {};
}

// Typing:
DEFINE_PRINTER_METHOD(MethodDecl)
DEFINE_PRINTER_METHOD(Interface)
DEFINE_PRINTER_METHOD(MemberDecl)
DEFINE_PRINTER_METHOD(Struct)
DEFINE_PRINTER_METHOD(Impl)
DEFINE_PRINTER_METHOD(DotExpr)

// Misc:
auto AstPrinter::visit(List* t_list) -> Any
{
  COUNTG_INIT();

  print("List");
  for(NodePtr& node : *t_list) {
    traverse(node);
  }

  return {};
}

auto AstPrinter::visit([[maybe_unused]] Nil* t_nil) -> Any
{
  COUNTG_INIT();

  print("Nil");

  return {};
}

auto AstPrinter::print(NodePtr t_ast) -> void
{
  traverse(t_ast);
}
} // namespace ast::visitor
