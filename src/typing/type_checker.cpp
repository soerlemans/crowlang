#include "type_checker.hpp"

// STL Includes:
#include <any>
#include <variant>

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"
#include "../exception/type_error.hpp"

// Local Includes:
#include "native_types.hpp"


// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:

auto TypeChecker::type_error(std::string_view t_msg) -> void
{
  using namespace exception;

  throw TypeError{t_msg};
}

auto TypeChecker::add_pairing(NameTypeP t_pair) -> void
{
  m_env.back().insert(t_pair);
}

auto TypeChecker::get_typev(NodePtr t_ptr) -> TypeV
{
  TypeV typev;

  auto any{traverse(t_ptr)};
  if(any.has_value()) {
    try {
      typev = std::any_cast<TypeV>(any);
    } catch(const std::bad_any_cast& e) {
      DBG_CRITICAL(e.what());
    }
  }

  return typev;
}

TypeChecker::TypeChecker(): m_env{}
{
  // There should always be a global environment
  m_env.emplace_back();
}

// Control:
auto TypeChecker::visit(If* t_if) -> Any
{
  const auto cond{get_typev(t_if->condition())};

  // TODO: Test for numerics
  if(cond != TypeV{NativeType::BOOL}) {
    type_error("Expected a numeric or boolean in condition expression");
  }

  traverse(t_if->init_expr());
  traverse(t_if->then());
  traverse(t_if->alt());

  return {};
}

auto TypeChecker::visit(Loop* t_loop) -> Any
{
  const auto cond{get_typev(t_loop->condition())};

  // TODO: Test for numerics
  if(cond != TypeV{NativeType::BOOL}) {
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
  return get_typev(t_return->expr());
}

// // Function:
auto TypeChecker::visit(Function* t_fn) -> Any
{
  // TODO: Implement
  traverse(t_fn->body());

  return {};
}

// // Lvalue:
auto TypeChecker::visit(Let* t_let) -> Any
{
  using namespace exception;

  const auto type{t_let->type()};
  const auto expr_typev{get_typev(t_let->init_expr())};
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

  NameTypeP pair{t_let->identifier(), expr_type};
  add_pairing(pair);

  return {};
}

// // Operators:
auto TypeChecker::visit(node::operators::Arithmetic* t_arith) -> Any
{
  using namespace exception;

  const auto lhs{get_typev(t_arith->left())};
  const auto rhs{get_typev(t_arith->right())};

  if(lhs != rhs) {
    // TODO: Implement type promotion later

    type_error("LHS and RHS types do not match!");
  }

  return lhs;
}

auto TypeChecker::visit(Comparison* t_comp) -> Any
{
  using namespace exception;

  const auto lhs{get_typev(t_comp->left())};
  const auto rhs{get_typev(t_comp->right())};

  if(lhs != rhs) {
    // TODO: Implement type promotion later

    type_error("LHS and RHS types do not match!");
  }

  return TypeV{NativeType::BOOL};
}

auto TypeChecker::visit(Increment* t_inc) -> Any
{
  const auto left{get_typev(t_inc->left())};

  return left;
}

auto TypeChecker::visit(Decrement* t_dec) -> Any
{
  const auto left{get_typev(t_dec->left())};

  return left;
}

auto TypeChecker::visit(UnaryPrefix* t_up) -> Any
{
  const auto left{get_typev(t_up->left())};

  return left;
}

// // Logical:
auto TypeChecker::visit(Not* t_not) -> Any
{
  using namespace exception;

  const auto lhs{get_typev(t_not->left())};

  const auto is_bool{[](const auto& t_v) {
    return t_v == TypeV{NativeType::BOOL};
  }};

  if(is_bool(lhs)) {
    type_error("LHS and RHS types do not match!");
  }

  return TypeV{NativeType::BOOL};
}

// TODO: Create a helper method for these types of type checks
auto TypeChecker::visit(And* t_and) -> Any
{
  using namespace exception;

  const auto lhs{get_typev(t_and->left())};
  const auto rhs{get_typev(t_and->right())};

  const auto is_bool{[](const auto& t_v) {
    return t_v == TypeV{NativeType::BOOL};
  }};

  if(is_bool(lhs) && is_bool(rhs)) {
    type_error("LHS and RHS types do not match!");
  }

  return TypeV{NativeType::BOOL};
}

auto TypeChecker::visit(Or* t_or) -> Any
{

  using namespace exception;

  const auto lhs{get_typev(t_or->left())};
  const auto rhs{get_typev(t_or->right())};

  const auto is_bool{[](const auto& t_v) {
    return t_v == TypeV{NativeType::BOOL};
  }};

  if(is_bool(lhs) && is_bool(rhs)) {
    type_error("LHS and RHS types do not match!");
  }

  return TypeV{NativeType::BOOL};
}

// Packaging:
AST_VISITOR_STUB(TypeChecker, Import)
AST_VISITOR_STUB(TypeChecker, ModuleDecl)

// Rvalue:
auto TypeChecker::visit([[maybe_unused]] Float* t_float) -> Any
{
  return TypeV{NativeType::F64};
}

auto TypeChecker::visit([[maybe_unused]] Integer* t_int) -> Any
{
  return TypeV{NativeType::INT};
}

auto TypeChecker::visit([[maybe_unused]] String* t_str) -> Any
{
  return TypeV{};
}

auto TypeChecker::visit([[maybe_unused]] Boolean* t_bool) -> Any
{
  return TypeV{NativeType::BOOL};
}
