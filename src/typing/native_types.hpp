#ifndef CROW_TYPING_NATIVE_TYPES_HPP
#define CROW_TYPING_NATIVE_TYPES_HPP

// STL Includes:
#include <algorithm>
#include <cctype>
#include <map>
#include <string_view>

// Library Includes:
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/bimap.hpp>


// Macros:
#define TYPING_NTYPE_PAIR(t_ntype)                          \
  NativeTypeMap::value_type                                 \
  {                                                         \
    boost::algorithm::to_lower_copy(std::string{#t_ntype}), \
      NativeType::t_ntype                                   \
  }

namespace check {
// Forward Declarations:
enum class NativeType;

// Aliases:
using NativeTypeMap = boost::bimap<std::string, NativeType>;

// Enums:
enum class NativeType {
  VOID = 0,

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

  // String:
  STRING,

  // Boolean:
  BOOL,
};

// clang-format off
const NativeTypeMap native_types = boost::assign::list_of<NativeTypeMap::relation>
  (TYPING_NTYPE_PAIR(VOID))

  // Floats:
  (TYPING_NTYPE_PAIR(F32))
	(TYPING_NTYPE_PAIR(F64))

  // Integers:
  (TYPING_NTYPE_PAIR(INT))
  (TYPING_NTYPE_PAIR(I8))
  (TYPING_NTYPE_PAIR(I16))
  (TYPING_NTYPE_PAIR(I32))
  (TYPING_NTYPE_PAIR(I64))
  (TYPING_NTYPE_PAIR(I128))

  (TYPING_NTYPE_PAIR(UINT))
  (TYPING_NTYPE_PAIR(U8))
  (TYPING_NTYPE_PAIR(U16))
  (TYPING_NTYPE_PAIR(U32))
  (TYPING_NTYPE_PAIR(U64))
  (TYPING_NTYPE_PAIR(U128))

	// String:
  (TYPING_NTYPE_PAIR(STRING))

  // // Boolean:
  (TYPING_NTYPE_PAIR(BOOL))
  ;
// clang-format on

// Functions:
auto is_integer(NativeType t_native_type) -> bool;
auto is_float(NativeType t_native_type) -> bool;
auto is_bool(NativeType t_native_type) -> bool;

auto is_condition(NativeType t_native_type) -> bool;
auto is_numeric(NativeType t_native_type) -> bool;

auto str2nativetype(std::string_view t_str) -> NativeType;
auto nativetype2str(NativeType t_native_type) -> std::string;
} // namespace check

auto operator<<(std::ostream& t_os, check::NativeType t_native_type) -> std::ostream&;

#endif // CROW_TYPING_NATIVE_TYPES_HPP
