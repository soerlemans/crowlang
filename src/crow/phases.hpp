#ifndef CROW_CROW_PHASES_HPP
#define CROW_CROW_PHASES_HPP

// Local Includes:
#include "ast/node/fdecl.hpp"
#include "ast/visitor/ast_printer.hpp"
#include "semantic/semantic_checker.hpp"
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
//! Tokenize the text buffer.
auto lex(const std::filesystem::path& t_path) -> token::TokenStream;
auto lex(const container::TextStreamPtr& t_stream) -> token::TokenStream;

//! Parse  the tokenized stream.
auto parse(const token::TokenStream& t_ts) -> ast::node::NodePtr;

//! Print the AST, only available if @ref DEBUG is defined.
auto print_ast(ast::node::NodePtr t_ast) -> void;

//! Check the semantic validaty of the AST.
auto check_semantics(ast::node::NodePtr t_ast) -> semantic::SemanticPack;

//! Execute the codegeneration backend.
auto backend(const semantic::SemanticPack& t_pack,
             const std::filesystem::path& t_path) -> void;

//! Crow compiler regular compilation flow.
auto run() -> void;

#endif // CROW_CROW_PHASES_HPP
