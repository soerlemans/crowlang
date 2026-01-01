// STL Includes:
#include <fstream>
#include <iostream>
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
  using container::TextBuffer;
  using lexer::Lexer;
  using parser::pratt::PrattParser;
  using token::TokenStream;

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
TEST(TestPrattParser, BasicAddition)
{
  // We only need to add.
  const auto program{"2 + 2"sv};
  const auto parser{prep_pratt_parser(program)};

  auto node{parser->expr()};

  EXPECT_TRUE(node != nullptr)
    << "Expression failed to parse: " << std::quoted(program) << '.';
}

TEST(TestPrattParser, BasicMultiplication)
{
  // We only need to add.
  const auto program{"2 * 2"sv};
  const auto parser{prep_pratt_parser(program)};

  auto node{parser->expr()};

  EXPECT_TRUE(node != nullptr)
    << "Expression failed to parse: " << std::quoted(program) << '.';
}

TEST(TestPrattParser, BasicPredenceTest)
{
  // We only need to add.
  const auto program{"2 * 2 + 3"sv};
  const auto parser{prep_pratt_parser(program)};

  auto node{parser->expr()};

  EXPECT_TRUE(node != nullptr)
    << "Expression failed to parse: " << std::quoted(program) << '.';
}
