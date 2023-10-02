#ifndef CROW_TYPING_TYPE_CHECKER_HPP
#define CROW_TYPING_TYPE_CHECKER_HPP

// STL Includes:
#include <list>
#include <string_view>
#include <variant>

// Includes:
#include "../ast/visitor/node_visitor.hpp"

// Local includes:
#include "native_types.hpp"


namespace typing {
// Using statements:
using namespace ast;
using visitable::Any;

// Aliases:
//! This is an abbreviation for TypeVariant
using TypeV = std::variant<NativeType, std::string>;
using NameTypeP = std::pair<std::string, TypeV>;
using Env = std::map<std::string, TypeV>;
using EnvStack = std::list<Env>;

// Classes:
class TypeChecker : public ast::visitor::NodeVisitor {
  private:
  EnvStack m_env;

  protected:
  auto type_error(std::string_view t_msg) -> void;
  auto add_pairing(NameTypeP t_pair) -> void;
  auto get_type_env(std::string_view t_id) -> TypeV;
  auto get_typev(ast::node::NodePtr t_ptr) -> TypeV;

  // TODO: Move somewhere else? these methods could effectively be static
  //! Check if a TypeV is one of the following arguments
  template<typename... Args>
  auto is_any_of(const TypeV& t_typev, Args&&... t_args) -> bool
  {
    return ((t_typev == TypeV{t_args}) || ...);
  }

  auto is_integer(const TypeV& t_typev) -> bool;
  auto is_float(const TypeV& t_typev) -> bool;
  auto is_bool(const TypeV& t_typev) -> bool;

  auto is_condition(const TypeV& t_typev) -> bool;
  auto is_numeric(const TypeV& t_typev) -> bool;

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

auto operator<<(std::ostream& t_os, const typing::TypeV t_typev)
  -> std::ostream&;

#endif // CROW_TYPING_TYPE_CHECKER_HPP
