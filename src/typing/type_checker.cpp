#include "type_checker.hpp"


using namespace typing;

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
// auto visit(node::rvalue::Float* t_float) -> Any override;
// auto visit(node::rvalue::Integer* t_int) -> Any override;
// auto visit(node::rvalue::String* t_str) -> Any override;
// auto visit(node::rvalue::Boolean* t_bool) -> Any override;
