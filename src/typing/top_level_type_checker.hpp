#ifndef CROW_TYPING_TOP_LEVEL_TYPE_CHECKER_HPP
#define CROW_TYPING_TOP_LEVEL_TYPE_CHECKER_HPP

// Local Includes:
#include "typev_utilities.hpp"


namespace typing {
// Using statements:
using namespace ast;
using visitable::Any;

// Aliases:
using NameTypeP = std::pair<std::string, TypeV>;
using Env = std::map<std::string, TypeV>;

/*! This class resolves the names and types of functions ahead of time so that
 * the types are known to the TypeChecker ahead of time, this allows order
 * independent function definition
 */
class ToplevelTypeChecker : public TypeVVisitor {
  private:
  Env m_env;

  protected:
  auto add_pairing(NameTypeP t_pair) -> void;

  public:
  ToplevelTypeChecker() = default;

  // Functions:
  auto visit(node::functions::Function* t_fn) -> Any override;

  // // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> Any override;

  auto resolve_functions(node::NodePtr t_ast) -> Env;

  virtual ~ToplevelTypeChecker() = default;
};
} // namespace typing

#endif // CROW_TYPING_TOP_LEVEL_TYPE_CHECKER_HPP
