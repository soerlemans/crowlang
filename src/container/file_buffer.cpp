#include "file_buffer.hpp"
#include "text_buffer.hpp"

// STL Includes:
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>


using namespace container;

// Methods:
FileBuffer::FileBuffer(fs::path&& t_path): m_path{std::move(t_path)}
{
  load();
}

auto FileBuffer::load() -> void
{
  if(!fs::exists(m_path)) {
    std::string error_str{"File does not exist! \""};
    error_str += m_path.string();
    error_str += "\"";

    throw std::invalid_argument{error_str};
  }

  std::ifstream ifs{m_path};
  while(ifs.good() && !ifs.eof()) {
    std::string line;
    std::getline(ifs, line);

    // Dont discard newlines
    line += '\n';

    add_line(line);
  }
}

auto FileBuffer::path() const -> fs::path
{
  return m_path;
}

auto FileBuffer::position() const -> TextPosition
{
  // Return the current position in the filebuffer as a FilePosition struct
  return {m_path.string(), line(), m_lineno, m_columnno};
}

namespace container {
auto operator<<(std::ostream& t_os, const FileBuffer& t_fb) -> std::ostream&
{
  t_os << t_fb.path() << '\n';
  t_os << (const TextBuffer&)t_fb;

  return t_os;
}
} // namespace container
