#ifndef CROW_LIB_STDEXCEPT_EXCEPTION_HPP
#define CROW_LIB_STDEXCEPT_EXCEPTION_HPP

/*!
 * @file Exception.hpp
 *
 * Helper exceptions which conditionally have stacktrace support or not.
 * Used for reporting errors that should not happen within the application.
 */

// STL Includes:
#include <sstream>
#include <string>
#include <string_view>

// Library Includes:
#include <cpptrace/cpptrace.hpp>

namespace lib::stdexcept {
class Exception {
  private:
  std::string m_msg;

  public:
  Exception(std::string_view t_msg);

  auto what() const noexcept -> const std::string_view;

  virtual ~Exception() = default;
};

// Functions:
template<typename T = Exception, typename... Args>
  requires std::is_base_of<Exception, T>::value
inline auto throw_exception(Args&&... t_args) -> void
{
  std::stringstream ss{};

  // Add all arguments to the string stream.
  (ss << ... << t_args);

  throw T{ss.view()};
}
} // namespace lib::stdexcept

#endif // CROW_LIB_STDEXCEPT_EXCEPTION_HPP
