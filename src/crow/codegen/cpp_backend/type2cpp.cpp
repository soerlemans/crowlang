#include "type2cpp.hpp"

// STL Includes:
#include <memory>

// Absolute Includes:
#include "crow/ast/node/include_nodes.hpp"
#include "lib/overload.hpp"
#include "lib/stdexcept/stdexcept.hpp"

// Macros:
#define MATCH(t_key, t_value) \
  case NativeType::t_key:     \
    str = t_value;            \
    break

namespace {
// Using Declarations:
using types::core::NativeType;
using types::core::nativetype2str;

// Functions:
/*!
 * @warning Make sure that <cstdint> is included for the fixed width integers.
 */
auto native_type2cpp(const NativeType t_type) -> std::string_view
{
  using lib::stdexcept::throw_invalid_argument;

  std::string_view str{};

  // FIXME: Currently the C++ fixed width floating point types.
  // Are not yet supported by clang libc++.
  // So for now just error out, on these.
  // Possibly print currently unsupported?
  switch(t_type) {
    MATCH(VOID, "void");

    MATCH(INT, "int");
    MATCH(I8, "std::int8_t");
    MATCH(I16, "std::int16_t");
    MATCH(I32, "std::int32_t");
    MATCH(I64, "std::int64_t");
    MATCH(ISIZE, "std::intptr_t");

    MATCH(UINT, "unsigned int");
    MATCH(U8, "std::uint8_t");
    MATCH(U16, "std::uint16_t");
    MATCH(U32, "std::uint32_t");
    MATCH(U64, "std::uint64_t");
    MATCH(USIZE, "std::uintptr_t");

    // TODO: Add string literals.

    MATCH(BOOL, "bool");

    default: {
      const auto msg{
        std::format("NativeType could not be converted to C++ type: ",
                    nativetype2str(t_type))};

      throw_invalid_argument(msg);
      break;
    }
  }

  return str;
}

/*!
 * FIXME: Implement type resolution to C++ types for user defined types.
 * This could be a function pointers or structs.
 *
 * @note @ref FnType when resolved will probably need to return its return type.
 * Resolving parameter types
 */
template<typename T>
auto user_type2cpp(const std::shared_ptr<T>& t_data) -> std::string_view
{
  return {};
}
} // namespace

namespace codegen::cpp_backend {
// Using Statements:
NODE_USING_ALL_NAMESPACES()

auto type_variant2cpp(const TypeVariant& t_variant) -> std::string_view
{
  using lib::Overload;

  std::string_view str{};

  if(const auto opt{t_variant.native_type()}; opt) {
    str = native_type2cpp(opt.value());
  }

  return str;

  // FIXME: Get the overloads to work.
  // I am getting some strange template error fix this later.

  // return std::visit(Overload{native_type2cpp_type, user_type2cpp_type},
  //                   symbol_data);
}
} // namespace codegen::cpp_backend
