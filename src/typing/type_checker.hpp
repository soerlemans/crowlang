#ifndef CROW_TYPING_TYPE_CHECKER_HPP
#define CROW_TYPING_TYPE_CHECKER_HPP

// STL Includes:
#include <list>
#include <string_view>
#include <variant>

// Local includes:
#include "type_variant_helper.hpp"


namespace typing {
// Using statements:
using namespace ast;
using visitable::Any;

// Aliases:
using NameTypeP = std::pair<std::string, TypeVariant>;
using Env = std::map<std::string, TypeVariant>;
using EnvStack = std::list<Env>;

// Classes:
class TypeChecker : public TypeVariantHelper {
  private:
  EnvStack m_env;

  protected:
  auto type_error(std::string_view t_msg) -> void;
  auto add_pairing(NameTypeP t_pair) -> void;
  auto get_type_env(std::string_view t_id) -> TypeVariant;

  public:
  TypeChecker();

  // Control:
  auto visit(node::control::If* t_if) -> Any override;
  auto visit(node::control::Loop* t_loop) -> Any override;
  auto visit(node::control::Continue* t_continue) -> Any override;
  auto visit(node::control::Break* t_break) -> Any override;
  auto visit(node::control::Return* t_return) -> Any override;

  // // Function:
  auto visit(node::functions::Function* t_fn) -> Any override;
  // auto visit(node::functions::FunctionCall* t_fn_call) -> Any override;
  // auto visit(node::functions::ReturnType* t_rt) -> Any override;

  // // Lvalue:
  // auto visit(node::lvalue::Const* t_const) -> Any override;
  auto visit(node::lvalue::Let* t_let) -> Any override;
  auto visit(node::lvalue::Variable* t_var) -> Any override;

  // // Operators:
  auto visit(node::operators::Arithmetic* t_arith) -> Any override;
  // auto visit(node::operators::Assignment* t_assignment) -> Any override;
  auto visit(node::operators::Comparison* t_comp) -> Any override;

  auto visit(node::operators::Increment* t_inc) -> Any override;
  auto visit(node::operators::Decrement* t_dec) -> Any override;

  auto visit(node::operators::UnaryPrefix* t_up) -> Any override;

  // // Logical:
  auto visit(node::operators::Not* t_not) -> Any override;
  auto visit(node::operators::And* t_and) -> Any override;
  auto visit(node::operators::Or* t_or) -> Any override;

  // auto visit(node::operators::Ternary* t_ternary) -> Any override;

  // // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> Any override;

  // // Rvalue:
  auto visit(node::rvalue::Float* t_float) -> Any override;
  auto visit(node::rvalue::Integer* t_int) -> Any override;
  auto visit(node::rvalue::String* t_str) -> Any override;
  auto visit(node::rvalue::Boolean* t_bool) -> Any override;

  // // Typing:
  // auto visit(node::typing::MethodDecl* t_md) -> Any override;
  // auto visit(node::typing::Interface* t_ifc) -> Any override;
  // auto visit(node::typing::MemberDecl* t_md) -> Any override;
  // auto visit(node::typing::Struct* t_struct) -> Any override;
  // auto visit(node::typing::Impl* t_impl) -> Any override;
  // auto visit(node::typing::DotExpr* t_dot_expr) -> Any override;

  ~TypeChecker() override = default;
};
} // namespace typing

#endif // CROW_TYPING_TYPE_CHECKER_HPP
