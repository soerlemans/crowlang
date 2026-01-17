#include "preprocessor.hpp"

// STL Includes:
#include <cctype>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/diagnostic/diagnostic.hpp"

namespace {
using namespace std::string_view_literals;
constexpr auto std_include_path{"/usr/local/include/stdcrow/"sv};

constexpr auto include_once{"include_once"sv};
constexpr auto include{"include"sv};

constexpr char space{' '};
constexpr char newline{'\n'};
constexpr char directive_start{'#'};
} // namespace

namespace preprocessor {
using diagnostic::PreprocessorError;

Preprocessor::Preprocessor(TextStreamPtr t_text)
  : m_text{t_text}, m_nesting_count{0}, m_already_included{}
{}

auto Preprocessor::make_buffer() -> TextBufferPtr
{
  const auto source_file{m_text->source()};

  return std::make_shared<TextBuffer>(source_file);
}

auto Preprocessor::include_file(TextBufferPtr& t_buffer, const fs::path t_path)
  -> void
{
  using fs::exists;

  if(!exists(t_path)) {
    std::stringstream ss{};

    ss << "File does not exist ";
    ss << std::quoted(t_path.string()) << '!';

    const auto pos{t_buffer->position()};

    throw PreprocessorError{ss.str(), pos};
  }

  std::ifstream ifs{t_path};
  while(ifs.good() && !ifs.eof()) {
    std::string line{};
    std::getline(ifs, line);

    t_buffer->add_line(line);

    // Nested include directive.
    if(!line.empty() && line.front() == directive_start) {
      auto buffer{make_buffer()};

      m_nesting_count++;
      if(m_nesting_count >= MAX_INCLUDE_NESTING) {
        auto pos{t_buffer->end_position()};

        throw PreprocessorError{
          std::format("Exceeded maximum #include nesting count of {} includes.",
                      MAX_INCLUDE_NESTING),
          pos};
      }

      handle_preprocessor(t_buffer, buffer);
      m_nesting_count--;

      // Expanded buffer write to intermediary.
      t_buffer = std::move(buffer);
    }
  }
}

auto Preprocessor::get_include_path(TextStreamPtr t_text) -> IncludePack
{
  std::stringstream ss{};

  unsigned char term_char{'"'};

  IncludePack pack{};

  const auto ch{(unsigned char)t_text->character()};
  if(ch == '<' || ch == '"') {
    if(ch == '<') {
      // Library include path.
      pack.m_is_lib = true;
      term_char = '>';
    }
    t_text->next();

    while(!t_text->eos()) {
      const auto ch{(unsigned char)t_text->character()};
      if(ch == term_char) {
        break;
      }

      if(ch == newline) {
        auto pos{t_text->position()};

        throw PreprocessorError{
          std::format("Newlines are when defining include paths.."), pos};
      }

      ss << ch;

      t_text->next();
    }
  } else {
    // TODO: Throw.
  }

  pack.m_include = ss.str();

  return pack;
}

auto Preprocessor::skip_whitespace(TextStreamPtr t_text)
{
  while(!t_text->eos()) {
    const auto ch{(unsigned char)t_text->character()};
    if(ch != space) {
      break;
    }

    t_text->next();
  }
}

auto Preprocessor::handle_include_once(TextStreamPtr t_text,
                                       TextBufferPtr& t_buffer) -> void
{
  skip_whitespace(t_text);

  auto [is_lib, original] = get_include_path(t_text);
  DBG_INFO("include_once: ", std::quoted(original), " : ", m_nesting_count);

  const auto prepend{(is_lib) ? std_include_path : ""sv};
  fs::path include{std::format("{}{}", prepend, original)};
  include = fs::absolute(include);

  if(m_already_included.contains(include) == false) {
    include_file(t_buffer, include);

    m_already_included.insert(include);
  }
}

auto Preprocessor::handle_include(TextStreamPtr t_text, TextBufferPtr& t_buffer)
  -> void
{
  skip_whitespace(t_text);

  auto [is_lib, original] = get_include_path(t_text);
  DBG_INFO("include: ", std::quoted(original), " : ", m_nesting_count);

  const auto prepend{(is_lib) ? std_include_path : ""sv};
  fs::path include{std::format("{}{}", prepend, original)};
  include = fs::absolute(include);

  include_file(t_buffer, include);
}

auto Preprocessor::handle_preprocessor(TextStreamPtr t_text,
                                       TextBufferPtr& t_buffer) -> void
{
  if(m_nesting_count >= MAX_INCLUDE_NESTING) {
    auto pos{t_text->end_position()};

    throw PreprocessorError{
      std::format("Exceeded maximum #include nesting count of {} includes.",
                  MAX_INCLUDE_NESTING),
      pos};
  }

  while(!t_text->eos()) {
    const auto ch{(unsigned char)t_text->character()};

    // Directive processing loop.
    if(ch == directive_start) {
      t_text->next();

      std::stringstream ss{};
      while(!t_text->eos()) {
        // FIXME: This checking for spaces strategy is not optimal.
        const auto pp_ch{(unsigned char)t_text->character()};
        if(std::isspace(pp_ch)) {
          break;
        }

        ss << pp_ch;

        t_text->next();
      }

      const auto str{ss.view()};
      if(str == include_once) {
        handle_include_once(t_text, t_buffer);
      } else if(str == include) {
        handle_include(t_text, t_buffer);
      }
    } else {
      t_buffer->add_line(std::string{t_text->line()});
    }

    t_text->next_line();
  }
}

auto Preprocessor::preprocess() -> TextStreamPtr
{
  auto buffer{make_buffer()};

  handle_preprocessor(m_text, buffer);
  DBG_INFO("buffer: ", *buffer);

  m_text->reset();

  return buffer;
}
} // namespace preprocessor
