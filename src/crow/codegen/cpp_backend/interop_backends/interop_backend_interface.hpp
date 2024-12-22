#ifndef BINDING_GENERATOR_INTERFACE_HPP
#define BINDING_GENERATOR_INTERFACE_HPP

// STL Includes:
#include <string>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "lib/types.hpp"

namespace codegen::cpp_backend::interop_backends {
// Using Declarations:
using node::NodePtr;

/*!
 * Interface used for
 */
class InteropBackendInterface {
  public:
  InteropBackendInterface() = default;

  virtual auto prologue() -> std::string = 0;
  virtual auto epilogue() -> std::string = 0;
  virtual auto generate(NodePtr t_ast) -> std::string = 0;

  virtual ~InteropBackendInterface() = default;
};

} // namespace codegen::cpp_backend::interop_backends

#endif // BINDING_GENERATOR_INTERFACE_HPP
