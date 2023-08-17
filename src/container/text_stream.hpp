#ifndef NEWLANG_CONTAINER_TEXT_STREAM_HPP
#define NEWLANG_CONTAINER_TEXT_STREAM_HPP

// Local Includes:
#include "stream.hpp"


namespace container {
class TextStream : public Stream {
  private:
  TextBufferPtr m_tb;

  mutable std::size_t m_lineno, m_columnno;

  public:
	TextStream(TextBufferPtr t_tb);

	virtual ~TextStream() = default;
};
} // namespace container

#endif // NEWLANG_CONTAINER_TEXT_STREAM_HPP
