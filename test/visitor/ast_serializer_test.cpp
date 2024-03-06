// STL Includes:
#include <iostream>
#include <sstream>

// Library Includes:
#include <catch2/catch_test_macros.hpp>

// Crow Includes:
#include "ast/visitor/ast_serializer.hpp"
#include "phases.hpp"


// Test Cases:
TEST_CASE("Deserialization", "[visitor]")
{
  using ast::node::NodePtr;
  using ast::visitor::AstPrinter;
  using ast::visitor::AstSerializer;
  using container::TextBuffer;
  using lexer::Lexer;

  // Create a simple crow program:
  auto stream_ptr{std::make_shared<TextBuffer>()};

  stream_ptr->add_line("fn main() -> int {");
  stream_ptr->add_line("  return 0");
  stream_ptr->add_line("}");

  // Create an AST:
  Lexer lexer{stream_ptr};
  const auto tokenstream{lexer.tokenize()};
  NodePtr ast{parse(tokenstream)};
  NodePtr ast_new{};

  // Create a stream too save too:
  std::stringstream ss;
  AstPrinter printer{std::cout};
  AstSerializer serializer{};

  std::cout << "Ast:"
            << "\n";
  printer.print(ast);

  SECTION("Serialization")
  {
    serializer.serialize(ast, ss);

    std::cout << "\n"
              << "Ast Serialized:"
              << "\n";
    std::cout << ss.str();
  }

  SECTION("Deserialization")
  {
    serializer.deserialize(ast_new, ss);
    // serializer.deserialize(ast_new, fs);

    std::cout << "Ast Deserialized:"
              << "\n";
    printer.print(ast_new);
  }

  REQUIRE(true);
}
