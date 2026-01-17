#ifndef ACRIS_ACRIS_PREPROCESSOR_PREPROCESSOR_HPP
#define ACRIS_ACRIS_PREPROCESSOR_PREPROCESSOR_HPP

// STL Includes:
#include <filesystem>
#include <set>
#include <string>

// Absolute Includes:
#include "acris/container/text_buffer.hpp"
#include "acris/container/text_stream.hpp"
#include "lib/stdtypes.hpp"

namespace preprocessor {
using container::TextBufferPtr;
using container::TextBuffer;
using container::TextStreamPtr;

namespace fs = std::filesystem;

using IncludedRegister = std::set<std::filesystem::path>;

constexpr u8 MAX_INCLUDE_NESTING{255};

struct IncludePack {
  bool m_is_lib;
  std::string m_include;
};

class Preprocessor {
  private:
  TextStreamPtr m_text;

  u16 m_nesting_count;
  IncludedRegister m_already_included;


  public:
  explicit Preprocessor(TextStreamPtr t_text);

	auto make_buffer() -> TextBufferPtr;

  auto include_file(TextBufferPtr& t_buffer, const fs::path t_path) -> void;
  auto get_include_path(TextStreamPtr t_text) -> IncludePack;
  auto skip_whitespace(TextStreamPtr t_text);

  auto handle_include_once(TextStreamPtr t_text, TextBufferPtr& t_buffer)
    -> void;
  auto handle_include(TextStreamPtr t_text, TextBufferPtr& t_buffer) -> void;
  auto handle_preprocessor(TextStreamPtr t_text, TextBufferPtr& t_buffer)
    -> void;

  auto preprocess() -> TextStreamPtr;

  virtual ~Preprocessor() = default;
};
} // namespace preprocessor

#endif // ACRIS_ACRIS_PREPROCESSOR_PREPROCESSOR_HPP
