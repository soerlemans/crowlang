// STL Includes:
#include <iostream>
#include <sstream>

// Library Includes:
#include <catch2/catch_test_macros.hpp>

// Crow Includes:
#include "ast/visitor/ast_serializer.hpp"
#include "phases.hpp"


// Test Cases:
TEST_CASE("Archive", "[visitor]")
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
  AstSerializer serializer{};

  SECTION("Serialize")
  {
    std::ofstream os("data.xml");
    cereal::XMLOutputArchive archive(os);

    archive(ast);
  }

  std::cout << "SS:\n" << ss.str();

  SECTION("Deserialize")
  {
    std::ifstream is("data.xml");
    cereal::XMLInputArchive archive(is);

    archive(ast_new);
  }
}
