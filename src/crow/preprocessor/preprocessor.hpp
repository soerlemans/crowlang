#ifndef CROW_CROW_PREPROCESSOR_PREPROCESSOR_HPP
#define CROW_CROW_PREPROCESSOR_PREPROCESSOR_HPP

// STL Includes:
#include <filesystem>
#include <set>
#include <string>

// Absolute Includes:
#include "crow/container/text_buffer.hpp"
#include "crow/container/text_stream.hpp"

namespace preprocessor {
using container::TextBufferPtr;
using container::TextStreamPtr;

using IncludedRegister = std::set<std::filesystem::path>;

struct IncludePack {
  bool m_is_lib;
  std::string m_include;
};

class Preprocessor {
  private:
  TextStreamPtr m_text;

  IncludedRegister m_already_included;

  public:
  explicit Preprocessor(TextStreamPtr t_text);

  auto get_include_path() -> IncludePack;

  auto handle_include_once(TextBufferPtr& t_buffer) -> void;
  auto handle_include(TextBufferPtr& t_buffer) -> void;

  auto preprocess() -> TextStreamPtr;

  virtual ~Preprocessor() = default;
};
} // namespace preprocessor

#endif // CROW_CROW_PREPROCESSOR_PREPROCESSOR_HPP
