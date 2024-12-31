#include "semantic_checker.hpp"

// STL Includes:
#include <algorithm>
#include <any>
#include <iomanip>
#include <memory>
#include <ranges>
#include <sstream>

// Library Includes:
#include <libassert/assert.hpp>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/debug/log.hpp"

// Local Includes:
#include "symbol/symbol_data.hpp"

namespace check {
// Using Statements:
using ast::node::node_traits::typing::NativeType;
using exception::type_error;
using symbol::FnTypePtr;
using symbol::StructTypePtr;
using symbol::SymbolData;
using symbol::VarTypePtr;

NODE_USING_ALL_NAMESPACES()

// Methods:
SemanticChecker::SemanticChecker()
{}

// Control:
auto SemanticChecker::visit(If* t_if) -> Any
{
  // Init expression must be evaluated before condition.
  traverse(t_if->init_expr());

  const auto cond{get_symbol_data(t_if->condition())};

  DBG_INFO("Condition: ", cond);

  handle_condition(cond, t_if->position());

  traverse(t_if->then());
  traverse(t_if->alt());

  return {};
}

auto SemanticChecker::visit(Loop* t_loop) -> Any
{
  // Init expression must be evaluated before condition.
  traverse(t_loop->init_expr());

  // A loops condition maybe empty, which is an endless loop.
  if(t_loop->condition()) {
    const auto cond{get_symbol_data(t_loop->condition())};

    DBG_INFO("Condition: ", cond);

    handle_condition(cond, t_loop->position());
  }

  traverse(t_loop->body());
  traverse(t_loop->expr());

  return {};
}

AST_VISITOR_STUB(SemanticChecker, Continue)
AST_VISITOR_STUB(SemanticChecker, Break)
AST_VISITOR_STUB(SemanticChecker, Defer)

auto SemanticChecker::visit(Return* t_return) -> Any
{
  // FIXME: Check if type of expression being returned.
  // Matches the functions return type.
  const auto data{get_symbol_data(t_return->expr())};

  return data;
}

// Function:
auto SemanticChecker::visit(Parameter* t_param) -> Any
{
  const auto type{str2nativetype(t_param->type())};

  return SymbolData{type};
}

auto SemanticChecker::visit(Function* t_fn) -> Any
{
  const auto id{t_fn->identifier()};
  const auto ret_type{str2nativetype(t_fn->type())};
  const auto params{t_fn->params()};

  // Register function type signature to environment.
  const auto params_type_list{get_type_list(params)};
  const SymbolData data{symbol::make_function(params_type_list, ret_type)};

  // Add the function and ID to the environment.
  add_symbol(id, data);
  DBG_INFO("Function: ", id, "(", params_type_list, ") -> ", ret_type);

  // Annotate AST.
  t_fn->set_type(data.type_variant());

  // Register parameters to environment.
  push_env();
  for(const auto& node : *params) {
    // Gain a raw ptr (non owning).
    // If the AST changes the assertion will be triggered.
    const auto* param{dynamic_cast<Parameter*>(node.get())};
    DEBUG_ASSERT(param, "Was unable to cast to \"Parameter*\"!", param,
                 node, params);

    const auto id{param->identifier()};
    const auto type{str2nativetype(param->type())};

    const SymbolData data{symbol::make_variable(false, type)};

    add_symbol(id, data);
  }

  // Run type checking on the function body.
  traverse(t_fn->body());
  pop_env();

  return {};
}

auto SemanticChecker::visit(Call* t_fn_call) -> Any
{
  // TODO: Improve this code to be more generic and clean, error if this is not
  // a function name
  const auto id{t_fn_call->identifier()};

  // FIXME: Temporary whitelist for standard lib print and println:
  if(id == "print" || id == "println") {
    return {};
  }

  const auto data{get_symbol(id)};
  const auto args{get_resolved_type_list(t_fn_call->args())};

  const auto fn{data.function()};
  const auto params{fn->m_params};
  const auto return_type{fn->m_return_type};

  if(args != params) {
    std::stringstream ss;

    ss << "Arguments passed to " << std::quoted(id)
       << " do not match parameters.\n";

    ss << "Function signature: fn " << id << "(" << params << ") -> "
       << return_type << " { ... }\n";

    ss << "Call signature: " << id << "(" << args << ")";

    type_error(ss.str());
  }

  return fn->m_return_type;
}

auto SemanticChecker::visit(ReturnType* t_rt) -> Any
{
  return SymbolData{str2nativetype(t_rt->type())};
}

// Lvalue:
// TODO: Account for when init expr is a nullptr
// TODO: Add TypeData annotation.
auto SemanticChecker::decl_expr(DeclExpr* t_decl) -> SymbolData
{
  auto expr{get_symbol_data(t_decl->init_expr())};

  const auto position{t_decl->position()};
  const auto type{t_decl->type()};

  const auto id{t_decl->identifier()};

  std::stringstream ss;
  if(!type.empty()) {
    ss << ": " << type;

    // TODO: Resolve non native types.
    const SymbolData data{str2nativetype(type)};

    const auto opt{promote(data, expr, true)};
    if(opt) {
      expr = opt.value();
    } else if(data != expr) {
      std::stringstream err_ss;
      const auto var{std::quoted(t_decl->identifier())};

      err_ss << "Init of " << var << " contains a type mismatch.\n\n";

      err_ss << "typeof " << var << " = " << data << "\n";
      err_ss << "typeof expr = " << expr << "\n\n";

      err_ss << t_decl->position();

      type_error(err_ss.str());
    }
  }

  DBG_INFO(id, ss.str(), " = <expr>: ", expr);

  // Annotate AST.
  t_decl->set_type(expr.type_variant());

  return expr;
}

// TODO: FIXME Disallow redeclaration of variables.
auto SemanticChecker::visit(Let* t_let) -> Any
{
  const auto id{t_let->identifier()};
  const auto expr_data{decl_expr(t_let)};

  // Create the SymbolData for a variable.
  const SymbolData data{symbol::make_variable(true, expr_data)};
  add_symbol(id, data);

  return {};
}

auto SemanticChecker::visit(Var* t_var) -> Any
{
  const auto id{t_var->identifier()};
  const auto expr_data{decl_expr(t_var)};

  // Create the SymbolData for a variable.
  const SymbolData data{symbol::make_variable(false, expr_data)};
  add_symbol(id, data);

  return {};
}

auto SemanticChecker::visit(Variable* t_var) -> Any
{
  const auto id{t_var->identifier()};
  const auto var{get_symbol(id)};

  DBG_INFO("Variable ", std::quoted(id), " of type ", var);

  // Annotate AST.
  t_var->set_type(var.type_variant());

  return var;
}

// Operators:
auto SemanticChecker::visit(Arithmetic* t_arith) -> Any
{
  auto ret{get_symbol_data(t_arith->left())};

  const auto lhs{ret.resolve_type()};
  const auto rhs{get_resolved_type(t_arith->right())};

  DBG_INFO("Typeof lhs: ", lhs);
  DBG_INFO("Typeof rhs: ", rhs);

  const auto opt{promote(lhs, rhs)};
  if(opt) {
    ret = opt.value();
  } else if(lhs != rhs) {
    std::stringstream ss;

    DBG_ERROR("Typeof: ", lhs, " != ", rhs);

    ss << "Arithmetic operation contains a type mismatch.\n";
    ss << "typeof lhs = " << lhs << "\n";
    ss << "typeof rhs = " << rhs << "\n\n";

    ss << t_arith->position();

    type_error(ss.str());
  }

  // Annotate AST.
  t_arith->set_type(ret.type_variant());

  DBG_INFO("Result: ", ret);

  return ret;
}

auto SemanticChecker::visit(Assignment* t_assign) -> Any
{
  using namespace exception;

  const auto var{get_symbol_data(t_assign->left())};
  const auto var_resolved{var.resolve_type()};

  const auto expr{get_resolved_type(t_assign->right())};

  DBG_INFO("Typeof var: ", var_resolved);
  DBG_INFO("Typeof expr: ", expr);

  std::stringstream ss;

  if(var.is_const()) {
    ss << "Assigning to a const variable is illegal.\n\n";

    ss << "<lhs> = <expr>\n";
    ss << "typeof lhs = " << var << "\n";
    ss << "typeof expr = " << expr << "\n\n";

    ss << t_assign->position();

    type_error(ss.str());
  }

  // If the expression being assigned is castable too the typ ebeing assigned
  const auto opt{promote(var, expr, true)};
  if(!opt && var_resolved != expr) {
    ss << "Types do not match on assignment.\n\n";

    ss << "<lhs> = <expr>\n";
    ss << "typeof lhs = " << var << "\n";
    ss << "typeof expr = " << expr << "\n\n";

    ss << t_assign->position();

    type_error(ss.str());
  }

  // TODO: Annotate types.

  return var;
}

auto SemanticChecker::visit(Comparison* t_comp) -> Any
{
  const auto lhs{get_symbol_data(t_comp->left())};
  const auto rhs{get_symbol_data(t_comp->right())};

  DBG_INFO("Typeof lhs: ", lhs);
  DBG_INFO("Typeof rhs: ", rhs);

  const auto opt{promote(lhs, rhs)};
  if(!opt && lhs != rhs) {
    std::stringstream ss;

    ss << "Comparison operation contains a type mismatch.\n";
    ss << "typeof lhs = " << lhs << "\n";
    ss << "typeof rhs = " << rhs << "\n\n";

    ss << t_comp->position();

    type_error(ss.str());
  }

  // TODO: Annotate types.

  return SymbolData{NativeType::BOOL};
}

auto SemanticChecker::visit(Increment* t_inc) -> Any
{
  const auto opt{get_native_type(t_inc->left())};

  if(!opt) {
    // TODO: Add position
    type_error("Trying to increment a non native type is illegal.");
  }

  if(!is_integer(opt.value())) {
    std::stringstream ss;

    ss << "Trying to increment a variable that is not an integer.";

    type_error(ss.str());
  }

  return SymbolData{opt.value()};
}

auto SemanticChecker::visit(Decrement* t_dec) -> Any
{
  const auto opt{get_native_type(t_dec->left())};

  if(!opt) {
    // TODO: Add position
    type_error("Trying to decrement a non native type is illegal.");
  }

  if(!is_integer(opt.value())) {
    std::stringstream ss;

    ss << "Trying to decrement a variable that is not an integer.";

    type_error(ss.str());
  }

  return SymbolData{opt.value()};
}

auto SemanticChecker::visit(UnaryPrefix* t_up) -> Any
{
  const auto left{get_symbol_data(t_up->left())};

  // TODO: Implement

  return left;
}

// Logical:
auto SemanticChecker::visit(Not* t_not) -> Any
{
  const auto lhs{get_symbol_data(t_not->left())};

  DBG_INFO("Typeof lhs: ", lhs);

  handle_condition(lhs, t_not->position());

  return SymbolData{NativeType::BOOL};
}

// TODO: Create a helper method for these types of type checks
auto SemanticChecker::visit(And* t_and) -> Any
{
  const auto lhs{get_symbol_data(t_and->left())};
  const auto rhs{get_symbol_data(t_and->right())};

  DBG_INFO("Typeof lhs: ", lhs);
  DBG_INFO("Typeof rhs: ", rhs);

  handle_condition(lhs, t_and->position());
  handle_condition(rhs, t_and->position());

  return SymbolData{NativeType::BOOL};
}

auto SemanticChecker::visit(Or* t_or) -> Any
{
  const auto lhs{get_symbol_data(t_or->left())};
  const auto rhs{get_symbol_data(t_or->right())};

  DBG_INFO("Typeof lhs: ", lhs);
  DBG_INFO("Typeof rhs: ", rhs);

  handle_condition(lhs, t_or->position());
  handle_condition(rhs, t_or->position());

  return SymbolData{NativeType::BOOL};
}

// Packaging:
AST_VISITOR_STUB(SemanticChecker, Import)
AST_VISITOR_STUB(SemanticChecker, ModuleDecl)

// Rvalue:
auto SemanticChecker::visit([[maybe_unused]] Float* t_float) -> Any
{
  return SymbolData{NativeType::F64};
}

auto SemanticChecker::visit([[maybe_unused]] Integer* t_int) -> Any
{
  return SymbolData{NativeType::INT};
}

auto SemanticChecker::visit([[maybe_unused]] String* t_str) -> Any
{
  return SymbolData{NativeType::STRING};
}

auto SemanticChecker::visit([[maybe_unused]] Boolean* t_bool) -> Any
{
  return SymbolData{NativeType::BOOL};
}

// Typing:
AST_VISITOR_STUB(SemanticChecker, MethodDecl)
AST_VISITOR_STUB(SemanticChecker, Interface)
AST_VISITOR_STUB(SemanticChecker, MemberDecl)
AST_VISITOR_STUB(SemanticChecker, Struct)
AST_VISITOR_STUB(SemanticChecker, Impl)
AST_VISITOR_STUB(SemanticChecker, DotExpr)

auto SemanticChecker::check(NodePtr t_ast) -> void
{
  traverse(t_ast);

  clear_env();
}
} // namespace check
