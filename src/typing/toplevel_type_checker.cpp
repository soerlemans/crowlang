#include "top_level_type_checker.hpp"

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"
#include "../exception/type_error.hpp"

// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto TopLevelTypeChecker::add_pairing(const NameTypeP t_pair) -> void
{
  m_env.insert(t_pair);
}

auto TopLevelTypeChecker::get_typev(NodePtr t_ptr) -> TypeV
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

// Functions:
auto TopLevelTypeChecker::visit(Function* t_fn) -> Any
{
  m_env.find()

    return {};
}

// // Packaging:
AST_VISITOR_STUB(TypeChecker, Import)
AST_VISITOR_STUB(TypeChecker, ModuleDecl)

auto TopLevelTypeChecker::resolve_functions(NodePtr t_ast) -> Env
{
  traverse(t_ast);

  return m_env;
}
