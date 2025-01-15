#ifndef BACKEND_INTERFACE_HPP
#define BACKEND_INTERFACE_HPP

// STL Includes:
#include <memory>

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/semantic/symbol_table/symbol_table.hpp"
#include "lib/filesystem.hpp"

namespace codegen {
// Using Statements:
using namespace ast;

// Using Declarations:
using node::NodePtr;
using semantic::symbol_table::SymbolTablePtr;
using std::filesystem::path;

// Forward Declarations:
class BackendInterface;

// Aliases:
using BackendPtr = std::unique_ptr<BackendInterface>;

// Enums:
enum class BackendType {
  LLVM_BACKEND,
  CPP_BACKEND
};

// Structs:
/*!
 * Utility structure packing all AST functionality together,
 * With the @ref SymbolTable.
 */
struct AstPack {
  NodePtr m_ast;
  SymbolTablePtr m_symbol_table;
};

// Classes:
/*!
 * This is an interface for communicating with backends in a generic way.
 */
class BackendInterface : public ast::visitor::NodeVisitor {
  public:
  BackendInterface() = default;

  virtual auto compile(AstPack t_pack, path t_stem) -> void = 0;

  virtual ~BackendInterface() = default;
};

// Functions:
// TODO: Implement with a unique_ptr or something similar.
[[nodiscard("Pure method must use results.")]]
auto select_backend(BackendType t_selector) -> BackendPtr;
} // namespace codegen

#endif // BACKEND_INTERFACE_HPP
