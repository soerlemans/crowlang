// STL Includes:
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// Library Includes:
#include <gtest/gtest.h>

// Absolute Includes:
#include "crow/ast/node/include.hpp"
#include "crow/container/text_buffer.hpp"
#include "crow/diagnostic/diagnostic.hpp"
#include "crow/lexer/lexer.hpp"
#include "crow/parser/crow/crow_parser.hpp"
#include "crow/parser/pratt/pratt_parser.hpp"
#include "lib/stdexcept/stdexcept.hpp"

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

inline auto report_parse_failure(std::string_view t_program) -> std::string
{
  std::ostringstream ss{};

  ss << "Failed to parse " << std::quoted(t_program);

  return ss.str();
}

template<typename T>
inline auto report_exception(std::string_view t_program, T& t_err)
  -> std::string
{
  std::ostringstream ss{};

  ss << "Exception for program " << std::quoted(t_program)
     << " error: " << t_err.what() << '.';

  return ss.str();
}

inline auto report_uncaught_exception(std::string_view t_program) -> std::string
{
  std::ostringstream ss{};

  ss << "Uncaught exception for program " << std::quoted(t_program) << '.';

  return ss.str();
}
} // namespace

// Test Cases:
TEST(TestPrattParser, BasicExpressions)
{
  PrattExprs exprs = {
    "2 + 2"sv,
    "2 * 2"sv,
    "2 * 2 + 3"sv,
    "2 * (2 + 3)"sv,
    "2 * 6 - 4 / 2"sv,
    "(2 * 6 - 3) + 10 / 2"sv,
    "6 / 2 - 3"sv,
    "2 * num1"sv,
    "2 * num1 + num2"sv,
    "num1 / 2 - num2"sv,
    "(2 * num1 - 3) + num2 / num3"sv,
  };

  for(auto&& program : exprs) {
    const auto parser{prep_pratt_parser(program)};

    auto node{parser->expr()};

    EXPECT_TRUE(node != nullptr)
      << "Expression failed to parse: " << std::quoted(program) << '.';
  }
}

TEST(TestPrattParser, AdvancedExpressions)
{
  using diagnostic::SyntaxError;

  PrattExprs exprs = {
    "num1"sv,
    "fun1()"sv,
    "num1 + num2"sv,
    "fun1() + num2"sv,
    "num1 + fun1() + num3"sv,
    "num1 + fun1()"sv,
    "fun1() + fun2()"sv,
  };

  for(auto&& program : exprs) {
    const auto parser{prep_pratt_parser(program)};

    try {
      auto node{parser->expr()};

      EXPECT_TRUE(node != nullptr) << report_parse_failure(program);
    } catch(SyntaxError& err) {
      FAIL() << report_exception(program, err);
    } catch(std::exception& err) {
      FAIL() << report_exception(program, err);
    } catch(...) {
      FAIL() << report_uncaught_exception(program);
    }
  }
}

TEST(TestPrattParser, BasicChainExpressions)
{
  using diagnostic::SyntaxError;

  PrattExprs exprs = {
    "num1"sv,
    "func1()"sv,
    "func1().func2()"sv,
    "name1.member1"sv,
    "name1.func1()"sv,
    "name1.member1.func1()"sv,
    "name1.func1().func2()"sv,
    "name1.member2.member3"sv,
  };

  for(auto&& program : exprs) {
    const auto parser{prep_pratt_parser(program)};

    try {
      auto node{parser->chain_expr()};

      EXPECT_TRUE(node != nullptr) << report_parse_failure(program);
    } catch(SyntaxError& err) {
      FAIL() << report_exception(program, err);
    } catch(std::exception& err) {
      FAIL() << report_exception(program, err);
    } catch(...) {
      FAIL() << report_uncaught_exception(program);
    }
  }
}

TEST(TestPrattParser, BasicInvalidExpressions)
{
  using diagnostic::SyntaxError;

  PrattExprs exprs = {
    ""sv, "2 + "sv, "2 + * 2"sv, "( 2 + * 2"sv, "( num1 + num2"sv,
  };

  for(auto&& program : exprs) {
    const auto parser{prep_pratt_parser(program)};

    try {
      auto node{parser->expr()};

      EXPECT_TRUE(node == nullptr) << report_parse_failure(program);
    } catch([[maybe_unused]]
            SyntaxError& err) {
      // Ignore and continue, we expect failure to parse.
    } catch(std::exception& err) {
      FAIL() << report_exception(program, err);
    } catch(...) {
      FAIL() << report_uncaught_exception(program);
    }
  }
}
