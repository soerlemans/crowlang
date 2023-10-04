#ifndef CROW_TYPING_ENTITY_TYPE_CHECKER_HPP
#define CROW_TYPING_ENTITY_TYPE_CHECKER_HPP

// Local Includes:
#include "typev_utilities.hpp"


namespace typing {
// Using statements:
using namespace ast;
using visitable::Any;

// Aliases:
//! Predominantly used for tying identifiers to types
template<Typename T = TypeV>
using NameTypeP = std::pair<std::string, T>;

//! Predominantly used for tying identifiers to types
template<typename T = TypeV>
using Env = std::map<std::string, T>;

using FnEnv = std::map<std::string, TypeV>;

// Structs:
//! Holds the environments of several types of software entities
struct Entities {
  FnEnv m_functions;
  Env m_globals;
  // Env m_types; // TODO: Implement and environement for keeping track of types
};
// Classes:
/*! This class resolves the names and types of functions ahead of time so that
 * the types are known to the TypeChecker ahead of time, this allows order
 * independent function definition
 */
class EntityTypeChecker : public TypeVVisitor {
  private:
  Entities m_entities;

  protected:
  auto add_function(NameTypeP t_pair) -> void;
  auto add_global(NameTypeP t_pair) -> void;

  public:
  EntityTypeChecker() = default;

  // Functions:
  auto visit(node::functions::Function* t_fn) -> Any override;

  // // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> Any override;

  auto resolve(node::NodePtr t_ast) -> Entities;

  virtual ~EntityTypeChecker() = default;
};
} // namespace typing

#endif // CROW_TYPING_ENTITY_TYPE_CHECKER_HPP
