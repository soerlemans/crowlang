#ifndef CROW_CROW_CODEGEN_CPP_BACKEND_TYPE_DATA2CPP_TYPE_HPP
#define CROW_CROW_CODEGEN_CPP_BACKEND_TYPE_DATA2CPP_TYPE_HPP

// STL Includes:
#include <string_view>

// Absolute Includes:
#include "crow/ast/node/fdecl.hpp"

namespace codegen::cpp_backend {
// Using Statements:
using ast::node::node_traits::typing::TypeVariant;
/*!
 * Convert the @ref TypeVariant to an actual C++ type.
 */
auto type_data2cpp_type(const TypeVariant& t_variant) -> std::string_view;
} // namespace codegen::cpp_backend

#endif // CROW_CROW_CODEGEN_CPP_BACKEND_TYPE_DATA2CPP_TYPE_HPP
