// STL Includes:
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// Library Includes:
#include <catch2/catch_test_macros.hpp>

// Crow Absolute Includes:
#include "crow/ast/node/include.hpp"
#include "crow/ast/visitor/ast_archive.hpp"
#include "crow/ast/visitor/ast_printer.hpp"
#include "crow/container/text_buffer.hpp"
#include "crow/lexer/lexer.hpp"
#include "crow/parser/crow/crow_parser.hpp"

/*!
 * @file
 *
 */


// Using namespace Declarations:
using namespace std::literals::string_view_literals;

// Helper functions:
namespace {
auto test_pratt_parser(const std::string_view t_program) -> void
{
  using ast::node::NodePtr;
  using container::TextBuffer;
  using lexer::Lexer;
  using parser::crow::CrowParser;
  using token::TokenStream;

  std::stringstream ss;

  // Write program.
  auto stream_ptr{std::make_shared<TextBuffer>()};
  stream_ptr->add_line(std::string{t_program});

  // Create AST from TextBuffer.
  Lexer lexer{stream_ptr};
  TokenStream tokenstream{lexer.tokenize()};
  CrowParser parser{tokenstream};

  NodePtr ast{parser.parse()};
  NodePtr ast_new{};
}
} // namespace

// Test Cases:
TEST_CASE("PrattParser_basic", "[.]")
{
  using ast::node::NodePtr;
  using ast::node::rvalue::Integer;

  // Printer.
  SECTION("Basic main")
  {
    const auto program{"fn main() -> int { return 0; }"sv};
    test_pratt_parser(program);
  }

  SECTION("Basic arithmetic")
  {
    const auto program{"fn main() -> int { return 10 + 10; }"sv};
    test_pratt_parser(program);
  }
}
