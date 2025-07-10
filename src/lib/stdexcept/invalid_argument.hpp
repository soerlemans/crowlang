#ifndef CROW_LIB_STDEXCEPT_INVALID_ARGUMENT_HPP
#define CROW_LIB_STDEXCEPT_INVALID_ARGUMENT_HPP

// Local Includes:
#include "exception.hpp"

namespace lib::stdexcept {
class InvalidArgument : public Exception {
  public:
  InvalidArgument(std::string_view t_msg);

  virtual ~InvalidArgument() = default;
};

// Functions:
template<typename... Args>
auto invalid_argument(Args&&... t_args) -> void
{
  exception<InvalidArgument>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept

#endif // CROW_LIB_STDEXCEPT_INVALID_ARGUMENT_HPP
