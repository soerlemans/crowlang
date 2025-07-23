#ifndef CROW_CROW_CODEGEN_BACKEND_INTERFACE_HPP
#define CROW_CROW_CODEGEN_BACKEND_INTERFACE_HPP

// STL Includes:
#include <memory>

// Absolute Includes:
#include "crow/ast/visitor/node_visitor.hpp"
#include "crow/codegen/interop_backend_interface.hpp"
#include "crow/semantic/symbol_table/symbol_table.hpp"
#include "lib/filesystem.hpp"

namespace codegen {
// Using Statements:
using namespace ast;

// Using Declarations:
using node::NodePtr;
using semantic::symbol_table::SymbolTablePtr;

namespace fs = std::filesystem;

// Forward Declarations:
class BackendInterface;

// Aliases:
using BackendPtr = std::shared_ptr<BackendInterface>;

// Enums:
enum class BackendType {
  LLVM_BACKEND,
  JS_BACKEND,
  CPP_BACKEND,
  C_BACKEND,
};

// Structs:
/*!
 * Utility structure packing all required parameters for compiling.
 */
struct CompileParams {
  NodePtr m_ast;
  SymbolTablePtr m_symbol_table;

  fs::path m_build_dir;
  fs::path m_source_path;
};

// Classes:
/*!
 * This is an interface for communicating with backends in a generic way.
 */
class BackendInterface : public ast::visitor::NodeVisitor {
  public:
  BackendInterface() = default;

  /*!
   * How an interop backend is added is backend specific.
   * So this is a shared factory method for nested interop backends.
   */
  virtual auto register_interop_backend(InteropBackendType t_type) -> void = 0;

  //! Compile the AST for the selected backend.
  virtual auto compile(CompileParams& t_params) -> void = 0;

  virtual ~BackendInterface() = default;
};

// Functions:
// TODO: Implement with a unique_ptr or something similar.
[[nodiscard("Pure method must use results.")]]
auto select_backend(BackendType t_selector) -> BackendPtr;

[[nodiscard("Pure method must use results.")]]
auto backendtype2str(BackendType t_type) -> std::string_view;
} // namespace codegen

auto operator<<(std::ostream& t_os, codegen::BackendType t_type)
  -> std::ostream&;


#endif // CROW_CROW_CODEGEN_BACKEND_INTERFACE_HPP
