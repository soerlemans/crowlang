#ifndef NATIVE_TYPES_HPP
#define NATIVE_TYPES_HPP

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
#define TYPING_NTYPE_PAIR(t_ntype) \
  boost::algorithm::to_lower_copy(std::string{#t_ntype}), NativeType::t_ntype

namespace typing {
// Forward Declarations:
enum class NativeType;

// Aliases:
using NTypeM = boost::bimap<std::string, NativeType>;
using NTypeP = NTypeM::value_type;

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

// clang-format off
const NTypeM type_map = boost::assign::list_of<NTypeM::relation>
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

  // // Boolean:
  (TYPING_NTYPE_PAIR(BOOL))
  ;
// clang-format on

// Functions:
auto nativetype2str(NativeType t_ntype) -> std::string;
} // namespace typing

#endif // NATIVE_TYPES_HPP
