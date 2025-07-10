#include "parser.hpp"

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "crow/diagnostic/syntax_error.hpp"
#include "crow/token/tokentype2str.hpp"

namespace parser {
// Using statements:
using ast::node::List;
using ast::node::NodeListPtr;

// Protected Methods:
auto Parser::get_token_stream() -> TokenStream&
{
  return m_token_stream;
}

auto Parser::syntax_error(const std::string_view t_msg) const -> void
{
  using exception::SyntaxError;

  const auto token{get_token()};

  throw SyntaxError{std::string{t_msg}, token.position()};
}

// FIXME: This function should be replaced with the printing of a stacktrace
auto Parser::eos_error(const std::string_view t_msg) const -> void
{
  if(m_token_stream.eos()) {
    std::stringstream ss;
    ss << "EOS reached!\n";
    ss << " - ";
    ss << t_msg;

    throw std::runtime_error{ss.str()};
  }
}

auto Parser::eos() const -> bool
{
  return m_token_stream.eos();
}

auto Parser::check(const TokenType t_type) -> bool
{
  eos_error("Tried to check for token at EOS!");

  const auto token{m_token_stream.current()};

  return token.type() == t_type;
}

auto Parser::next() -> Token&
{
  eos_error("Tried to move to next Token at EOS!");

  return m_token_stream.next();
}

auto Parser::expect(const TokenType t_type) -> Token&
{
  if(!check(t_type)) {
    std::stringstream ss;
    ss << "Expected -> ";
    ss << std::quoted(tokentype2str(t_type), '\'');

    syntax_error(ss.str());
  }

  auto& token{get_token()};

  next();

  return token;
}

auto Parser::prev() -> Token&
{
  return m_token_stream.prev();
}

auto Parser::get_token() const -> Token&
{
  eos_error("Tried to return get token at EOS!");

  return m_token_stream.current();
}

auto Parser::get_position() const -> const TextPosition&
{
  return get_token().position();
}

//! This method is used to verify if a certain token is located after newlines
auto Parser::after_newlines(const TokenType t_type) -> bool
{
  DBG_TRACE_FN(VERBOSE);

  bool found{false};

  for(auto iter{m_token_stream.iter()}; iter != m_token_stream.end(); iter++) {
    if(iter->type() != TokenType::NEWLINE) {
      if(iter->type() == t_type) {
        found = true;

        DBG_TRACE_PRINT(VERBOSE,
                        "Found: ", std::quoted(tokentype2str(t_type), '\''));

        // Update iterator
        m_token_stream.set(iter);
      }

      break;
    }
  }

  return found;
}

//! Creates a list of the given function type
auto Parser::list_of(const ParseFn t_fn) -> NodeListPtr
{
  DBG_TRACE_FN(VERBOSE);
  auto nodes{make_node<List>()};

  while(!eos()) {
    if(auto ptr{t_fn()}; ptr) {
      nodes->push_back(std::move(ptr));
    } else {
      break;
    }
  }

  return nodes;
}

// Methods:
Parser::Parser(TokenStream&& t_token_stream)
  : m_token_stream{std::forward<TokenStream>(t_token_stream)}
{}
} // namespace parser
