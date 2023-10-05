#ifndef CROW_TYPING_ENTITY_TYPE_CHECKER_HPP
#define CROW_TYPING_ENTITY_TYPE_CHECKER_HPP

// Local Includes:
#include "type_variant_helper.hpp"


namespace typing {
// Aliases:
//! Predominantly used for tying identifiers to types
using TypePair = std::pair<std::string, TypeVariant>;

//! Predominantly used for tying identifiers to types
using Env = std::map<std::string, TypeVariant>;

// Classes:
/*! This class resolves the names and types of functions ahead of time so that
 * the types are known to the TypeChecker ahead of time, this allows order
 * independent function definition
 */
class EntityTypeChecker : public TypeVariantHelper {
  private:
  Env m_env;

  protected:
  auto add_entity(TypePair t_pair) -> void;

  public:
  EntityTypeChecker() = default;

  // Functions:
  auto visit(node::functions::Function* t_fn) -> Any override;

  // // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> Any override;

  auto resolve(node::NodePtr t_ast) -> Env;

  virtual ~EntityTypeChecker() = default;
};
} // namespace typing

#endif // CROW_TYPING_ENTITY_TYPE_CHECKER_HPP
