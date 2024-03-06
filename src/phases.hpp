#ifndef CROW_PHASES_HPP
#define CROW_PHASES_HPP

// Includes:
#include "ast/node/fdecl.hpp"
#include "ast/node/include.hpp"
#include "ast/visitor/ast_printer.hpp"
#include "check/type_checker.hpp"
#include "codegen/llvm_backend/llvm_backend.hpp"
#include "container/text_buffer.hpp"
#include "debug/log.hpp"
#include "lexer/lexer.hpp"
#include "parser/crow/crow_parser.hpp"
#include "token/token.hpp"

// Local Includes:
#include "cli.hpp"


// Functions:
auto open_file(const fs::path t_path) -> container::TextBuffer
{
  using container::TextBuffer;

  if(!fs::exists(t_path)) {
    std::stringstream ss;
    ss << "File does not exist! ";
    ss << std::quoted(t_path.string());

    throw std::invalid_argument{ss.str()};
  }

  TextBuffer tb{t_path.string()};

  std::ifstream ifs{t_path};
  while(ifs.good() && !ifs.eof()) {
    std::string line;
    std::getline(ifs, line);

    tb.add_line(std::move(line));
  }

  return tb;
}

auto lex(const fs::path& t_path) -> token::TokenStream
{
  using container::TextBuffer;
  using lexer::Lexer;

  DBG_PRINTLN("|> Lexing:");

  auto ts_ptr{std::make_shared<TextBuffer>(open_file(t_path))};
  Lexer lexer{ts_ptr};
  const auto tokenstream{lexer.tokenize()};

  DBG_PRINTLN("$");

  return tokenstream;
}

auto print_ast([[maybe_unused]] ast::node::NodePtr t_ast) -> void
{
  using ast::visitor::AstPrinter;

#ifdef DEBUG

  // Pretty print the AST
  DBG_PRINTLN("|> Pretty printing AST:");
  std::stringstream ss;
  ss << "\nAST:\n";

  AstPrinter printer{ss};
  printer.print(t_ast);

  DBG_INFO(ss.str());

  DBG_PRINTLN("$");
#endif // DEBUG
}

auto parse(const token::TokenStream& t_ts) -> ast::node::NodePtr
{
  using parser::crow::CrowParser;

  DBG_PRINTLN("|> Parsing:");

  CrowParser parser{t_ts};
  const auto ast{parser.parse()};

  DBG_PRINTLN("$");

  return ast;
}

auto check_types(ast::node::NodePtr t_ast) -> void
{
  using check::TypeChecker;

  DBG_PRINTLN("|> Type checking:");

  TypeChecker type_checker;
  type_checker.check(t_ast);

  DBG_PRINTLN("$");
}

auto backend(ast::node::NodePtr t_ast) -> void
{
  using codegen::llvm_backend::LlvmBackend;

  DBG_PRINTLN("|> Code generation:");

  LlvmBackend backend;
  backend.codegen(t_ast);
  // backend.compile("main.out");

#ifdef DEBUG
  std::stringstream ss;
  ss << "\nLLVM IR:\n";

  backend.dump_ir(ss);

  DBG_INFO(ss.str());
#endif // DEBUG

  DBG_PRINTLN("$");
}

//! Crow compilers regular compilation flow.
auto run() -> void
{
  for(const auto& path : settings.m_paths) {
    const auto ts{lex(path)};
    const auto ast{parse(ts)};

    print_ast(ast);

    check_types(ast);
    print_ast(ast);

    backend(ast);
  }
}

#endif // CROW_PHASES_HPP
