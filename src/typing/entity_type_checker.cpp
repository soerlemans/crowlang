#include "entity_type_checker.hpp"

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"
#include "../exception/type_error.hpp"

// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Private Functions:
namespace {
template<typename... Args>
inline auto make_fn_type(Args&&... t_args) -> FnTypePtr
{
  return std::make_shared<FnType>(std::forward<Args>(t_args)...);
}

template<typename... Args>
inline auto make_var_type(Args&&... t_args) -> FnTypePtr
{
  return std::make_shared<VarType>(std::forward<Args>(t_args)...);
}
} // namespace

// Methods:
// Functions:
auto EntityTypeChecker::visit(Function* t_fn) -> Any
{
  const auto id{t_fn->identifier()};

  // TODO: Resolve parameters
  // TODO: Resolve return type

  t_fn->params();
  t_fn->type();

  // m_env.find();

  return {};
}

// // Packaging:
AST_VISITOR_STUB(EntityTypeChecker, Import)
AST_VISITOR_STUB(EntityTypeChecker, ModuleDecl)

auto EntityTypeChecker::check(NodePtr t_ast) -> Env
{
  traverse(t_ast);

  return m_env;
}
