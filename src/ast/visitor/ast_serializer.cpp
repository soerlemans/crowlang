#include "ast_serializer.hpp"

// Includes:
#include "../../debug/log.hpp"
#include <boost/archive/xml_oarchive.hpp>


namespace ast::visitor {
// Using statements:
NODE_USING_ALL_NAMESPACES()

// Methods:
// Public: Methods:
// Control:
auto AstSerializer::visit(If* t_if) -> Any
{
  return {};
}

auto AstSerializer::visit(Loop* t_loop) -> Any
{
  return {};
}

auto AstSerializer::visit(Continue* t_continue) -> Any
{
  return {};
}

auto AstSerializer::visit(Break* t_break) -> Any
{
  return {};
}

auto AstSerializer::visit(Return* t_ret) -> Any
{
  // archive(*t_ret);

  return {};
}

// Function:
auto AstSerializer::visit(Parameter* t_param) -> Any
{
  return {};
}

auto AstSerializer::visit(Function* t_fn) -> Any
{
  archive(*t_fn);

  return {};
}

auto AstSerializer::visit(Call* t_fn_call) -> Any
{
  return {};
}

auto AstSerializer::visit(ReturnType* t_rt) -> Any
{
  return {};
}

// Lvalue:
auto AstSerializer::visit(Let* t_let) -> Any
{
  archive(*t_let);

  return {};
}

auto AstSerializer::visit(Var* t_var) -> Any
{
  return {};
}

auto AstSerializer::visit(Variable* t_var) -> Any
{
  // archive(*t_var);

  return {};
}

// Operators:
auto AstSerializer::visit(Arithmetic* t_arith) -> Any
{
	archive(*t_arith);

  return {};
}

auto AstSerializer::visit(Assignment* t_assign) -> Any
{}

auto AstSerializer::visit(Comparison* t_comp) -> Any
{}

auto AstSerializer::visit(Increment* t_inc) -> Any
{}

auto AstSerializer::visit(Decrement* t_dec) -> Any
{}

auto AstSerializer::visit(UnaryPrefix* t_up) -> Any
{}

// Logical:
auto AstSerializer::visit(Not* t_not) -> Any
{
  return {};
}
auto AstSerializer::visit(And* t_and) -> Any
{
  return {};
}
auto AstSerializer::visit(Or* t_or) -> Any
{
  return {};
}

auto AstSerializer::visit(Ternary* t_ternary) -> Any
{
  return {};
}

// Packaging:
auto AstSerializer::visit(Import* t_import) -> Any
{
  // for(const auto& pair : t_import->imports()) {
  //   std::stringstream ss;
  //   if(pair.second) {
  //     ss << " Identifier: " << pair.second.value();
  //   }

  //   print("| Pkg: ", std::quoted(pair.first), ss.str());
  // }

  return {};
}

auto AstSerializer::visit(ModuleDecl* t_md) -> Any
{
  return {};
}

// Rvalue:
auto AstSerializer::visit(Float* t_float) -> Any
{
  archive(*t_float);

  return {};
}

auto AstSerializer::visit(Integer* t_int) -> Any
{
  archive(*t_int);

  return {};
}

auto AstSerializer::visit(String* t_str) -> Any
{
  archive(*t_str);

  return {};
}

auto AstSerializer::visit(Boolean* t_bool) -> Any
{
  archive(*t_bool);

  return {};
}

// Typing:
auto AstSerializer::visit(MethodDecl* t_md) -> Any
{
  return {};
}

auto AstSerializer::visit(Interface* t_inf) -> Any
{
  return {};
}

auto AstSerializer::visit(MemberDecl* t_md) -> Any
{
  return {};
}

auto AstSerializer::visit(Struct* t_struct) -> Any
{
  return {};
}

auto AstSerializer::visit(Impl* t_impl) -> Any
{
  return {};
}

auto AstSerializer::visit(DotExpr* t_dot_expr) -> Any
{
  return {};
}

// Misc:
auto AstSerializer::visit(List* t_list) -> Any
{
  for(NodePtr& elem : *t_list) {
    traverse(elem);
  }

  return {};
}

auto AstSerializer::visit([[maybe_unused]] Nil* t_nil) -> Any
{
  return {};
}

auto AstSerializer::serialize(NodePtr t_ast, std::ostream& t_os) -> void
{
  // Set the archive pointer.
  m_archive = make_archive(t_os);

  traverse(t_ast);

  m_archive.reset();
}
} // namespace ast::visitor
