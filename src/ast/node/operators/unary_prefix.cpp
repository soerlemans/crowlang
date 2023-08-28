#include "unary_prefix.hpp"


using namespace node::operators;

using namespace visitor;
using namespace token;

namespace {
constexpr auto tokentype2op(const TokenType t_tokentype) -> UnaryPrefixOp
{
  UnaryPrefixOp op;

  switch(t_tokentype) {
    case TokenType::PLUS:
      op = UnaryPrefixOp::PLUS;
      break;

    case TokenType::MINUS:
      op = UnaryPrefixOp::MINUS;
      break;

    default:
      // TODO: Error handling
      // This just prevents an warning
      op = UnaryPrefixOp::PLUS;
      break;
  }

  return op;
}
} // namespace

UnaryPrefix::UnaryPrefix(UnaryPrefixOp t_op, NodePtr&& t_left)
  : UnaryOperator{std::forward<NodePtr>(t_left)}, m_op{t_op}
{}


UnaryPrefix::UnaryPrefix(TokenType t_tokentype, NodePtr&& t_left)
  : UnaryOperator{std::forward<NodePtr>(t_left)},
    m_op{tokentype2op(t_tokentype)}
{}

auto UnaryPrefix::op() const -> UnaryPrefixOp
{
  return m_op;
}
