#ifndef NATIVE_TYPES_HPP
#define NATIVE_TYPES_HPP

// STL Includes:
#include <algorithm>
#include <cctype>
#include <map>
#include <string_view>


// Macros:
#define TYPING_NTYPE_PAIR(t_ntype)         \
  NTypeP                                   \
  {                                        \
    tolower(#t_ntype), NativeType::t_ntype \
  }

namespace typing {
// TODO: Move
auto tolower(std::string t_str) -> std::string
{
  std::transform(t_str.begin(), t_str.end(), t_str.begin(),
                 [](unsigned char t_ch) {
                   return std::tolower(t_ch);
                 });
  return t_str;
}

// Forward Declarations:
enum class NativeType;

// Aliases:
using NTypeP = std::pair<std::string, NativeType>;

// Enums:
enum class NativeType {
  // Floats:
  F32,
  F64,

  // Integers:
  INT,
  I8,
  I16,
  I32,
  I64,
  I128,

  UINT,
  U8,
  U16,
  U32,
  U64,
  U128,

  // Boolean:
  BOOL
};

const std::map<std::string, NativeType> type_map{
  // Floats:
  TYPING_NTYPE_PAIR(F32), TYPING_NTYPE_PAIR(F64),

  // Integers:
  TYPING_NTYPE_PAIR(INT), TYPING_NTYPE_PAIR(I8), TYPING_NTYPE_PAIR(I16),
  TYPING_NTYPE_PAIR(I32), TYPING_NTYPE_PAIR(I64), TYPING_NTYPE_PAIR(I128),

  TYPING_NTYPE_PAIR(UINT), TYPING_NTYPE_PAIR(U8), TYPING_NTYPE_PAIR(U16),
  TYPING_NTYPE_PAIR(U32), TYPING_NTYPE_PAIR(U64), TYPING_NTYPE_PAIR(U128),

  // Boolean:
  TYPING_NTYPE_PAIR(BOOL)};

// TODO: Create mappin
} // namespace typing

#endif // NATIVE_TYPES_HPP
