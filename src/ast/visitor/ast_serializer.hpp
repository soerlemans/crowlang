#ifndef CROW_AST_VISITOR_AST_SERIALIZER_HPP
#define CROW_AST_VISITOR_AST_SERIALIZER_HPP


// Library Includes:
#include <cereal/archives/xml.hpp>

// Local Includes:
#include "node_visitor.hpp"

// Includes:
#include "../../exception/error.hpp"
#include "../node/include.hpp"


namespace ast::visitor {
// Using Statements;
using cereal::XMLOutputArchive;
using ArchivePtr = std::shared_ptr<XMLOutputArchive>;

// Classes:
/*!
 * Serializes an AST.
 * Useful for when compiling multiple files to keep memory footprint low by
 * serializing an AST to disk. Also commonly used for inspecting the AST.
 */
class AstSerializer : public NodeVisitor {
  private:
  ArchivePtr m_archive;

  protected:
  template<typename... Args>
  auto make_archive(Args&&... t_args) -> ArchivePtr
  {
    return std::make_shared<XMLOutputArchive>(std::forward<Args>(t_args)...);
  }

  template<typename... Args>
  auto archive(Args&&... t_args) -> void
  {
		using exception::error;

    if(!m_archive) {
      error("No archive pointer has been set.");
    }

    (*m_archive)(std::forward<Args>(t_args)...);
  }

  public:
  AstSerializer() = default;

  // Control:
  auto visit(node::control::If* t_if) -> Any override;
  auto visit(node::control::Loop* t_loop) -> Any override;
  auto visit(node::control::Continue* t_continue) -> Any override;
  auto visit(node::control::Break* t_break) -> Any override;
  auto visit(node::control::Return* t_return) -> Any override;

  // Function:
  auto visit(node::function::Parameter* t_param) -> Any override;
  auto visit(node::function::Function* t_fn) -> Any override;
  auto visit(node::function::FunctionCall* t_fn_call) -> Any override;
  auto visit(node::function::ReturnType* t_rt) -> Any override;

  // Lvalue:
  auto visit(node::lvalue::Const* t_const) -> Any override;
  auto visit(node::lvalue::Let* t_let) -> Any override;
  auto visit(node::lvalue::Variable* t_var) -> Any override;

  // Operators:
  auto visit(node::operators::Arithmetic* t_arith) -> Any override;
  auto visit(node::operators::Assignment* t_assign) -> Any override;
  auto visit(node::operators::Comparison* t_comp) -> Any override;

  auto visit(node::operators::Increment* t_inc) -> Any override;
  auto visit(node::operators::Decrement* t_dec) -> Any override;

  auto visit(node::operators::UnaryPrefix* t_up) -> Any override;

  // Logical:
  auto visit(node::operators::Not* t_not) -> Any override;
  auto visit(node::operators::And* t_and) -> Any override;
  auto visit(node::operators::Or* t_or) -> Any override;

  auto visit(node::operators::Ternary* t_ternary) -> Any override;

  // Packaging:
  auto visit(node::packaging::Import* t_import) -> Any override;
  auto visit(node::packaging::ModuleDecl* t_mod) -> Any override;

  // Rvalue:
  auto visit(node::rvalue::Float* t_float) -> Any override;
  auto visit(node::rvalue::Integer* t_int) -> Any override;
  auto visit(node::rvalue::String* t_str) -> Any override;
  auto visit(node::rvalue::Boolean* t_bool) -> Any override;

  // Typing:
  auto visit(node::typing::MethodDecl* t_md) -> Any override;
  auto visit(node::typing::Interface* t_ifc) -> Any override;
  auto visit(node::typing::MemberDecl* t_md) -> Any override;
  auto visit(node::typing::Struct* t_struct) -> Any override;
  auto visit(node::typing::Impl* t_impl) -> Any override;
  auto visit(node::typing::DotExpr* t_dot_expr) -> Any override;

  // Misc:
  auto visit(node::List* t_list) -> Any override;
  auto visit(node::Nil* t_nil) -> Any override;

  auto serialize(NodePtr t_ast, std::ostream& t_os) -> void;
  // auto deserialize(NodePtr t_ast, std::ostream& t_os) -> void;

  virtual ~AstSerializer() = default;
};
} // namespace ast::visitor

#endif // CROW_AST_VISITOR_AST_SERIALIZER_HPP
