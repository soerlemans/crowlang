#ifndef PREPROCESSOR_ERROR_HPP
#define PREPROCESSOR_ERROR_HPP

// STL Includes:
#include <filesystem>

// Absolute Includes:
#include "acris/container/text_position.hpp"

// Local Includes:
#include "diagnostic_error.hpp"

namespace diagnostic {
// Using Statements:
using container::TextPosition;

// TODO: Maybe add an option to show the nested include?
// So a user can trace back what kicked off recursive inclusion or similar?

// Classes:
/*!
 * Is thrown during the preprocessor step of compilation.
 */
class PreprocessorError : public DiagnosticError {
  private:
  auto format(std::string_view t_msg, const TextPosition& t_pos) const
    -> std::string;

  protected:
  container::TextPosition m_pos;

  public:
  PreprocessorError(std::string_view t_msg, const TextPosition& t_pos);

  virtual ~PreprocessorError() = default;
};
} // namespace diagnostic

#endif // PREPROCESSOR_ERROR_HPP
