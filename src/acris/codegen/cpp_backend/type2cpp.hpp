#ifndef ACRIS_ACRIS_CODEGEN_CPP_BACKEND_TYPE2CPP_HPP
#define ACRIS_ACRIS_CODEGEN_CPP_BACKEND_TYPE2CPP_HPP

// STL Includes:
#include <string_view>

// Absolute Includes:
#include "acris/ast/node/fdecl.hpp"
#include "acris/types/core/core.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using types::core::TypeVariant;
/*!
 * Convert the @ref TypeVariant to an actual C++ type.
 */
auto type_variant2cpp(const TypeVariant& t_variant) -> std::string;
} // namespace codegen::cpp_backend

#endif // ACRIS_ACRIS_CODEGEN_CPP_BACKEND_TYPE2CPP_HPP
