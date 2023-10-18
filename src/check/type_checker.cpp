#include "type_checker.hpp"

// STL Includes:
#include <algorithm>
#include <any>
#include <iomanip>
#include <memory>
#include <ranges>

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"

// Local Includes:
#include "native_types.hpp"
#include "symbol_types.hpp"


// Using Statements:
using namespace check;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto TypeChecker::handle_condition(const SymbolData& t_data,
                                   const container::TextPosition& t_pos) const
  -> void
{
  std::stringstream ss;

  if(const auto opt{t_data.native_type()}; opt) {
    if(!is_condition(opt.value())) {
      ss << "Expected a pointer, integer or a boolean for a conditional "
            "expression."
         << "\n\n";

      ss << t_pos;

      type_error(ss.str());
    }
  } else {
    ss << "Non native types can not casted to ";
    ss << std::quoted("bool") << "."
       << "\n\n";

    ss << t_pos;

    type_error(ss.str());
  }
}

auto TypeChecker::add_symbol(const std::string_view t_id,
                             const SymbolData t_variant) -> void
{
  TypePair pair{t_id, t_variant};

  const auto result{m_envs.back().insert(pair)};
  if(!result.second) {
    // TODO: Throw exception, that name was already defined
  }
}

auto TypeChecker::get_symbol(std::string_view t_id) -> SymbolData
{
  bool found{false};
  SymbolData variant;

  // We want to traverse the scopes from inner to outer
  for(const auto& env : m_envs | std::views::reverse) {
    const std::string str{t_id};
    const auto iter{env.find(str)};
    if(iter != env.end()) {
      DBG_INFO("Found Symbol ", std::quoted(t_id), " in Env!");

      found = true;
      variant = iter->second;
    }
  }

  if(!found) {
    type_error("Identifier is not defined in environment");
  }

  return variant;
}

TypeChecker::TypeChecker(): m_envs{}
{}

// Control:
auto TypeChecker::visit(If* t_if) -> Any
{
  const auto cond{get_symbol_data(t_if->condition())};

  DBG_INFO("Condition: ", cond);

  handle_condition(cond, t_if->position());

  traverse(t_if->init_expr());
  traverse(t_if->then());
  traverse(t_if->alt());

  return {};
}

auto TypeChecker::visit(Loop* t_loop) -> Any
{
  const auto cond{get_symbol_data(t_loop->condition())};

  handle_condition(cond, t_loop->position());

  traverse(t_loop->init_expr());
  traverse(t_loop->body());
  traverse(t_loop->expr());

  return {};
}


AST_VISITOR_STUB(TypeChecker, Continue)
AST_VISITOR_STUB(TypeChecker, Break)

auto TypeChecker::visit(Return* t_return) -> Any
{
  const auto data{get_symbol_data(t_return->expr())};

  // TODO: Compare or indicate ReturnType to function somehow?
  return data;
}

// // Function:
auto TypeChecker::visit(Function* t_fn) -> Any
{
  const auto id{t_fn->identifier()};

  const auto type{str2nativetype(t_fn->type())};
  const auto params{get_type_list(t_fn->params())};

  SymbolData ptr{define_function(params, type)};
  add_symbol(id, ptr);

  traverse(t_fn->body());

  return {};
}

auto TypeChecker::visit(FunctionCall* t_fn_call) -> Any
{
  auto variant{get_symbol(t_fn_call->identifier())};

  // TODO: Improve this code to be more generic and clean, error if this is not
  // a function name
  const auto fn{std::get<FnTypePtr>(variant)};

  return fn->m_return_type;
}

auto TypeChecker::visit(ReturnType* t_rt) -> Any
{
  return SymbolData{str2nativetype(t_rt->type())};
}

// // Lvalue:
auto TypeChecker::visit(Let* t_let) -> Any
{
  using namespace exception;

  const auto type{t_let->type()};
  const auto expr{get_symbol_data(t_let->init_expr())};

  std::stringstream ss;
  if(!type.empty()) {
    ss << ": " << type;

    // TODO: Resolve non native types
    const SymbolData variant{str2nativetype(type)};
    if(variant != expr) {
      std::stringstream ss;
      const auto id{std::quoted(t_let->identifier())};

      ss << "Init of " << id << " contains a type mismatch.\n\n";

      ss << "typeof " << id << " = " << variant << "\n";
      ss << "typeof expr = " << expr << "\n\n";

      ss << t_let->position();

      type_error(ss.str());
    }
  }

  DBG_INFO(t_let->identifier(), ss.str(), " = <expr>: ", expr);

  // Work with variables that contain metadata later
  SymbolData data{define_variable(false, expr)};
  add_symbol(t_let->identifier(), data);

  return {};
}

auto TypeChecker::visit(Variable* t_var) -> Any
{
  const auto variant{get_symbol(t_var->identifier())};

  DBG_INFO("Variable ", std::quoted(t_var->identifier(), '\''), " of type ",
           variant);

  return variant;
}

// // Operators:
auto TypeChecker::visit(Arithmetic* t_arith) -> Any
{
  using namespace exception;

  const auto ret{get_symbol_data(t_arith->left())};

  const auto lhs{ret.native_type()};
  const auto rhs{get_symbol_data(t_arith->right()).native_type()};

  if(lhs != rhs) {
    // TODO: Implement type promotion later

    DBG_ERROR("Typeof: ", lhs, " != ", rhs);

    type_error("LHS and RHS types do not match!");
  }

  return ret;
}

auto TypeChecker::visit(Assignment* t_assign) -> Any
{
  using namespace exception;

  const auto var{get_symbol_data(t_assign->left())};
  const auto expr{get_symbol_data(t_assign->right())};

  if(var != expr) {
    std::stringstream ss;

    ss << "Types do not match on assignment.\n\n";

    ss << "typeof left hand side = " << var << "\n";
    ss << "typeof expr = " << expr << "\n";

    type_error(ss.str());
  }

  return var;
}

auto TypeChecker::visit(Comparison* t_comp) -> Any
{
  using namespace exception;

  const auto lhs{get_symbol_data(t_comp->left()).native_type()};
  const auto rhs{get_symbol_data(t_comp->right()).native_type()};

  if(lhs != rhs) {
    // TODO: Implement type promotion later

    type_error("LHS and RHS types do not match!");
  }

  return SymbolData{NativeType::BOOL};
}

auto TypeChecker::visit(Increment* t_inc) -> Any
{
  const auto left{get_symbol_data(t_inc->left())};

  return left;
}

auto TypeChecker::visit(Decrement* t_dec) -> Any
{
  const auto left{get_symbol_data(t_dec->left())};

  return left;
}

auto TypeChecker::visit(UnaryPrefix* t_up) -> Any
{
  const auto left{get_symbol_data(t_up->left())};

  return left;
}

// // Logical:
auto TypeChecker::visit(Not* t_not) -> Any
{
  using namespace exception;

  const auto lhs{get_symbol_data(t_not->left())};

  handle_condition(lhs, t_not->position());

  return SymbolData{NativeType::BOOL};
}

// TODO: Create a helper method for these types of type checks
auto TypeChecker::visit(And* t_and) -> Any
{
  using namespace exception;

  const auto lhs{get_symbol_data(t_and->left()).native_type()};
  const auto rhs{get_symbol_data(t_and->right()).native_type()};

  if(lhs && rhs) {
    if(!is_condition(lhs.value()) || !is_condition(rhs.value())) {
      type_error("LHS and RHS types do not match!");
    }
  } else {
    type_error("Both operands must be native types!");
  }

  return SymbolData{NativeType::BOOL};
}

auto TypeChecker::visit(Or* t_or) -> Any
{

  using namespace exception;

  const auto lhs{get_symbol_data(t_or->left()).native_type()};
  const auto rhs{get_symbol_data(t_or->right()).native_type()};

  if(lhs && rhs) {
    if(!is_condition(lhs.value()) || !is_condition(rhs.value())) {
      type_error("LHS and RHS types do not match!");
    }
  } else {
    type_error("Both operands must be native types!");
  }

  return SymbolData{NativeType::BOOL};
}

// Packaging:
AST_VISITOR_STUB(TypeChecker, Import)
AST_VISITOR_STUB(TypeChecker, ModuleDecl)

// Rvalue:
auto TypeChecker::visit([[maybe_unused]] Float* t_float) -> Any
{
  return SymbolData{NativeType::F64};
}

auto TypeChecker::visit([[maybe_unused]] Integer* t_int) -> Any
{
  return SymbolData{NativeType::INT};
}

auto TypeChecker::visit([[maybe_unused]] String* t_str) -> Any
{
  return SymbolData{NativeType::STRING};
}

auto TypeChecker::visit([[maybe_unused]] Boolean* t_bool) -> Any
{
  return SymbolData{NativeType::BOOL};
}

auto TypeChecker::check(NodePtr t_ast) -> void
{
  m_envs.clear();
  m_envs.emplace_back();

  traverse(t_ast);
}
