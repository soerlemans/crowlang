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

using AcrisExprs = std::vector<std::string_view>;

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
TEST(TestAcrisParser, BasicExpressions)
{
}

TEST(TestAcrisParser, AdvancedExpressions)
{
}

TEST(TestAcrisParser, BasicChainExpressions)
{
}

TEST(TestAcrisParser, AdvancedChainExpressions)
{
}

TEST(TestAcrisParser, BasicInvalidExpressions)
{
}
