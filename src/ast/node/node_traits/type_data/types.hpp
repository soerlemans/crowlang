#ifndef CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPES_HPP
#define CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPES_HPP

/*!
 * @file
 *
 * Contains aliases that are required for representing the type structure.
 */

// STL Includes:
#include <iostream>
#include <list>
#include <memory>
#include <optional>


namespace ast::node::node_traits::type_data {
// Forward Declarations:
class TypeVariant;

struct StructType;
struct FnType;
struct VarType;

// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using VarTypePtr = std::shared_ptr<VarType>;

using TypeList = std::list<TypeVariant>;
} // namespace ast::node::node_traits::type_data

// auto operator<<(std::ostream& t_os, check::StructTypePtr t_struct)
//   -> std::ostream&;
// auto operator<<(std::ostream& t_os, check::FnTypePtr t_fn) -> std::ostream&;
// auto operator<<(std::ostream& t_os, check::VarTypePtr t_var) -> std::ostream&;

// auto operator<<(std::ostream& t_os, const check::TypeList& t_list)
//   -> std::ostream&;

#endif // CROW_AST_NODE_NODE_TRAITS_TYPE_DATA_TYPES_HPP
