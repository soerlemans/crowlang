#ifndef CROW_LIB_STDEXCEPT_RUNTIME_EXCEPTION_HPP
#define CROW_LIB_STDEXCEPT_RUNTIME_EXCEPTION_HPP

// Local Includes:
#include "exception.hpp"

namespace lib::stdexcept {
class RuntimeException : public Exception {
  public:
  RuntimeException(std::string_view t_msg);

  virtual ~RuntimeException() = default;
};

// Functions:
template<typename... Args>
inline auto throw_runtime_exception(Args&&... t_args) -> void
{
  throw_exception<RuntimeException>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept

#endif // CROW_LIB_STDEXCEPT_RUNTIME_EXCEPTION_HPP
