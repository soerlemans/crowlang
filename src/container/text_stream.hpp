#ifndef CROW_CONTAINER_TEXT_STREAM_HPP
#define CROW_CONTAINER_TEXT_STREAM_HPP

// STL Includes:
#include <string>

// Local Includes:
#include "stream.hpp"


namespace container {
class TextStream : public Stream<std::string> {
  public:
	auto next_line() -> void;

  virtual ~TextStream() = default;
};
} // namespace container

#endif // CROW_CONTAINER_TEXT_STREAM_HPP
