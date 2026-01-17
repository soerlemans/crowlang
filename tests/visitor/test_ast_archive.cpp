// STL Includes:
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// Library Includes:
#include <gtest/gtest.h>

// Acris Absolute Includes:
#include "acris/ast/node/include.hpp"
#include "acris/ast/visitor/ast_archive.hpp"
#include "acris/ast/visitor/ast_printer.hpp"
#include "acris/container/text_buffer.hpp"
#include "acris/lexer/lexer.hpp"
#include "acris/parser/acris/acris_parser.hpp"

/*!
 * @file
 *
 * For the archiving of the AST we likely will not use assertions.
 * Currently we do not have a tool for comparing if two AST's are equal.
 * So as of writing we can not check this.
 * For now using ast printer is good enough.
 * We could use the output of the AST printer and compare it but that is ugly.
 */


// Using namespace Declarations:
using namespace std::literals::string_view_literals;

// Helper functions:
namespace {
using ast::visitor::ArchiveType;
using ast::visitor::AstArchive;
using ast::visitor::AstPrinter;

AstArchive archive{ArchiveType::JSON};
AstPrinter printer{std::cout};

auto test_archive(const std::string_view t_program) -> void
{
  using ast::node::NodePtr;
  using container::TextBuffer;
  using lexer::Lexer;
  using parser::acris::AcrisParser;
  using token::TokenStream;

  std::stringstream ss;

  // Write program.
  auto stream_ptr{std::make_shared<TextBuffer>()};
  stream_ptr->add_line(std::string{t_program});

  // Create AST from TextBuffer.
  Lexer lexer{stream_ptr};
  TokenStream tokenstream{lexer.tokenize()};
  AcrisParser parser{tokenstream};

  NodePtr ast{parser.parse()};
  NodePtr ast_new{};

  // Test archiving.
  std::cout << "AST.\n";
  printer.print(ast);

  std::cout << "Serialize AST.\n";
  archive.out(ast, ss);

  std::cout << "Ast serialized:\n" << ss.str() << '\n';

  std::cout << "Deserialize AST.\n";
  archive.in(ast_new, ss);

  std::cout << "New AST.\n";
  printer.print(ast_new);
}
} // namespace

// Test Cases:
TEST(TestAstArchive, Basic)
{
  GTEST_SKIP();

  using ast::node::NodePtr;
  using ast::node::rvalue::Integer;

  // Printer.
  AstPrinter printer{std::cout};

  NodePtr ast{std::make_shared<Integer>(10)};
  NodePtr ast_new{};

  // FIXME: Moving from catch2 to Google test.
  // SECTION("Basic main")
  // {
  //   const auto program{"fn main() -> int { return 0; }"sv};
  //   test_archive(program);
  // }

  // SECTION("Basic arithmetic")
  // {
  //   const auto program{"fn main() -> int { return 10 + 10; }"sv};
  //   test_archive(program);
  // }

  printer.print(ast_new);
}
