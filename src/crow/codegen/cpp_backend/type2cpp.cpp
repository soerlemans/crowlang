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
using types::core::FnTypePtr;
using types::core::NativeType;
using types::core::nativetype2str;
using types::core::PointerTypePtr;
using types::core::StructTypePtr;
using types::core::VarTypePtr;

// Functions:
/*!
 * @warning Make sure that <cstdint> is included for the fixed width integers.
 */
inline auto native_type2cpp(const NativeType t_type) -> std::string
{
  using lib::stdexcept::throw_invalid_argument;

  std::string str{};

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

    MATCH(STRING, "const char*");

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

inline auto struct2cpp(const StructTypePtr& t_struct) -> std::string
{
  return t_struct->m_identifier;
}

inline auto fn2cpp(const FnTypePtr& t_type) -> std::string
{
  // TODO: Throw?

  return {};
}

inline auto pointer2cpp(const PointerTypePtr& t_ptr) -> std::string
{
  using codegen::cpp_backend::type_variant2cpp;

  auto base_type{type_variant2cpp(t_ptr->m_type)};

  return std::format("{}*", base_type);
}

// Could be used for decltype() or similar.
inline auto var2cpp(const VarTypePtr& t_var) -> std::string
{
  using codegen::cpp_backend::type_variant2cpp;

  auto base_type{type_variant2cpp(t_var->m_type)};

  return std::format("{}", base_type);
}

} // namespace

namespace codegen::cpp_backend {
// Using Statements:
NODE_USING_ALL_NAMESPACES()

auto type_variant2cpp(const TypeVariant& t_variant) -> std::string
{
  using lib::Overload;

  // clang-format off
  return std::visit(
					Overload{
						[](const NativeType t_native) {
							return native_type2cpp(t_native);
						},
						[](const StructTypePtr& t_struct) {
							return struct2cpp(t_struct);
						},
						[](const FnTypePtr& t_fn) {
							return fn2cpp(t_fn);
						},
						[](const PointerTypePtr& t_ptr) {
							return pointer2cpp(t_ptr);
						},
						[](const VarTypePtr& t_var) {
							return var2cpp(t_var);
						}},
					t_variant);
	// clang-format off
}
} // namespace codegen::cpp_backend
