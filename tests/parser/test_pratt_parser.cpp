// STL Includes:
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// Library Includes:
#include <gtest/gtest.h>

// Crow Absolute Includes:
#include "crow/ast/node/include.hpp"
#include "crow/container/text_buffer.hpp"
#include "crow/lexer/lexer.hpp"
#include "crow/parser/pratt/pratt_parser.hpp"

/*!
 * @file
 *
 */


// Using namespace Declarations:
using namespace std::literals::string_view_literals;

// Helper functions:
namespace {
auto prep_pratt_parser(const std::string_view t_program)
  -> parser::pratt::PrattParser
{
  using ast::node::NodePtr;
  using container::TextBuffer;
  using lexer::Lexer;
  using parser::pratt::PrattParser;
  using token::TokenStream;

  std::stringstream ss;

  // Write program.
  auto stream_ptr{std::make_shared<TextBuffer>()};
  stream_ptr->add_line(std::string{t_program});

  // Create AST from TextBuffer.
  Lexer lexer{stream_ptr};
  TokenStream tokenstream{lexer.tokenize()};
  PrattParser parser{tokenstream};

  return parser;
}
} // namespace

// Test Cases:
TEST(TestPrattParser, BasicExpressions)
{
  using ast::node::NodePtr;
  using ast::node::rvalue::Integer;

  // Printer.
  SECTION("Basic addition")
  {
    const auto program{""sv};
    prep_pratt_parser(program);
  }

  SECTION("Basic arithmetic")
  {
    const auto program{""sv};
    prep_pratt_parser(program);
  }
}
