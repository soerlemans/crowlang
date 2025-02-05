#ifndef CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_INTEROP_BACKEND_INTERFACE_HPP
#define CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_INTEROP_BACKEND_INTERFACE_HPP

// STL Includes:
#include <memory>
#include <string>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "lib/types.hpp"

namespace codegen::cpp_backend::interop_backends {
// Using Statements:
using namespace ast;

// Using Declarations:
using node::NodePtr;

// Forward Declarations:
class InteropBackendInterface;

// Aliases:
using InteropBackendPtr = std::shared_ptr<InteropBackendInterface>;

/*!
 * Interface used for creating interop between
 */
class InteropBackendInterface {
  public:
  InteropBackendInterface() = default;

  virtual auto prologue() -> std::string = 0;
  virtual auto epilogue() -> std::string = 0;

  // TODO: Need to consider how a type should be registered.
  // We probably should use some kind of combination of either std::any.
  // Or some kind of enum telling how a function should be registered.
  virtual auto register_function(std::string_view t_id) -> void = 0;
  virtual auto register_variable(std::string_view t_id) -> void = 0;

  virtual ~InteropBackendInterface() = default;
};

} // namespace codegen::cpp_backend::interop_backends

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_INTEROP_BACKEND_INTERFACE_HPP
