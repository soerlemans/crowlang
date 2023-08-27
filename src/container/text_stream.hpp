#ifndef CROW_CONTAINER_TEXT_STREAM_HPP
#define CROW_CONTAINER_TEXT_STREAM_HPP

// STL Includes:
#include <string>
#include <memory>

// Local Includes:
#include "stream.hpp"
#include "text_position.hpp"


namespace container {
// Forward Declarations:
class TextStream;

// Aliases:
using TextStreamPtr = std::shared_ptr<TextStream>;

// Classes:
class TextStream {
  public:
  virtual auto next_line() const -> void = 0;

  virtual auto next() const -> char = 0;
  virtual auto prev() const -> char = 0;

  virtual auto character() const -> char = 0;
  virtual auto is_newline() const -> bool = 0;

  virtual auto eos() const -> bool = 0;

  virtual auto position() const -> TextPosition = 0;

  virtual ~TextStream() = default;
};
} // namespace container

#endif // CROW_CONTAINER_TEXT_STREAM_HPP
