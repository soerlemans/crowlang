#include "text_buffer.hpp"


using namespace container;

// Methods:
TextBuffer::TextBuffer(): m_lineno{0}, m_columnno{0}
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

auto TextBuffer::next() const -> std::string
{
  // Changing lines resets the column number
  m_columnno = 0;

  return m_buffer[m_lineno++];
}

auto TextBuffer::prev() const -> std::string
{
  std::string result{m_buffer[m_lineno]};

  // Changing lines resets the column number
  m_columnno = 0;

  // Logically you can go past a stream but not in front of a stream
  if(m_lineno) {
    m_lineno--;
  }

  return result;
}

auto TextBuffer::forward() const -> char
{
  return m_buffer[m_lineno][m_columnno++];
}

auto TextBuffer::backward() const -> char
{
  const char character{m_buffer[m_lineno][m_columnno]};

  if(m_columnno) {
    m_columnno--;
  }

  return character;
}

auto TextBuffer::line() const -> std::string
{
  return m_buffer[m_lineno];
}

auto TextBuffer::character() const -> char
{
  return m_buffer[m_lineno][m_columnno];
}

auto TextBuffer::size() const -> std::size_t
{
  return m_buffer.size();
}

auto TextBuffer::eol() const -> bool
{
  return m_columnno >= line().size();
}

auto TextBuffer::eof() const -> bool
{
  return m_lineno >= size();
}

auto TextBuffer::path() const -> fs::path
{
  return fs::path{""};
}

//! This method is required for token creating in the Lexer, think about how to
//! make this more elegant
auto TextBuffer::position() const -> TextPosition
{
  return {"", line(), m_lineno, m_columnno};
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
