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
#include "crow/debug/debug.hpp"
#include "crow/types/semantic/symbol_data.hpp"

namespace semantic {
// Using Statements:
using diagnostic::throw_type_error;
using symbol::FnTypePtr;
using symbol::StructTypePtr;
using symbol::SymbolData;
using symbol::VarTypePtr;
using types::core::NativeType;

NODE_USING_ALL_NAMESPACES()

// Protected methods:
auto SemanticChecker::push_env() -> void
{
  m_symbol_state.push_env();
}

auto SemanticChecker::pop_env() -> void
{
  m_symbol_state.pop_env();
}

auto SemanticChecker::clear_env() -> void
{
  // Reset/clear the construction object.
  m_symbol_state.clear();
}

auto SemanticChecker::annotate_attr(AttributeData* t_node) -> void
{
  for(const auto& attr : m_active_attrs) {
    t_node->add_attribute(attr);
  }
}

auto SemanticChecker::annotate_type(TypeData* t_node, const SymbolData& t_data)
  -> void
{
  // Convert SymbolData to TypeVariant.
  const auto type_variant{t_data.type_variant()};

  // Annotate AST, with TypeVariant.
  t_node->set_type(type_variant);
}

// Environment state related methods:
auto SemanticChecker::add_symbol_declaration(const std::string_view t_key,
                                             const SymbolData& t_data) -> void
{
  // First check if the entry exists.
  const auto [iter, exists] = m_symbol_state.find(t_key);
  if(exists) {
    const auto& symbol{iter->second};

    std::stringstream ss{};
    switch(symbol.m_status) {
      case SymbolStatus::DECLARED:
        [[fallthrough]];
      case SymbolStatus::DEFINED: {
        // Check for conflicting.
        if(t_data != symbol.m_data) {
          ss << "Conflicting declarations and definitions for "
             << std::quoted(t_key) << ".";

          throw_type_error(ss.str());
        }
        break;
      }

      default: {
        using lib::stdexcept::throw_invalid_argument;

        throw_invalid_argument("Unhandled SymbolStatus case.");
        break;
      }
    }
  } else {
    Symbol symbol{SymbolStatus::DECLARED, t_data};
    m_symbol_state.insert({std::string{t_key}, symbol});
  }
}

auto SemanticChecker::add_symbol_definition(const std::string_view t_key,
                                            const SymbolData& t_data) -> void
{
  // First check if the entry exists.
  const auto [iter, exists] = m_symbol_state.find(t_key);
  if(exists) {
    auto& symbol{iter->second};

    std::stringstream ss{};
    switch(symbol.m_status) {
      case SymbolStatus::DECLARED: {
        // Check symbolData equality.
        if(t_data == symbol.m_data) {
          // Change from declaration to definition.
          symbol.m_status = SymbolStatus::DEFINED;
        } else {
          ss << "Conflicting declaration and definition for "
             << std::quoted(t_key) << ".";

          throw_type_error(ss.str());
        }
        break;
      }

      case SymbolStatus::DEFINED: {
        // Redefinition is not allowed so throw.
        ss << "Redefining " << std::quoted(t_key) << " is not allowed.";

        throw_type_error(ss.str());
        break;
      }

      default: {
        using lib::stdexcept::throw_invalid_argument;

        throw_invalid_argument("Unhandled SymbolStatus case.");
        break;
      }
    }
  } else {
    Symbol symbol{SymbolStatus::DEFINED, t_data};
    m_symbol_state.insert({std::string{t_key}, symbol});
  }
}

auto SemanticChecker::get_symbol_data_from_env(
  const std::string_view t_key) const -> SymbolData
{
  return m_symbol_state.get_data(t_key);
}

// Type promotion related methods:
auto SemanticChecker::handle_condition(const SymbolData& t_data,
                                       const TextPosition& t_pos) const -> void
{
  std::stringstream ss{};

  if(const auto opt{t_data.native_type()}; opt) {
    if(!is_condition(opt.value())) {
      ss << "Expected a pointer, integer or a boolean for a conditional "
         << "expression.\n\n";

      ss << t_pos;

      throw_type_error(ss.str());
    }
  } else {
    ss << "Non native types can not casted to " << std::quoted("bool")
       << ".\n\n";

    ss << t_pos;

    throw_type_error(ss.str());
  }
}

auto SemanticChecker::promote(const SymbolData& t_lhs, const SymbolData& t_rhs,
                              const PromotionMode t_mode) const
  -> NativeTypeOpt
{
  NativeTypeOpt opt{};

  const auto lhs{t_lhs.native_type()};
  const auto rhs{t_rhs.native_type()};

  // FIXME: For now we must ensure both types are native types to consider
  // promotion.
  if(lhs && rhs) {
    opt = m_type_promoter.promote(lhs.value(), rhs.value(), t_mode);
  }

  return opt;
}

auto SemanticChecker::get_symbol_data(NodePtr t_ptr) -> SymbolData
{
  SymbolData data;

  const auto any{traverse(t_ptr)};
  if(any.has_value()) {
    try {
      data = std::any_cast<SymbolData>(any);
    } catch(const std::bad_any_cast& err) {
      DBG_CRITICAL(err.what());

      // TODO: Print elegant error message and terminate.
      throw err;
    }
  }

  return data;
}

auto SemanticChecker::get_resolved_type(NodePtr t_ptr) -> SymbolData
{
  return get_symbol_data(t_ptr).resolve_type();
}

auto SemanticChecker::get_native_type(NodePtr t_ptr) -> NativeTypeOpt
{
  return get_symbol_data(t_ptr).native_type();
}

auto SemanticChecker::get_type_list(NodeListPtr t_list) -> SymbolDataList
{
  SymbolDataList list;

  for(const auto& ptr : *t_list) {
    list.push_back(get_symbol_data(ptr));
  }

  return list;
}

auto SemanticChecker::get_resolved_type_list(NodeListPtr t_list)
  -> SymbolDataList
{
  SymbolDataList list;

  for(const auto& ptr : *t_list) {
    list.push_back(get_resolved_type(ptr));
  }

  return list;
}

// Public methods:
SemanticChecker::SemanticChecker()
  : m_symbol_state{}, m_type_promoter{}, m_active_attrs{}
{}

// Control:
auto SemanticChecker::visit(If* t_if) -> Any
{
  const auto init_expr{t_if->init_expr()};
  const auto then{t_if->then()};
  const auto alt{t_if->alt()};

  // Init expression must be evaluated before condition.
  if(init_expr) {
    traverse(init_expr);
  }

  // The condition is resolved to a type.
  const auto cond{get_symbol_data(t_if->condition())};
  DBG_INFO("Condition: ", cond);

  handle_condition(cond, t_if->position());

  // Branch traversal:
  traverse(then);

  if(alt) {
    traverse(alt);
  }

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

  t_param->set_type({type});

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
  add_symbol_definition(id, data);
  DBG_INFO("Function: ", id, "(", params_type_list, ") -> ", ret_type);

  // Annotate AST.
  annotate_type(t_fn, data);
  annotate_attr(t_fn);

  // Register parameters to environment.
  push_env();
  for(const auto& node : *params) {
    // Gain a raw ptr (non owning).
    // If the AST changes the assertion will be triggered.
    const auto* param{dynamic_cast<Parameter*>(node.get())};
    DEBUG_ASSERT(param, R"(Was unable to cast to "Parameter*"!)", param, node,
                 params);

    const auto id{param->identifier()};
    const auto type{str2nativetype(param->type())};

    const SymbolData data{symbol::make_variable(false, type)};

    // Add parameter to environment.
    add_symbol_definition(id, data);
  }

  // Run type checking on the function body.
  traverse(t_fn->body());
  pop_env();

  return {};
}

auto SemanticChecker::visit(Call* t_fn_call) -> Any
{
  // TODO: Improve this code to be more generic and clean, error if this is
  // not a function name
  const auto id{t_fn_call->identifier()};

  // FIXME: Temporary whitelist for standard lib print and println:
  if(id == "print" || id == "println") {
    return {};
  }

  const auto fn_data{get_symbol_data_from_env(id)};
  const auto args{get_resolved_type_list(t_fn_call->args())};

  const auto fn{fn_data.function()};
  const auto params{fn->m_params};
  const auto return_type{fn->m_return_type};

  if(args != params) {
    std::stringstream ss;

    ss << "Arguments passed to " << std::quoted(id)
       << " do not match parameters.\n";

    ss << "Function signature: fn " << id << "(" << params << ") -> "
       << return_type << " { ... }\n";

    ss << "Call signature: " << id << "(" << args << ")";

    throw_type_error(ss.str());
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
  auto init_expr{t_decl->init_expr()};

  const auto position{t_decl->position()};
  const auto type{t_decl->type()};

  const auto id{t_decl->identifier()};

  // TODO: Handle the case where we have no init_expr and type is not empty!
  // if(init_expr)

  auto init_expr_data{get_symbol_data(init_expr)};

  std::stringstream ss{};
  if(!type.empty()) {
    ss << ": " << type;

    // TODO: Resolve non native types.
    const SymbolData data{str2nativetype(type)};

    const auto opt{
      promote(data, init_expr_data, PromotionMode::ENFORCE_RHS)};
    if(opt) {
      // Successfull type promotion.
      init_expr_data = opt.value();
    } else if(data != init_expr_data) {
      // Type annotation and expression deduced type do not match.
      std::stringstream err_ss{};
      const auto var{std::quoted(t_decl->identifier())};

      err_ss << "Init of " << var << " contains a type mismatch.\n\n";

      err_ss << "typeof " << var << " = " << data << "\n";
      err_ss << "typeof init_expr_data = " << init_expr_data << "\n\n";

      err_ss << t_decl->position();

      throw_type_error(err_ss.str());
    }
  }

  DBG_INFO(id, ss.str(), " = <expr>: ", init_expr_data);

  // Annotate AST.
  annotate_type(t_decl, init_expr_data);
  annotate_attr(t_decl);

  return init_expr_data;
}

// TODO: FIXME Disallow redeclaration of variables.
auto SemanticChecker::visit(Let* t_let) -> Any
{
  const auto id{t_let->identifier()};
  const auto init_expr_data{decl_expr(t_let)};

  // Create the SymbolData for a variable.
  const SymbolData data{symbol::make_variable(true, init_expr_data)};
  add_symbol_definition(id, data);

  return {};
}

auto SemanticChecker::visit(Var* t_var) -> Any
{
  const auto id{t_var->identifier()};
  const auto init_expr_data{decl_expr(t_var)};

  // Create the SymbolData for a variable.
  const SymbolData data{symbol::make_variable(false, init_expr_data)};
  add_symbol_definition(id, data);

  return {};
}

auto SemanticChecker::visit(Variable* t_var) -> Any
{
  const auto id{t_var->identifier()};
  const auto var_data{get_symbol_data_from_env(id)};

  DBG_INFO("Variable ", std::quoted(id), " of type ", var_data);

  // Annotate AST.
  t_var->set_type(var_data.type_variant());

  return {var_data};
}

// Meta:
auto SemanticChecker::visit(Attribute* t_attr) -> Any
{
  using ast::node::node_traits::AttributeArgs;

  const auto id{t_attr->identifier()};
  const auto params{t_attr->params()};
  const auto body{t_attr->body()};

  // TODO: Resolve parameters, and get them as strings.
  AttributeArgs args{};
  AttributeMetadata attr{id, std::move(args)};

  // Annotate attribute.
  t_attr->add_attribute(attr);

  // Push the current attribute on the context stack.
  // So we can refer to them later.
  m_active_attrs.push_back(attr);

  // Traverse body like normal.
  traverse(body);

  m_active_attrs.pop_back();

  return {};
}

auto SemanticChecker::visit(LetDecl* t_ldecl) -> Any
{
  const auto id{t_ldecl->identifier()};
  const auto type_data{str2nativetype(t_ldecl->type())};

  // Create the SymbolData for a variable.
  const SymbolData data{symbol::make_variable(true, type_data)};
  add_symbol_declaration(id, data);

  // Annotate AST.
  annotate_type(t_ldecl, type_data);
  annotate_attr(t_ldecl);

  return {};
}

auto SemanticChecker::visit(VarDecl* t_vdecl) -> Any
{
  const auto id{t_vdecl->identifier()};
  const auto type_data{str2nativetype(t_vdecl->type())};

  // Create the SymbolData for a variable.
  const SymbolData data{symbol::make_variable(false, type_data)};
  add_symbol_declaration(id, data);

  // Annotate AST.
  annotate_type(t_vdecl, type_data);
  annotate_attr(t_vdecl);

  return {};
}

auto SemanticChecker::visit(FunctionDecl* t_fdecl) -> Any
{
  const auto id{t_fdecl->identifier()};
  const auto ret_type{str2nativetype(t_fdecl->type())};
  const auto params{t_fdecl->params()};

  // Register function type signature to environment.
  const auto params_type_list{get_type_list(params)};
  const SymbolData data{symbol::make_function(params_type_list, ret_type)};

  add_symbol_declaration(id, data);
  DBG_INFO("FunctionDecl: ", id, "(", params_type_list, ") -> ", ret_type);

  // Annotate AST.
  annotate_type(t_fdecl, data);
  annotate_attr(t_fdecl);

  return {};
}

// Operators:
auto SemanticChecker::visit(Arithmetic* t_arith) -> Any
{
  const auto lhs{get_resolved_type(t_arith->left())};
  const auto rhs{get_resolved_type(t_arith->right())};
  const auto pos{t_arith->position()};

  BinaryOperationData data{lhs, rhs, pos};
  const auto ret{m_validator.validate_assignment(data)};

  // Annotate AST.
  annotate_type(t_arith, ret);

  return ret;
}

auto SemanticChecker::visit(Assignment* t_assign) -> Any
{
  const auto var{get_symbol_data(t_assign->left())};
  const auto var_resolved{var.resolve_type()};

  const auto expr{get_resolved_type(t_assign->right())};

  DBG_INFO("Typeof var: ", var_resolved);
  DBG_INFO("Typeof expr: ", expr);

  std::stringstream ss{};

  if(var.is_const()) {
    ss << "Assigning to a const variable is illegal.\n\n";

    ss << "<lhs> = <expr>\n";
    ss << "typeof lhs = " << var << "\n";
    ss << "typeof expr = " << expr << "\n\n";

    ss << t_assign->position();

    throw_type_error(ss.str());
  }

  // If the expression being assigned is castable too the type being assigned
  const auto opt{promote(var, expr, PromotionMode::ENFORCE_RHS)};
  if(!opt && var_resolved != expr) {
    ss << "Types do not match on assignment.\n\n";

    ss << "<lhs> = <expr>\n";
    ss << "typeof lhs = " << var << "\n";
    ss << "typeof expr = " << expr << "\n\n";

    ss << t_assign->position();

    throw_type_error(ss.str());
  }

  // Annotate AST.
  annotate_type(t_assign, var);

  return var;
}

auto SemanticChecker::visit(Comparison* t_comp) -> Any
{
  const auto lhs{get_symbol_data(t_comp->left())};
  const auto rhs{get_symbol_data(t_comp->right())};
  const auto pos{t_comp->position()};

  BinaryOperationData data{lhs, rhs, pos};
  const auto ret{m_validator.validate_comparison(data)};

  // TODO: Annotate types.

  return ret;
}

auto SemanticChecker::visit(Increment* t_inc) -> Any
{
  const auto opt{get_native_type(t_inc->left())};

  if(!opt) {
    // TODO: Add position
    throw_type_error("Trying to increment a non native type is illegal.");
  }

  if(!is_integer(opt.value())) {
    std::stringstream ss;

    ss << "Trying to increment a variable that is not an integer.";

    throw_type_error(ss.str());
  }

  return SymbolData{opt.value()};
}

auto SemanticChecker::visit(Decrement* t_dec) -> Any
{
  const auto opt{get_native_type(t_dec->left())};

  if(!opt) {
    // TODO: Add position
    throw_type_error("Trying to decrement a non native type is illegal.");
  }

  if(!is_integer(opt.value())) {
    std::stringstream ss;

    ss << "Trying to decrement a variable that is not an integer.";

    throw_type_error(ss.str());
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

  // Check types of
  handle_condition(lhs, t_not->position());

  return SymbolData{NativeType::BOOL};
}

// TODO: Create a helper method for these types of type checks
auto SemanticChecker::visit(And* t_and) -> Any
{
  const auto lhs{get_symbol_data(t_and->left())};
  const auto rhs{get_symbol_data(t_and->right())};
  const auto pos{t_and->position()};

  DBG_INFO("Typeof lhs: ", lhs);
  DBG_INFO("Typeof rhs: ", rhs);

  // Check if arguments
  handle_condition(lhs, pos);
  handle_condition(rhs, pos);

  return SymbolData{NativeType::BOOL};
}

auto SemanticChecker::visit(Or* t_or) -> Any
{
  const auto lhs{get_symbol_data(t_or->left())};
  const auto rhs{get_symbol_data(t_or->right())};
  const auto pos{t_or->position()};

  DBG_INFO("Typeof lhs: ", lhs);
  DBG_INFO("Typeof rhs: ", rhs);

  handle_condition(lhs, pos);
  handle_condition(rhs, pos);

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
auto SemanticChecker::visit(Method* t_meth) -> Any
{
  // const auto id{t_fn->identifier()};
  // const auto ret_type{str2nativetype(t_fn->type())};
  // const auto params{t_fn->params()};

  // // Register function type signature to environment.
  // const auto params_type_list{get_type_list(params)};
  // const SymbolData data{symbol::make_function(params_type_list, ret_type)};

  // // Add the function and ID to the environment.
  // add_symbol_definition(id, data);
  // DBG_INFO("Function: ", id, "(", params_type_list, ") -> ", ret_type);

  // // Annotate AST.
  // annotate_type(t_fn, data);
  // annotate_attr(t_fn);

  // // Register parameters to environment.
  // push_env();
  // for(const auto& node : *params) {
  //   // Gain a raw ptr (non owning).
  //   // If the AST changes the assertion will be triggered.
  //   const auto* param{dynamic_cast<Parameter*>(node.get())};
  //   DEBUG_ASSERT(param, R"(Was unable to cast to "Parameter*"!)", param,
  //   node,
  //                params);

  //   const auto id{param->identifier()};
  //   const auto type{str2nativetype(param->type())};

  //   const SymbolData data{symbol::make_variable(false, type)};

  //   // Add parameter to environment.
  //   add_symbol_definition(id, data);
  // }

  // // Run type checking on the function body.
  // traverse(t_fn->body());
  // pop_env();

  return {};
}
AST_VISITOR_STUB(SemanticChecker, Interface)
AST_VISITOR_STUB(SemanticChecker, MemberDecl)
AST_VISITOR_STUB(SemanticChecker, Struct)
AST_VISITOR_STUB(SemanticChecker, Self)
AST_VISITOR_STUB(SemanticChecker, DotExpr)

auto SemanticChecker::check(NodePtr t_ast) -> void
{
  // Semantically check the AST for correctness.
  // This also constructs the global symbol table.
  traverse(t_ast);

  // Create the return value containing the AST and the global SymbolTable.
  // const auto ptr{retrieve_symbol_table()};

  // Clear EnvState and release old SymbolTable ptr.
  clear_env();

  // return ptr;
}
} // namespace semantic
