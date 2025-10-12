#ifndef CROW_CROW_AST_NODE_FUNCTION_FUNCTION_CALL_HPP
#define CROW_CROW_AST_NODE_FUNCTION_FUNCTION_CALL_HPP

// Includes:
#include "../list.hpp"
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::function {
// Using Statements:
using node_traits::Args;
using node_traits::Identifier;

// Classes:
class FunctionCall : public Identifier, public Args {
  public:
  FunctionCall(std::string_view t_identifier, NodeListPtr&& t_args);

  AST_ARCHIVE_MAKE_TRAITS_ARCHIVEABLE(FunctionCall, Identifier, Args)
  AST_VISITOR_MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~FunctionCall() = default;
};
} // namespace ast::node::function

// Cereal type registration:
REGISTER_ARCHIVEABLE_TYPE(ast::node::function, FunctionCall);

#endif // CROW_CROW_AST_NODE_FUNCTION_FUNCTION_CALL_HPP
