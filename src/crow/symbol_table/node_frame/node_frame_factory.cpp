#include "node_frame_factory.hpp"

namespace symbol_table::node_frame {
NODE_USING_ALL_NAMESPACES()

// Public methods:
NodeFrameFactory::NodeFrameFactory(): m_tree_factory{}, m_register{}
{}

// Control:
auto NodeFrameFactory::visit(If* t_if) -> Any
{}

auto NodeFrameFactory::visit(Loop* t_loop) -> Any
{}

AST_VISITOR_STUB(NodeFrameFactory, Continue)
AST_VISITOR_STUB(NodeFrameFactory, Break)
AST_VISITOR_STUB(NodeFrameFactory, Defer)
AST_VISITOR_STUB(NodeFrameFactory, Return)

// Function:
auto NodeFrameFactory::visit(Parameter* t_param) -> Any
{
  // const auto type{str2nativetype(t_param->type())};

  // t_param->set_type({type});

  // return SymbolData{type};

  return {};
}

auto NodeFrameFactory::visit(Function* t_fn) -> Any
{
  const auto id{t_fn->identifier()};

  const auto params{t_fn->params()};
  const auto body{t_fn->body()};

  m_tree_factory.insert(id);

  push_scope();
  // Add parameters to nested scope.
  traverse(params);

  // Add body in nested scope.
  traverse(body);
  pop_scope();

  return {};
}

auto NodeFrameFactory::visit(Call* t_fn_call) -> Any
{
  const auto id{t_fn_call->identifier()};

  const auto fn_data{get_symbol_data_from_env(id)};
  const auto args{get_resolved_type_list(t_fn_call->args())};

  const auto fn{fn_data.function()};
  const auto params{fn->m_params};
  const auto return_type{fn->m_return_type};

  // if(args != params) {
  //   std::stringstream ss;

  //   ss << "Arguments passed to " << std::quoted(id)
  //      << " do not match parameters.\n";

  //   ss << "Function signature: fn " << id << "(" << params << ") -> "
  //      << return_type << " { ... }\n";

  //   ss << "Call signature: " << id << "(" << args << ")";

  //   throw_type_error(ss.str());
  // }

  // return fn->m_return_type;

  return {};
}

auto NodeFrameFactory::visit(ReturnType* t_rt) -> Any
{
  // return SymbolData{str2nativetype(t_rt->type())};
  return {};
}

// Lvalue:
// TODO: Account for when init expr is a nullptr
// TODO: Add TypeData annotation.
auto NodeFrameFactory::decl_expr(DeclExpr* t_decl) -> void
{
  auto expr{get_symbol_data(t_decl->init_expr())};

  const auto position{t_decl->position()};
  const auto type{t_decl->type()};

  const auto id{t_decl->identifier()};
}

// TODO: FIXME Disallow redeclaration of variables.
auto NodeFrameFactory::visit(Let* t_let) -> Any
{
  const auto id{t_let->identifier()};

  decl_expr(t_let);

  // // Create the SymbolData for a variable.
  // const SymbolData data{symbol::make_variable(true, expr_data)};
  // if(!add_symbol(id, data)) {
  //   // TODO: Throw!
  // }

  return {};
}

auto NodeFrameFactory::visit(Var* t_var) -> Any
{
  const auto id{t_var->identifier()};

  decl_expr(t_var);

  // Create the SymbolData for a variable.
  // const SymbolData data{symbol::make_variable(false, expr_data)};
  // if(!add_symbol(id, data)) {
  //   // TODO: Throw!
  // }

  return {};
}

AST_VISITOR_STUB(NodeFrameFactory, Variable)

// Operators:
AST_VISITOR_STUB(NodeFrameFactory, Arithmetic)
AST_VISITOR_STUB(NodeFrameFactory, Assignment)
AST_VISITOR_STUB(NodeFrameFactory, Comparison)

AST_VISITOR_STUB(NodeFrameFactory, Increment)
AST_VISITOR_STUB(NodeFrameFactory, Decrement)

AST_VISITOR_STUB(NodeFrameFactory, UnaryPrefix)

// Logical:
AST_VISITOR_STUB(NodeFrameFactory, Not)
AST_VISITOR_STUB(NodeFrameFactory, And)
AST_VISITOR_STUB(NodeFrameFactory, Or)

// Packaging:
AST_VISITOR_STUB(NodeFrameFactory, Import)
AST_VISITOR_STUB(NodeFrameFactory, ModuleDecl)

// Rvalue:
AST_VISITOR_STUB(NodeFrameFactory, Float)
AST_VISITOR_STUB(NodeFrameFactory, Integer)
AST_VISITOR_STUB(NodeFrameFactory, String)
AST_VISITOR_STUB(NodeFrameFactory, Boolean)

// Typing:
AST_VISITOR_STUB(NodeFrameFactory, MethodDecl)
AST_VISITOR_STUB(NodeFrameFactory, Interface)
AST_VISITOR_STUB(NodeFrameFactory, MemberDecl)
AST_VISITOR_STUB(NodeFrameFactory, Struct)
AST_VISITOR_STUB(NodeFrameFactory, Impl)
AST_VISITOR_STUB(NodeFrameFactory, DotExpr)

auto NodeFrameFactory::push_scope() -> void
{
  m_tree_factory.push_scope();
}

auto NodeFrameFactory::pop_scope() -> void
{
  m_tree_factory.pop_scope();
}

auto NodeFrameFactory::construct_frame(NodePtr t_ast) -> NodeFramePtr
{
  m_tree_factory.clear();

  traverse(t_ast);

  return {};
}
} // namespace symbol_table::node_frame
