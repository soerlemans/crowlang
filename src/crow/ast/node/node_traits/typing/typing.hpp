#ifndef CROW_CROW_AST_NODE_NODE_TRAITS_TYPING_TYPING_HPP
#define CROW_CROW_AST_NODE_NODE_TRAITS_TYPING_TYPING_HPP

/*!
 * @file
 *
 * Contains aliases that are required for representing the type structure.
 */

// STL Includes:
#include <iosfwd>
#include <list>
#include <memory>
#include <optional>

// Local Includes:
#include "fdecl.hpp"

namespace ast::node::node_traits::typing {
// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using VarTypePtr = std::shared_ptr<VarType>;

using TypeList = std::list<TypeVariant>;
} // namespace ast::node::node_traits::typing

// TODO: Find a cleaner way to have operators always be accessible.
auto operator<<(std::ostream& t_os,
                ast::node::node_traits::typing::StructTypePtr t_struct)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                ast::node::node_traits::typing::FnTypePtr t_fn)
  -> std::ostream&;
auto operator<<(std::ostream& t_os,
                ast::node::node_traits::typing::VarTypePtr t_var)
  -> std::ostream&;

auto operator<<(std::ostream& t_os,
                const ast::node::node_traits::typing::TypeList& t_list)
  -> std::ostream&;

#endif // CROW_CROW_AST_NODE_NODE_TRAITS_TYPING_TYPING_HPP
