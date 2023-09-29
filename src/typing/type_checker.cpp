#include "type_checker.hpp"

// STL Includes:
#include <any>
#include <variant>

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"


// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto TypeChecker::add_pairing(NameTypeP t_pair) -> void
{
  m_env.back().insert(t_pair);
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
  auto any{traverse(t_let->init_expr())};
  const auto type{std::any_cast<TypeV>(any)};

  std::visit(
    [&]([[maybe_unused]] auto v) {
      DBG_CRITICAL("Type pairing: { Identifier: ", t_let->identifier(),
                   ", Type: ", "}");
    },
    type);

  NameTypeP pair{t_let->identifier(), type};
  add_pairing(pair);

  return {};
}

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
