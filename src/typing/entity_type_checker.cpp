#include "entity_type_checker.hpp"

// Includes:
#include "../ast/node/include.hpp"
#include "../debug/log.hpp"
#include "../exception/type_error.hpp"
#include "toplevel_type_checker.hpp"

// Using Statements:
using namespace typing;

NODE_USING_ALL_NAMESPACES()

// Methods:
auto EntityTypeChecker::add_pairing(const NameTypeP t_pair) -> void
{
  m_env.insert(t_pair);
}

// Functions:
auto EntityTypeChecker::visit(Function* t_fn) -> Any
{
  // m_env.find();

  return {};
}

// // Packaging:
AST_VISITOR_STUB(EntityTypeChecker, Import)
AST_VISITOR_STUB(EntityTypeChecker, ModuleDecl)

auto EntityTypeChecker::resolve(NodePtr t_ast) -> TopLevelEntities
{
  traverse(t_ast);

  return m_entities;
}
