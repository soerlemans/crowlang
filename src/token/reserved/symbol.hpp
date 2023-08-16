#ifndef NEWLANG_TOKEN_RESERVED_SYMBOL_HPP
#define NEWLANG_TOKEN_RESERVED_SYMBOL_HPP

// STL Includes:
#include <type_traits>


namespace token::reserved {
// Concepts:
template<typename T>
concept StringLike =
  std::is_convertible_v<T, std::string_view> || std::same_as<T, char>;

// Aliases:

template<typename T = std::string_view>
requires StringLike<T>
class Symbol {
  private:
  T m_identifier;
  std::optional<TokenType> m_type;

  public:
  // TODO: Use std::is_convertible<T, std::string_view> to not need to cast to
  // std::string_view explicitly
  constexpr Symbol(const T t_identifier, const TokenType t_type)
    : m_identifier{t_identifier}, m_type{t_type}
  {}

  constexpr Symbol(const char* t_identifier, const TokenType t_type)
    : m_identifier{t_identifier}, m_type{t_type}
  {}

  [[nodiscard]] constexpr auto identifier() const -> T
  {
    return m_identifier;
  }

  [[nodiscard]] constexpr auto tokentype() const -> TokenType
  {
    return m_type;
  }

  [[nodiscard]] constexpr auto get() const -> std::tuple<T, TokenType>
  {
    return {m_identifier, m_type};
  }

  // Warning: The class can be explicitly converted
  [[nodiscard]] explicit constexpr operator TokenType() const
  {
    return m_type;
  }

  virtual ~Symbol() = default;
};
} // namespace token::reserved

#endif // NEWLANG_TOKEN_RESERVED_SYMBOL_HPP
