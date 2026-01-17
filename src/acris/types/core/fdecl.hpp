#ifndef ACRIS_ACRIS_TYPES_CORE_FDECL_HPP
#define ACRIS_ACRIS_TYPES_CORE_FDECL_HPP

// STL Includes:
#include <list>
#include <memory>
#include <optional>

namespace types::core {
// Forward Declarations:
enum class NativeType;

struct StructType;
struct FnType;
struct PointerType;
struct VarType;

class TypeVariant;

// Aliases:
using StructTypePtr = std::shared_ptr<StructType>;
using FnTypePtr = std ::shared_ptr<FnType>;
using PointerTypePtr = std::shared_ptr<PointerType>;
using VarTypePtr = std::shared_ptr<VarType>;

using NativeTypeOpt = std::optional<NativeType>;

using TypeList = std::list<TypeVariant>;
} // namespace types::core

#endif // ACRIS_ACRIS_TYPES_CORE_FDECL_HPP
