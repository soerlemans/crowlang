// Library Includes:
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

// Crow Includes:
#include "lexer/lexer.hpp"
#include "phases.hpp"


// Test Cases:
TEST_CASE("Lexer", "[lexer]")
{
  using container::TextBuffer;
  using lexer::Lexer;

  // Create a simple crow program:
  auto stream_ptr{std::make_shared<TextBuffer>()};
  stream_ptr->add_line("fn main() -> int { return 0; }");

  // Tokenize the stream:
  Lexer lexer{stream_ptr};
  const auto tokenstream{lexer.tokenize()};

  SECTION("Tokenizing")
  {
    Lexer lexer{stream_ptr};

    const auto tokenstream{lexer.tokenize()};
  }

  BENCHMARK("Tokenizing")
  {
    Lexer lexer{stream_ptr};

    return lexer.tokenize();
  };
}
