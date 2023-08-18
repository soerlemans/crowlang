#ifndef CROW_TOKEN_RESERVED_TERMINAL_HPP
#define CROW_TOKEN_RESERVED_TERMINAL_HPP

// STL Includes:
#include <type_traits>

// Includes:
#include "../token_type.hpp"


namespace token::reserved {
// Concepts:
template<typename T>
concept StringLike =
  std::is_convertible_v<T, std::string_view> || std::same_as<T, char>;

// Classes:
template<typename T = std::string_view>
requires StringLike<T>
struct Terminal {
  T m_identifier;
  TokenType m_type;

  constexpr Terminal(T t_identifier, TokenType t_type)
    : m_identifier{t_identifier}, m_type{t_type}
  {}

  constexpr Terminal(const char* t_identifier, TokenType t_type)
    : m_identifier{t_identifier}, m_type{t_type}
  {}

  virtual ~Terminal() = default;
};
} // namespace token::reserved

#endif // CROW_TOKEN_RESERVED_TERMINAL_HPP
