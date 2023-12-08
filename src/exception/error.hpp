#ifndef CROW_EXCEPTION_STACKTRACE_EXCEPTION_HPP
#define CROW_EXCEPTION_STACKTRACE_EXCEPTION_HPP

// STL Includes:
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <utility>

// Library Includes:
#include <cpptrace/cpptrace.hpp>

// Macros:
#ifdef DEBUG
#define ERROR_PARENT cpptrace::exception
#else
#define ERROR_PARENT std::exception
#endif

namespace exception {
// Classes:
/*!
 * Base exception/error class.
 * Includes a stacktrace when compiling with the @ref DEBUG macro defined.
 */
class Error : public ERROR_PARENT {
  private:
  //! format() constructs a std::stringstraam in order to append to the message
  virtual auto format(std::string_view t_msg) -> std::string = 0;

  protected:
  std::string m_error;

  public:
  Error(std::string t_msg);

  auto what() const noexcept -> const char* override;

  ~Error() override = default;
};


// Functions:
template<typename T, typename... Args>
  requires std::is_base_of<Error, T>::value
inline auto error(Args&&... t_args) -> void
{
  std::stringstream ss;

  // Add all arguments to the string stream.
  (ss << ... << t_args);

  throw T{ss.view()};
}
} // namespace exception

#endif // CROW_EXCEPTION_STACKTRACE_EXCEPTION_HPP
