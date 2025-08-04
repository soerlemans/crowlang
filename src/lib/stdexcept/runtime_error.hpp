#ifndef CROW_LIB_STDEXCEPT_RUNTIME_ERROR_HPP
#define CROW_LIB_STDEXCEPT_RUNTIME_ERROR_HPP

// Local Includes:
#include "exception.hpp"

namespace lib::stdexcept {
class RuntimeError : public Exception {
  public:
  RuntimeError(std::string_view t_msg);

  virtual ~RuntimeError() = default;
};

// Functions:
template<typename... Args>
inline auto throw_runtime_error(Args&&... t_args) -> void
{
  throw_exception<RuntimeError>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept

#endif // CROW_LIB_STDEXCEPT_RUNTIME_ERROR_HPP
