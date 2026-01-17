#ifndef ACRIS_LIB_STDEXCEPT_LOGIC_ERROR_HPP
#define ACRIS_LIB_STDEXCEPT_LOGIC_ERROR_HPP

// Local Includes:
#include "exception.hpp"

// Macros:
#define LOGIC_ERROR(...) lib::stdexcept::throw_logic_error(__VA_ARGS__)

namespace lib::stdexcept {
// Classes:
class LogicError : public Exception {
  public:
  LogicError(std::string_view t_msg);

  virtual ~LogicError() = default;
};

// Functions:
template<typename... Args>
inline auto throw_logic_error(Args&&... t_args) -> void
{
  throw_exception<LogicError>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept

#endif // ACRIS_LIB_STDEXCEPT_LOGIC_ERROR_HPP
