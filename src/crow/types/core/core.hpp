#ifndef CROW_CROW_TYPES_CORE_CORE_HPP
#define CROW_CROW_TYPES_CORE_CORE_HPP

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
#include "native_types.hpp"

namespace types::core {
// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using VarTypePtr = std::shared_ptr<VarType>;

using TypeList = std::list<TypeVariant>;
} // namespace types::core

// TODO: Find a cleaner way to have operators always be accessible.
auto operator<<(std::ostream& t_os, types::core::StructTypePtr t_struct)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, types::core::FnTypePtr t_fn)
  -> std::ostream&;
auto operator<<(std::ostream& t_os, types::core::VarTypePtr t_var)
  -> std::ostream&;

auto operator<<(std::ostream& t_os, const types::core::TypeList& t_list)
  -> std::ostream&;

#endif // CROW_CROW_TYPES_CORE_CORE_HPP
