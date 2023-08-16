#ifndef NEWLANG_CONTAINER_TEXT_POSITION_HPP
#define NEWLANG_CONTAINER_TEXT_POSITION_HPP

// STL Includes:
#include <string>


namespace container {
struct TextPosition {
  // Members:
  std::string m_source;
  std::string m_line;

  std::size_t m_lineno;
  std::size_t m_columno;

  // Methods:
  TextPosition();
  TextPosition(std::string t_source, std::string t_line, std::size_t t_lineno,
               std::size_t t_columnno);

  friend auto operator<<(std::ostream& t_os, const TextPosition& t_fp)
    -> std::ostream&;

  virtual ~TextPosition() = default;
};
} // namespace container

#endif // NEWLANG_CONTAINER_TEXT_POSITION_HPP
