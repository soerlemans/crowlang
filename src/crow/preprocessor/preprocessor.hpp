#ifndef CROW_CROW_PREPROCESSOR_PREPROCESSOR_HPP
#define CROW_CROW_PREPROCESSOR_PREPROCESSOR_HPP

// STL Includes:
#include <set>

// Absolute Includes:
#include "crow/container/text_stream.hpp"
#include "crow/container/text_buffer.hpp"

namespace preprocessor {
using container::TextBufferPtr;
using container::TextStreamPtr;

class Preprocessor {
  private:
  TextStreamPtr m_text;

  std::set<std::string> m_already_included;

  public:
  explicit Preprocessor(TextStreamPtr t_text);

	auto get_include_path() -> std::string;

  auto perform_include_once(TextBufferPtr& t_buffer) -> void;
  auto perform_include(TextBufferPtr& t_buffer) -> void;

  auto preprocess() -> TextStreamPtr;

  virtual ~Preprocessor() = default;
};
} // namespace preprocessor

#endif // CROW_CROW_PREPROCESSOR_PREPROCESSOR_HPP
