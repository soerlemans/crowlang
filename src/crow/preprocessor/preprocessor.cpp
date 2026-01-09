#include "preprocessor.hpp"

// STL Includes:
#include <cctype>
#include <sstream>
#include <string_view>

// Absolute Includes:
#include "crow/debug/log.hpp"

using namespace std::string_view_literals;

static const auto include_once{"include_once"sv};
static const auto include{"include"sv};

namespace preprocessor {
Preprocessor::Preprocessor(TextStreamPtr t_text)
  : m_text{t_text}, m_already_included{}
{}

// /usr/local/include/stdlibcrow/


auto Preprocessor::get_include_path() -> std::string
{
  std::stringstream ss{};

  const auto ch{(unsigned char)m_text->character()};
  if(ch == '<') {
    m_text->next();

    while(!m_text->eos()) {
      const auto ch{(unsigned char)m_text->character()};
      if(ch == '>') {
        break;
      }

      ss << ch;

      m_text->next();
    }
  } else {
    // TODO: Throw.
  }

  return ss.str();
}

auto Preprocessor::perform_include_once(TextBufferPtr& t_buffer) -> void
{
  while(!m_text->eos()) {
    const auto ch{(unsigned char)m_text->character()};
    if(ch != ' ') {
      break;
    }

    m_text->next();
  }

  const auto include_path{get_include_path()};
  DBG_INFO("include_path: ", include_path);
}

auto Preprocessor::perform_include(TextBufferPtr& t_buffer) -> void
{
  while(!m_text->eos()) {
    const auto ch{(unsigned char)m_text->character()};
    if(ch != ' ') {
      DBG_INFO("ch: ", ch);
      break;
    }

    m_text->next();
  }


  const auto include_path{get_include_path()};
  DBG_INFO("include_path: ", include_path);
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
        perform_include_once(buffer);
      } else if(str == include) {
        perform_include(buffer);
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
