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
#include "crow/parser/crow/crow_parser.hpp"
#include "crow/parser/pratt/pratt_parser.hpp"

/*!
 * @file
 *
 */


// Using:
using namespace std::literals::string_view_literals;

using parser::pratt::PrattParserPtr;

using PrattExprs = std::vector<std::string_view>;

// Helper functions:
namespace {
auto prep_pratt_parser(const std::string_view t_program) -> PrattParserPtr
{
  // PrattParser is abstract so we.
  // Init a crow parser and parse back an interface ptr.

  using container::TextBuffer;
  using lexer::Lexer;
  using parser::crow::CrowParser;
  using token::TokenStream;

  // Write program.
  auto stream_ptr{std::make_shared<TextBuffer>()};
  stream_ptr->add_line(std::string{t_program});

  // Create AST from TextBuffer.
  Lexer lexer{stream_ptr};
  TokenStream tokenstream{lexer.tokenize()};

  PrattParserPtr parser{std::make_unique<CrowParser>(tokenstream)};

  return parser;
}
} // namespace

// Test Cases:
TEST(TestPrattParser, BasicExpressions)
{
  PrattExprs exprs = {
    "2 + 2"sv,       "2 * 2"sv,         "2 * 2 + 3"sv,
    "2 * (2 + 3)"sv, "2 * 6 - 4 / 2"sv, "(2 * 6 - 3) + 10 / 2"sv,
    "6 / 2 - 3"sv,
  };

  for(auto&& program : exprs) {
    const auto parser{prep_pratt_parser(program)};

    auto node{parser->expr()};

    EXPECT_TRUE(node != nullptr)
      << "Expression failed to parse: " << std::quoted(program) << '.';
  }
}

TEST(TestPrattParser, BasicInvalidExpressions)
{
  using diagnostic::SyntaxError;

  PrattExprs exprs = {
    "2 + "sv,
    "2 + * 2"sv,
  };

  for(auto&& program : exprs) {
    const auto parser{prep_pratt_parser(program)};

    try {
      auto node{parser->expr()};
    } catch(SyntaxError& err) {
      SUCCEED();

    } catch(std::exception& err) {
      FAIL() << "Exception for program " << std::quoted(program)
             << " error: " << err.what() << '.';

    } catch(...) {
      FAIL() << "Uncaught exception for program " << std::quoted(program)
             << '.';
    }
  }
}
