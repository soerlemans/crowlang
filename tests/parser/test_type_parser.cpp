// STL Includes:
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

// Test Includes:
#include "test_util.hpp"

/*!
 * @file
 *
 */


// Using:
using namespace std::literals::string_view_literals;

using parser::acris::AcrisParser;
using parser::acris::TypeParser;
using parser::pratt::PrattParser;

using TypeExprs = std::vector<std::string_view>;

// Test Cases:
TEST(TestPrattParser, BasicExpressions)
{
  using diagnostic::SyntaxError;

  TypeExprs exprs = {
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
