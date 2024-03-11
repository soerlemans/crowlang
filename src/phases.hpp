#ifndef CROW_PHASES_HPP
#define CROW_PHASES_HPP

// Includes:
#include "ast/node/fdecl.hpp"
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
//! Open a file and store its contents in a @ref TextBuffer.
auto open_file(const fs::path t_path) -> container::TextBuffer;

//! Tokenize the text buffer.
auto lex(const fs::path& t_path) -> token::TokenStream;
auto lex(const container::TextStreamPtr& t_stream) -> token::TokenStream;

//! Parse.
auto parse(const token::TokenStream& t_ts) -> ast::node::NodePtr;
auto print_ast([[maybe_unused]] ast::node::NodePtr t_ast) -> void;

//! Type check the AST.
auto check_types(ast::node::NodePtr t_ast) -> void;

//! Execute the codegeneration backend.
auto backend(ast::node::NodePtr t_ast) -> void;

//! Crow compiler regular compilation flow.
auto run() -> void;

#endif // CROW_PHASES_HPP
