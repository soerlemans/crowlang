#include "ast_serializer.hpp"

// Includes:
#include "../../debug/log.hpp"


namespace ast::visitor {
// Using statements:
NODE_USING_ALL_NAMESPACES()

// Methods:
// Protected Methods:
// auto AstSerializer::get_xml_node(NodePtr t_ptr) -> xml_node
// {
//   xml_node node;

//   auto any{traverse(t_ptr)};
//   if(any.has_value()) {
//     try {
//       node = std::any_cast<xml_node>(any);
//     } catch(const std::bad_any_cast& e) {
//       DBG_CRITICAL(e.what());

//       // TODO: Print elegant error message and terminate
//       throw e;
//     }
//   }

//   return node;
// }

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

auto AstSerializer::visit(Return* t_return) -> Any
{
  return {};
}

// Function:
auto AstSerializer::visit(Parameter* t_param) -> Any
{
  return {};
}

auto AstSerializer::visit(Function* t_fn) -> Any
{
  // FIXME: Temp code.
  return traverse(t_fn->body());
}

auto AstSerializer::visit(FunctionCall* t_fn_call) -> Any
{
  return {};
}

auto AstSerializer::visit(ReturnType* t_rt) -> Any
{
  return {};
}

// Lvalue:
auto AstSerializer::visit(Const* t_const) -> Any
{
  return {};
}
auto AstSerializer::visit(Let* t_let) -> Any
{
  // FIXME: Temp
  return traverse(t_let->init_expr());
}

auto AstSerializer::visit(Variable* t_var) -> Any
{}

// Operators:
auto AstSerializer::visit(Arithmetic* t_arith) -> Any
{
  // xml_node node;

  // node.set_name("Arithmetic");

  // TODO: Cleanup.
  // node.append_child("Left") = get_xml_node(t_arith->left());
  // node.append_child("Right") = get_xml_node(t_arith->right());

  // return std::make_any<xml_node>(node);

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
  return {};
}

auto AstSerializer::visit(Integer* t_int) -> Any
{
  // xml_node node;

  // node.set_name("Integer");
  // node.append_attribute("Literal") = t_int->get();

  // return std::make_any<xml_node>(node);

  return {};
}

auto AstSerializer::visit(String* t_str) -> Any
{
  return {};
}

auto AstSerializer::visit(Boolean* t_bool) -> Any
{
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
  // xml_node node;
  for(NodePtr& elem : *t_list) {
    // const auto elem_node{get_xml_node(elem)};
    traverse(elem);

    // node.append_child("Elem:") = elem_node;
  }

  return {};
}

auto AstSerializer::visit([[maybe_unused]] Nil* t_nil) -> Any
{
  return {};
}

auto AstSerializer::serialize(NodePtr t_ast, std::ostream& t_os) -> void
{
  // const auto node{get_xml_node(t_ast)};

  // t_doc.insert_child_after("Abstract Syntax Tree", node);
}
} // namespace ast::visitor
