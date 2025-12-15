#ifndef BACKTRACK_GUARD_HPP
#define BACKTRACK_GUARD_HPP

// Absolute Includes:
#include "crow/parser/parser.hpp"

// Macros;
#define PRATT_BACKTRACK_GUARD(t_node)                                \
  parser::pratt::BacktrackGuard CONCAT(pratt_backtrack, __COUNTER__) \
  {                                                                  \
    get_token_stream(), t_node                                        \
  }

namespace parser::pratt {
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

} // namespace parser::pratt

#endif // BACKTRACK_GUARD_HPP
