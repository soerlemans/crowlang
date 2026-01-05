#ifndef CROW_CROW_AST_NODE_USER_TYPES_METHOD_CALL_HPP
#define CROW_CROW_AST_NODE_USER_TYPES_METHOD_CALL_HPP

// Includes:
#include "../list.hpp"
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::user_types {
// Using Statements:
using node_traits::Args;
using node_traits::Identifier;

// Classes:
class MethodCall : public Identifier, public Args {
  public:
  MethodCall(std::string_view t_identifier, NodeListPtr&& t_args);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(MethodCall, Identifier, Args)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~MethodCall() = default;
};
} // namespace ast::node::user_types

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::user_types, MethodCall);

#endif // CROW_CROW_AST_NODE_USER_TYPES_METHOD_CALL_HPP
