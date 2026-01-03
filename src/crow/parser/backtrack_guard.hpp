#ifndef CROW_CROW_PARSER_BACKTRACK_GUARD_HPP
#define CROW_CROW_PARSER_BACKTRACK_GUARD_HPP

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "crow/token/token_stream.hpp"

// Macros;
#define PARSER_BACKTRACK_GUARD(t_node)                        \
  parser::BacktrackGuard CONCAT(pratt_backtrack, __COUNTER__) \
  {                                                           \
    get_token_stream(), t_node                                \
  }

namespace parser {
// Using Statements:
using ast::node::NodePtr;
using token::TokenStream;

// Need to make sure this is a safe construct.
/*!
 * Roll back the tokenstream to where it was before attempting to parse
something.
 * Only do it if we dont get a hit.
 * This is not really pretty or efficient but kind of necessary.
 * For more elaborate expression parsing around `., ->, *, [], etc`.
 * I hope to only use this in the Pratt Parser.
 */
class BacktrackGuard {
  private:
  TokenStream& m_stream;
  TokenStream::Iterator m_iter;

  // Check for nullptr, at end of lifetime.
  NodePtr& m_node;

  public:
  BacktrackGuard(TokenStream& t_stream, NodePtr& t_node);

  virtual ~BacktrackGuard();
};

} // namespace parser

#endif // CROW_CROW_PARSER_BACKTRACK_GUARD_HPP
