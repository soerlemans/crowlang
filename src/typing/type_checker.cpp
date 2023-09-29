#include "type_checker.hpp"

// Includes:
#include "../ast/node/include.hpp"


// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto TypeChecker::global_env() -> Env&
{
  return m_env.front();
}

auto TypeChecker::current_env() -> Env&
{
  return m_env.back();
}

TypeChecker::TypeChecker(): m_env{}
{
  // There should always be a global environment
  m_env.emplace_back();
}

// Rvalue:
auto TypeChecker::visit(node::rvalue::Float* t_float) -> Any
{}

auto TypeChecker::visit(node::rvalue::Integer* t_int) -> Any
{}

auto TypeChecker::visit(node::rvalue::String* t_str) -> Any
{}

auto TypeChecker::visit(node::rvalue::Boolean* t_bool) -> Any
{}
