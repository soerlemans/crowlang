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
 * Interface used for
 */
class InteropBackendInterface {
  public:
  InteropBackendInterface() = default;

  virtual auto prologue() -> std::string = 0;
  virtual auto epilogue() -> std::string = 0;

  virtual ~InteropBackendInterface() = default;
};

} // namespace codegen::cpp_backend::interop_backends

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_BACKENDS_INTEROP_BACKEND_INTERFACE_HPP
