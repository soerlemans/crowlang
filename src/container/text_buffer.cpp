#include "text_buffer.hpp"


using namespace container;

// Methods:
TextBuffer::TextBuffer(): m_lineno{0}, m_columnno{0}
{
  m_buffer.reserve(256);
}

TextBuffer::TextBuffer(const std::string_view t_source)
  : m_source{t_source}, m_lineno{0}, m_columnno{0}
{
  m_buffer.reserve(256);
}

auto TextBuffer::add_line(std::string t_line) -> void
{
  // Warning: We disregard carriage return's
  if(t_line.back() != '\n') {
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

//! Wraps to the next_line() when at the end of a line
auto TextBuffer::next() const -> char
{
  const auto& line{m_buffer[m_lineno]};
  const char ch{line[m_columnno]};

  if(m_columnno + 1 >= line.size()) {
    next_line();
  } else {
    m_columnno++;
  }


  return ch;
}

auto TextBuffer::prev() const -> char
{
  const auto& line{m_buffer[m_lineno]};
  const char ch{line[m_columnno]};

  if(m_columnno) {
    m_columnno--;
  }

  return ch;
}

auto TextBuffer::character() const -> char
{
  return m_buffer[m_lineno][m_columnno];
}

auto TextBuffer::is_newline() const -> bool
{
  return character() == '\n';
}

auto TextBuffer::eos() const -> bool
{
  return m_lineno >= m_buffer.size();
}

//! This method is required for token creating in the Lexer, think about how to
//! make this more elegant
auto TextBuffer::position() const -> TextPosition
{
  return {"", m_buffer[m_lineno], m_lineno, m_columnno};
}

namespace container {
auto operator<<(std::ostream& t_os, const TextBuffer& t_tb) -> std::ostream&
{
  for(auto& line : t_tb.m_buffer) {
    t_os << line;
  }

  return t_os;
}
} // namespace container
