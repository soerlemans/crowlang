// STL Includes:
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// Library Includes:
#include <gtest/gtest.h>

// Absolute Includes:
#include "acris/ast/node/include.hpp"
#include "acris/container/text_buffer.hpp"
#include "acris/diagnostic/diagnostic.hpp"
#include "acris/lexer/lexer.hpp"
#include "acris/parser/acris/acris_parser.hpp"
#include "lib/stdexcept/stdexcept.hpp"

/*!
 * @file
 *
 */


// Using:
using namespace std::literals::string_view_literals;

using parser::acris::AcrisParser;
using parser::pratt::PrattParser;

using PrattExprs = std::vector<std::string_view>;

// Helper functions:
namespace {
auto prep_parser(const std::string_view t_program) -> AcrisParser
{
  using container::TextBuffer;
  using lexer::Lexer;
  using parser::acris::AcrisParser;
  using token::TokenStream;

  // Write program.
  auto stream_ptr{std::make_shared<TextBuffer>()};
  stream_ptr->add_line(std::string{t_program});

  // Create AST from TextBuffer.
  Lexer lexer{stream_ptr};
  AcrisParser parser{lexer.tokenize()};

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
  using diagnostic::SyntaxError;

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
    "(2 * -num1 - 3) + +num2 / -num3"sv,
  };

  for(auto&& program : exprs) {
    auto parser{prep_parser(program)};

    try {
      auto node{parser.pratt_parse([](PrattParser& pratt) {
        return pratt.expr();
      })};

      EXPECT_TRUE(node != nullptr)
        << "Expression failed to parse: " << std::quoted(program) << '.';
    } catch(SyntaxError& err) {
      FAIL() << report_exception(program, err);
    } catch(std::exception& err) {
      FAIL() << report_exception(program, err);
    } catch(...) {
      FAIL() << report_uncaught_exception(program);
    }
  }
}

TEST(TestPrattParser, AdvancedExpressions)
{
  using diagnostic::SyntaxError;

  PrattExprs exprs = {
    "num1"sv,
    "fun1()"sv,
    "fun1(1, 2, 3)"sv,
    "num1 + num2"sv,
    "fun1() + num2"sv,
    "fun1(1, num, \"apple\") + num2"sv,
    "num1 + fun1() + num3"sv,
    "num1 + fun1(\"banana\", 2, 3) + num3"sv,
    "num1 + fun1()"sv,
    "num1 + fun1(100)"sv,
    "fun1() + fun2(22)"sv,
    "fun1(func2(fun3(0)))"sv,
    "fun1(+func2(-fun3(0)))"sv,
  };

  for(auto&& program : exprs) {
    auto parser{prep_parser(program)};

    try {
      auto node{parser.pratt_parse([](PrattParser& pratt) {
        return pratt.expr();
      })};

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
    "func1(12).func2(21)"sv,
    "name1.member1"sv,
    "name1.func1()"sv,
    "name1.member1.func1()"sv,
    "name1.func1().func2()"sv,
    "name1.member2.member3"sv,
  };

  for(auto&& program : exprs) {
    auto parser{prep_parser(program)};

    try {
      auto node{parser.pratt_parse([](PrattParser& pratt) {
        return pratt.chain_expr();
      })};

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

TEST(TestPrattParser, AdvancedChainExpressions)
{
  using diagnostic::SyntaxError;

  PrattExprs exprs = {
    "name1.fun1(name2.fun2()).func3()"sv,
    "name1.fun1(name2.fun2(0)).func3(3 + 2, 3)"sv,
    "name1.fun1(name2.fun2(0)).func3(3 + 2, 3, num3 + 32)"sv,
    "name1.fun1(name2.fun2(0)).func3(3 + 2, 3, num3 * 32)"sv,
  };

  for(auto&& program : exprs) {
    auto parser{prep_parser(program)};

    try {
      auto node{parser.pratt_parse([](PrattParser& pratt) {
        return pratt.chain_expr();
      })};

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

  // FIXME: Currently failing: "( 2 + * 2"sv, (Find out why later).
  // Also:  "2 + * 2"sv,

  PrattExprs exprs = {""sv, "2 + "sv, "( num1 + num2"sv, "func("sv, "(fun"sv};

  // FIXME: "fun)" is parsed as IDENTIFIER and then).
  // This might only be like this in testing.

  for(auto&& program : exprs) {
    auto parser{prep_parser(program)};

    try {
      auto node{parser.pratt_parse([](PrattParser& pratt) {
        return pratt.expr();
      })};

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
