#include "type_checker.hpp"

// STL Includes:
#include <any>
#include <variant>

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"
#include "../exception/type_error.hpp"
#include "native_types.hpp"

// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:
// Control:
AST_VISITOR_STUB(TypeChecker, If)
AST_VISITOR_STUB(TypeChecker, Loop)
AST_VISITOR_STUB(TypeChecker, Continue)
AST_VISITOR_STUB(TypeChecker, Break)

auto TypeChecker::visit([[maybe_unused]] Return* t_return) -> Any
{
  return {};
}

// Methods:
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

      throw TypeError{"LHS and RHS of 'Let' do not match!"};
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

    throw TypeError{"LHS and RHS types do not match!"};
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

    throw TypeError{"LHS and RHS types do not match!"};
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
