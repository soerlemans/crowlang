#include "text_stream.hpp"

namespace container {
// Methods:
TextStream::TextStream(): m_lineno{0}, m_columnno{0}
{}

auto TextStream::next_line() -> void
{
  while(current() != '\n' && !eos()) {
    next();
  }
}
} // namespace container
