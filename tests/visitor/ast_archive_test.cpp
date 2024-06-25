// STL Includes:
#include <iostream>
#include <sstream>

// Library Includes:
#include <catch2/catch_test_macros.hpp>

// Crow Absolute Includes:
#include "crow/ast/visitor/ast_archive.hpp"
#include "crow/phases.hpp"

// Test Cases:
TEST_CASE("AstArchive", "[visitor]")
{
  using ast::node::NodePtr;
  using ast::visitor::ArchiveType;
  using ast::visitor::AstArchive;
  using ast::visitor::AstPrinter;
  using container::TextBuffer;
  using lexer::Lexer;

  // Create a simple crow program:
  auto stream_ptr{std::make_shared<TextBuffer>()};
  stream_ptr->add_line("fn main() -> int { return 0; }");

  // Create an AST:
  Lexer lexer{stream_ptr};
  const auto tokenstream{lexer.tokenize()};
  NodePtr ast{parse(tokenstream)};
  NodePtr ast_new{};

  // Create a stream too save too:
  std::stringstream ss("data.xml");
  AstArchive archive{ArchiveType::JSON};

  SECTION("Serialize")
  {
    archive.out(ast, ss);
  }

  std::cout << "Ast serialized:\n" << ss.str();

  SECTION("Deserialize")
  {
    archive.in(ast_new, ss);
  }

  REQUIRE(false);
}
