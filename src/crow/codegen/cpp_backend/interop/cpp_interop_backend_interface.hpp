#ifndef CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_CPP_INTEROP_BACKEND_INTERFACE_HPP
#define CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_CPP_INTEROP_BACKEND_INTERFACE_HPP

// STL Includes:
#include <memory>
#include <string>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"
#include "crow/codegen/interop_backend_interface.hpp"
#include "lib/types.hpp"

namespace codegen::cpp_backend::interop {
// Forward Declarations:
class CppInteropBackendInterface;

// Aliases:
using namespace ast;

using node::NodePtr;

using CppInteropBackendPtr = std::shared_ptr<CppInteropBackendInterface>;

// Classes:
/*!
 * Interface used for creating interop between
 */
class CppInteropBackendInterface : public InteropBackendInterface {
  public:
  CppInteropBackendInterface() = default;

  virtual auto prologue() -> std::string = 0;

  // TODO: Need to consider the registration interface more in the future.
  // As one day we might want to have the LLVM backend also have interop.
  // And this should then be generic enough.
  // But for now the source based interop can just use the name.
  virtual auto register_constant(std::string_view t_id) -> void = 0;
  virtual auto register_variable(std::string_view t_id) -> void = 0;
  virtual auto register_function(std::string_view t_id) -> void = 0;

  virtual auto epilogue() -> std::string = 0;

  virtual ~CppInteropBackendInterface() = default;
};
} // namespace codegen::cpp_backend::interop

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_INTEROP_CPP_INTEROP_BACKEND_INTERFACE_HPP
