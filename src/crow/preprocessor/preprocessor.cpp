#include "preprocessor.hpp"

// STL Includes:
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// Absolute Includes:
#include "crow/debug/log.hpp"

using namespace std::string_view_literals;

static const auto std_include_path{"/usr/local/include/stdcrow/"sv};

static const auto include_once{"include_once"sv};
static const auto include{"include"sv};

// Using Statements:
using container::TextBuffer;
using container::TextBufferPtr;
using std::filesystem::path;

static auto read_file_into(TextBufferPtr& t_buffer, const path t_path) -> void
{
  using std::filesystem::exists;

  if(!exists(t_path)) {
    std::stringstream ss{};

    ss << "File does not exist! ";
    ss << std::quoted(t_path.string());

    throw std::invalid_argument{ss.str()};
  }

  std::ifstream ifs{t_path};
  while(ifs.good() && !ifs.eof()) {
    std::string line{};
    std::getline(ifs, line);

    t_buffer->add_line(std::move(line));
  }
}

namespace preprocessor {
Preprocessor::Preprocessor(TextStreamPtr t_text)
  : m_text{t_text}, m_already_included{}
{}

// /usr/local/include/stdlibcrow/


auto Preprocessor::get_include_path() -> IncludePack
{
  std::stringstream ss{};

  unsigned char term_char{'"'};

  IncludePack pack{};

  const auto ch{(unsigned char)m_text->character()};
  if(ch == '<' || ch == '"') {
    if(ch == '<') {
      // Library include path.
      pack.m_is_lib = true;
      term_char = '>';
    }
    m_text->next();

    while(!m_text->eos()) {
      const auto ch{(unsigned char)m_text->character()};
      if(ch == term_char) {
        break;
      }

      ss << ch;

      m_text->next();
    }
  } else {
    // TODO: Throw.
  }

  pack.m_include = ss.str();

  return pack;
}

auto Preprocessor::handle_include_once(TextBufferPtr& t_buffer) -> void
{
  while(!m_text->eos()) {
    const auto ch{(unsigned char)m_text->character()};
    if(ch != ' ') {
      break;
    }

    m_text->next();
  }

  auto [is_lib, original] = get_include_path();
  DBG_INFO("include: ", original);

  path include{};
  if(is_lib) {
    include = path{std::format("{}{}", std_include_path, original)};
  } else {
    include = path{original};
  }
  include = std::filesystem::absolute(include);

  if(m_already_included.contains(include) == false) {
    read_file_into(t_buffer, include);

    m_already_included.insert(include);
  }
}

auto Preprocessor::handle_include(TextBufferPtr& t_buffer) -> void
{
  while(!m_text->eos()) {
    const auto ch{(unsigned char)m_text->character()};
    if(ch != ' ') {
      break;
    }

    m_text->next();
  }

  auto [is_lib, original] = get_include_path();
  DBG_INFO("include: ", original);

  path include{};
  if(is_lib) {
    include = path{std::format("{}{}", std_include_path, original)};
  } else {
    include = path{original};
  }
  include = std::filesystem::absolute(include);

  read_file_into(t_buffer, include);
}

auto Preprocessor::preprocess() -> TextStreamPtr
{
  using container::TextBuffer;

  auto buffer{std::make_shared<TextBuffer>()};

  while(!m_text->eos()) {
    const auto ch{(unsigned char)m_text->character()};

    // Lexing loop:
    if(ch == '#') {
      m_text->next();

      std::stringstream ss{};
      while(!m_text->eos()) {
        const auto pp_ch{(unsigned char)m_text->character()};
        if(std::isspace(pp_ch)) {
          break;
        }

        ss << pp_ch;

        m_text->next();
      }

      const auto str{ss.view()};
      if(str == include_once) {
        handle_include_once(buffer);
      } else if(str == include) {
        handle_include(buffer);
      }
    } else {
      buffer->add_line(std::string{m_text->line()});
    }

    m_text->next_line();
  }

  DBG_INFO("buffer: ", *buffer);

  return buffer;
}
} // namespace preprocessor
