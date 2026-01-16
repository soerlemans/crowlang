#include "text_buffer.hpp"


static constexpr std::size_t default_buffer_reserve_size{1'024};

namespace container {
// Methods:
TextBuffer::TextBuffer(): m_source{}, m_lineno{0}, m_columnno{0}
{
  m_buffer.reserve(default_buffer_reserve_size);
}

TextBuffer::TextBuffer(const std::string_view t_source)
  : m_source{t_source}, m_lineno{0}, m_columnno{0}
{
  m_buffer.reserve(default_buffer_reserve_size);
}

auto TextBuffer::add_line(std::string t_line) -> void
{
  // Warning: We disregard carriage return's.
  if(t_line.empty() || t_line.back() != '\n') {
    t_line += '\n';
  }

  m_buffer.push_back(std::move(t_line));
}

auto TextBuffer::next_line() const -> void
{
  // Changing lines resets the column number
  m_columnno = 0;
  m_lineno++;
}

auto TextBuffer::prev_line() const -> void
{
  // Changing lines resets the column number
  m_columnno = 0;
  m_lineno--;
}

//! Wraps to the @ref next_line() when at the end of a line.
auto TextBuffer::next() const -> void
{
  if(m_columnno + 1 >= line().size()) {
    next_line();
  } else {
    m_columnno++;
  }
}

auto TextBuffer::prev() const -> void
{
  if(m_columnno < 1) {
    prev_line();
  } else {
    m_columnno--;
  }
}

auto TextBuffer::peek() const -> CharOpt
{
  CharOpt ch;

  next();
  if(!eos()) {
    ch = character();
  }
  prev();

  return ch;
}

auto TextBuffer::character() const -> char
{
  return m_buffer.at(m_lineno).at(m_columnno);
}

auto TextBuffer::line() const -> std::string_view
{
  return m_buffer.at(m_lineno);
}

auto TextBuffer::eos() const -> bool
{
  return m_lineno >= m_buffer.size();
}

auto TextBuffer::reset() -> void
{
  m_lineno = 0;
  m_columnno = 0;
}

//! This method is required for token creating in the Lexer, think about how to
//! make this more elegant
auto TextBuffer::position() const -> TextPosition
{
  return TextPosition{m_source, line(), m_lineno, m_columnno};
}

auto operator<<(std::ostream& t_os, const TextBuffer& t_tb) -> std::ostream&
{
  for(const auto& line : t_tb.m_buffer) {
    t_os << line;
  }

  return t_os;
}
} // namespace container
