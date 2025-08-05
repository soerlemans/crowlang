#ifndef CROW_LIB_IS_ANY_OF_HPP
#define CROW_LIB_IS_ANY_OF_HPP

// STL Includes:
#include <type_traits>

namespace lib {
// Concepts:
template<typename Type, typename... Args>
concept IsAnyOf = (std::same_as<Args, Type> || ...);
} // namespace lib

#endif // CROW_LIB_IS_ANY_OF_HPP
