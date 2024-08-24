#ifndef CROW_CROW_PHASES_HPP
#define CROW_CROW_PHASES_HPP

// Absolute Includes:
#include "ast/node/fdecl.hpp"
#include "ast/visitor/ast_printer.hpp"
#include "check/type_checker.hpp"
#include "codegen/cpp_backend/cpp_backend.hpp"
#include "codegen/llvm_backend/llvm_backend.hpp"
#include "container/text_buffer.hpp"
#include "lexer/lexer.hpp"
#include "parser/crow/crow_parser.hpp"

// FIXME: log has to be included as last in order to see all operator<<().
// Add a rule for this in the .clang-format file.
#include "debug/log.hpp"

// Local Includes:
#include "cli.hpp"

// Functions:
//! Open a file and store its contents in a @ref TextBuffer.
auto open_file(const std::filesystem::path t_path) -> container::TextBuffer;

//! Tokenize the text buffer.
auto lex(const std::filesystem::path& t_path) -> token::TokenStream;
auto lex(const container::TextStreamPtr& t_stream) -> token::TokenStream;

//! Parse  the tokenized stream.
auto parse(const token::TokenStream& t_ts) -> ast::node::NodePtr;

//! Print the AST, only available if @ref DEBUG is defined.
auto print_ast(ast::node::NodePtr t_ast) -> void;

//! Type check the AST.
auto check_types(ast::node::NodePtr t_ast) -> void;

//! Execute the codegeneration backend.
auto backend(ast::node::NodePtr t_ast) -> void;

//! Crow compiler regular compilation flow.
auto run() -> void;

#endif // CROW_CROW_PHASES_HPP
