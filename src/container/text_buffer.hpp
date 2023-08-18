#ifndef CROW_CONTAINER_TEXT_BUFFER_HPP
#define CROW_CONTAINER_TEXT_BUFFER_HPP

// STL Includes:
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

// Local Includes:
#include "text_position.hpp"


namespace container {
// Forward Declarations:
class TextBuffer;

// Aliases:
using TextBufferPtr = std::shared_ptr<TextBuffer>;

// Classes:
class TextBuffer {
  private:
  std::vector<std::string> m_buffer;

  // Keep track of current position in the filebuffer
  mutable std::size_t m_lineno, m_columnno;

  public:
  TextBuffer();

  auto add_line(std::string t_line) -> void;

  // Line movement:
  auto next() const -> std::string;
  auto prev() const -> std::string;

  // Character movement:
  auto forward() const -> char;
  auto backward() const -> char;

  // Getters:
  auto line() const -> std::string;
  auto character() const -> char;

  auto size() const -> std::size_t;

  auto eol() const -> bool;
  auto eof() const -> bool;

  virtual auto position() const -> TextPosition;

  friend auto operator<<(std::ostream& t_os, const TextBuffer& t_tb)
    -> std::ostream&;

  virtual ~TextBuffer() = default;
};
} // namespace container

#endif // CROW_CONTAINER_TEXT_BUFFER_HPP
