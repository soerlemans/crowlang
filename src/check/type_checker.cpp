#include "type_checker.hpp"

// STL Includes:
#include <algorithm>
#include <any>
#include <memory>
#include <variant>

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"
#include "../exception/type_error.hpp"


// Using Statements:
using namespace check;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto TypeChecker::type_error(std::string_view t_msg) -> void
{
  using namespace exception;

  throw TypeError{t_msg};
}

auto TypeChecker::add_entity(const std::string_view t_id, TypeVariant t_variant)
  -> void
{
  TypePair pair{t_id, t_variant};

  const auto result{m_env.back().insert(pair)};
  if(!result.second) {
    // TODO: Throw exception, that name was already defined
  }
}

auto TypeChecker::get_entity(std::string_view t_id) -> TypeVariant
{
  bool found{false};
  TypeVariant variant;

  std::for_each(m_env.rbegin(), m_env.rend(), [&](const auto& t_env) {
    const std::string str{t_id};
    const auto iter{t_env.find(str)};
    if(iter != t_env.end()) {
      DBG_INFO("Found ID!: ", t_id);

      found = true;
      variant = iter->second;
    }
  });

  if(!found) {
    type_error("Identifier is not defined in environment");
  }

  return variant;
}

TypeChecker::TypeChecker(): m_env{}
{}

// Control:
auto TypeChecker::visit(If* t_if) -> Any
{
  const auto cond{get_variant(t_if->condition())};

  DBG_INFO("Condition: ", cond);

  if(!is_condition(cond.get_type())) {
    type_error("Expected a numeric or boolean in condition expression");
  }

  traverse(t_if->init_expr());
  traverse(t_if->then());
  traverse(t_if->alt());

  return {};
}

auto TypeChecker::visit(Loop* t_loop) -> Any
{
  const auto cond{get_variant(t_loop->condition())};

  // TODO: Test for numerics
  if(!is_condition(cond.get_type())) {
    type_error("Expected a numeric or boolean in condition expression");
  }

  traverse(t_loop->init_expr());
  traverse(t_loop->body());
  traverse(t_loop->expr());

  return {};
}


AST_VISITOR_STUB(TypeChecker, Continue)
AST_VISITOR_STUB(TypeChecker, Break)

auto TypeChecker::visit(Return* t_return) -> Any
{
  // TODO: Compare Return Type somehow?
  return get_variant(t_return->expr());
}

// // Function:
auto TypeChecker::visit(Function* t_fn) -> Any
{
  const auto id{t_fn->identifier()};

  // TODO: Implement
  traverse(t_fn->body());

  return {};
}

// // Lvalue:
auto TypeChecker::visit(Let* t_let) -> Any
{
  using namespace exception;

  const auto type{t_let->type()};
  const auto expr_typev{get_variant(t_let->init_expr())};

	//! TODO: Find a more sophisticated way of getting an index
  const auto expr_type{nativetype2str(std::get<NativeType>(expr_typev))};

  std::stringstream ss;
  if(!type.empty()) {
    ss << ": " << type;

    if(type != expr_type) {
      DBG_ERROR("Init of ", std::quoted(t_let->identifier()),
                " contains a type mismatch");

      type_error("LHS and RHS of 'Let' do not match!");
    }
  }

  DBG_INFO(t_let->identifier(), ss.str(), " = <expr>: ", expr_type);

  TypeVariant variant{std::make_shared<VarType>(false, expr_typev)};
  add_entity(t_let->identifier(), variant);

  return {};
}

auto TypeChecker::visit(Variable* t_var) -> Any
{
  const auto variant{get_entity(t_var->identifier())};

  DBG_INFO("Variable ", std::quoted(t_var->identifier(), '\''), " of type ",
           variant);

  return variant;
}

// // Operators:
auto TypeChecker::visit(node::operators::Arithmetic* t_arith) -> Any
{
  using namespace exception;

  const auto lhs{get_variant(t_arith->left())};
  const auto rhs{get_variant(t_arith->right())};

  if(lhs != rhs) {
    // TODO: Implement type promotion later

    type_error("LHS and RHS types do not match!");
  }

  return lhs;
}

auto TypeChecker::visit(Comparison* t_comp) -> Any
{
  using namespace exception;

  const auto lhs{get_variant(t_comp->left())};
  const auto rhs{get_variant(t_comp->right())};

  if(lhs != rhs) {
    // TODO: Implement type promotion later

    type_error("LHS and RHS types do not match!");
  }

  return TypeVariant{NativeType::BOOL};
}

auto TypeChecker::visit(Increment* t_inc) -> Any
{
  const auto left{get_variant(t_inc->left())};

  return left;
}

auto TypeChecker::visit(Decrement* t_dec) -> Any
{
  const auto left{get_variant(t_dec->left())};

  return left;
}

auto TypeChecker::visit(UnaryPrefix* t_up) -> Any
{
  const auto left{get_variant(t_up->left())};

  return left;
}

// // Logical:
auto TypeChecker::visit(Not* t_not) -> Any
{
  using namespace exception;

  const auto lhs{get_variant(t_not->left())};

  if(!is_condition(lhs.get_type())) {
    type_error("LHS and RHS types do not match!");
  }

  return TypeVariant{NativeType::BOOL};
}

// TODO: Create a helper method for these types of type checks
auto TypeChecker::visit(And* t_and) -> Any
{
  using namespace exception;

  const auto lhs{get_variant(t_and->left())};
  const auto rhs{get_variant(t_and->right())};

  if(!is_condition(lhs.get_type()) || !is_condition(rhs.get_type())) {
    type_error("LHS and RHS types do not match!");
  }

  return TypeVariant{NativeType::BOOL};
}

auto TypeChecker::visit(Or* t_or) -> Any
{

  using namespace exception;

  const auto lhs{get_variant(t_or->left())};
  const auto rhs{get_variant(t_or->right())};

  if(!is_condition(lhs.get_type()) || !is_condition(rhs.get_type())) {
    type_error("LHS and RHS types do not match!");
  }

  return TypeVariant{NativeType::BOOL};
}

// Packaging:
AST_VISITOR_STUB(TypeChecker, Import)
AST_VISITOR_STUB(TypeChecker, ModuleDecl)

// Rvalue:
auto TypeChecker::visit([[maybe_unused]] Float* t_float) -> Any
{
  return TypeVariant{NativeType::F64};
}

auto TypeChecker::visit([[maybe_unused]] Integer* t_int) -> Any
{
  return TypeVariant{NativeType::INT};
}

auto TypeChecker::visit([[maybe_unused]] String* t_str) -> Any
{
  return TypeVariant{};
}

auto TypeChecker::visit([[maybe_unused]] Boolean* t_bool) -> Any
{
  return TypeVariant{NativeType::BOOL};
}

auto TypeChecker::check(NodePtr t_ast) -> void
{
  m_env.clear();
  m_env.emplace_back();

  traverse(t_ast);
}
