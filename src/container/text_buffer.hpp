#ifndef CROW_CONTAINER_TEXT_BUFFER_HPP
#define CROW_CONTAINER_TEXT_BUFFER_HPP

// STL Includes:
#include <string>
#include <string_view>
#include <vector>

// Local Includes:
#include "text_stream.hpp"


namespace container {
class TextBuffer : public TextStream {
  private:
  std::vector<std::string> m_buffer;

	std::string m_source;

  // Keep track of current position in the filebuffer
  mutable std::size_t m_lineno, m_columnno;

  public:
  TextBuffer();
  TextBuffer(const std::string_view t_source);

  auto add_line(std::string t_line) -> void;
  auto next_line() const -> void override;

  auto next() const -> char override;
  auto prev() const -> char override;

  auto character() const -> char override;
  auto is_newline() const -> bool override;

  auto eos() const -> bool override;

  auto position() const -> TextPosition override;

  friend auto operator<<(std::ostream& t_os, const TextBuffer& t_tb)
    -> std::ostream&;

  virtual ~TextBuffer() = default;
};
} // namespace container

#endif // CROW_CONTAINER_TEXT_BUFFER_HPP
