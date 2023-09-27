#ifndef CROW_CONTAINER_TEXT_POSITION_HPP
#define CROW_CONTAINER_TEXT_POSITION_HPP

// STL Includes:
#include <string>
#include <string_view>


namespace container {
struct TextPosition {
  // Members:
  std::string m_source;
  std::string m_line;

  std::size_t m_lineno;
  std::size_t m_columno;

  // Methods:
  TextPosition();
  TextPosition(std::string_view t_source, std::string_view t_line,
               std::size_t t_lineno, std::size_t t_columnno);

  friend auto operator<<(std::ostream& t_os, const TextPosition& t_fp)
    -> std::ostream&;

  virtual ~TextPosition() = default;
};
} // namespace container

#endif // CROW_CONTAINER_TEXT_POSITION_HPP
