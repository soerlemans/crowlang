#ifndef NATIVE_TYPES_HPP
#define NATIVE_TYPES_HPP

// STL Includes:
#include <map>


namespace typing {
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

// TODO: Create mappin
} // namespace typing

#endif // NATIVE_TYPES_HPP
