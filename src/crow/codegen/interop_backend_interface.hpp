#ifndef CROW_CROW_CODEGEN_INTEROP_BACKEND_INTERFACE_HPP
#define CROW_CROW_CODEGEN_INTEROP_BACKEND_INTERFACE_HPP

// STL Includes:
#include <memory>
#include <string>
#include <vector>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "lib/types.hpp"

namespace codegen {
// Using Statements:
using namespace ast;

// Using Declarations:
using node::NodePtr;

// Forward Declarations:
class InteropBackendInterface;
enum class InteropBackendType;

// Aliases:
using InteropSelectionVec = std::vector<InteropBackendType>;
using InteropBackendPtr = std::shared_ptr<InteropBackendInterface>;

// Enums:
/*!
 * Keeps track of which interop backends exist.
 * Not all interop backends enums need to be supported.
 * By every codegeneration backend.
 */
enum class InteropBackendType {
  C_INTEROP_BACKEND,
  PYTHON_INTEROP_BACKEND,
  LUA_INTEROP_BACKEND,
  JS_INTEROP_BACKEND,
};

// Classes:
/*!
 * Interface used for creating interop between different programming languages.
 */
class InteropBackendInterface {
  public:
  InteropBackendInterface() = default;

  virtual auto prologue() -> std::string = 0;

  virtual auto epilogue() -> std::string = 0;

  virtual ~InteropBackendInterface() = default;
};

auto interopbackendtype2str(InteropBackendType t_type) -> std::string_view;
} // namespace codegen

// Functions:
auto operator<<(std::ostream& t_os, codegen::InteropBackendType t_type)
  -> std::ostream&;

#endif // CROW_CROW_CODEGEN_INTEROP_BACKEND_INTERFACE_HPP
