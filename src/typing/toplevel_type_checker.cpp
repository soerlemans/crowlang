#include "top_level_type_checker.hpp"

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"
#include "../exception/type_error.hpp"

// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto ToplevelTypeChecker::add_pairing(const NameTypeP t_pair) -> void
{
  m_env.insert(t_pair);
}

// Functions:
auto ToplevelTypeChecker::visit(Function* t_fn) -> Any
{
  // m_env.find();

  return {};
}

// // Packaging:
AST_VISITOR_STUB(ToplevelTypeChecker, Import)
AST_VISITOR_STUB(ToplevelTypeChecker, ModuleDecl)

auto ToplevelTypeChecker::resolve_functions(NodePtr t_ast) -> Env
{
  traverse(t_ast);

  return m_env;
}
