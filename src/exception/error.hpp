#ifndef CROW_EXCEPTION_ERROR_HPP
#define CROW_EXCEPTION_ERROR_HPP

// STL Includes:
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <utility>

// Library Includes:
#include <cpptrace/cpptrace.hpp>

namespace exception {
// Classes:
/*!
 * Base exception/error class.
 * Includes a stacktrace when compiling with the @ref DEBUG macro defined.
 */
class Error : public std::exception {
  protected:
  std::string m_error;

  public:
  Error(std::string t_msg);

  auto what() const noexcept -> const char* override;

  virtual ~Error() = default;
};


// Functions:
template<typename T = Error, typename... Args>
  requires std::is_base_of<Error, T>::value
inline auto error(Args&&... t_args) -> void
{
  std::stringstream ss;
  std::string str;

  // Add all arguments to the string stream.
  (ss << ... << t_args);

  str = ss.view();

  throw T{str};
}
} // namespace exception

#endif // CROW_EXCEPTION_ERROR_HPP
