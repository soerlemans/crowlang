#ifndef CROW_CROW_TYPES_CORE_FDECL_HPP
#define CROW_CROW_TYPES_CORE_FDECL_HPP

// STL Includes:
#include <list>
#include <memory>
#include <optional>

namespace types::core {
// Forward Declarations:
class TypeVariant;

struct StructType;
struct FnType;
struct VarType;

class TypeData;

// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using VarTypePtr = std::shared_ptr<VarType>;

using TypeList = std::list<TypeVariant>;
} // namespace types::core

#endif // CROW_CROW_TYPES_CORE_FDECL_HPP
