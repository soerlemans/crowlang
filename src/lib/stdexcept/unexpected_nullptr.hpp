#ifndef UNEXPECTED_NULLPTR_HPP
#define UNEXPECTED_NULLPTR_HPP

// Local Includes:
#include "exception.hpp"

namespace lib::stdexcept {
class UnexpectedNullptr : public Exception {
  public:
  UnexpectedNullptr(std::string_view t_msg);

  virtual ~UnexpectedNullptr() = default;
};

// Functions:
template<typename... Args>
auto unexpected_nullptr(Args&&... t_args) -> void
{
  exception<UnexpectedNullptr>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept

#endif // UNEXPECTED_NULLPTR_HPP
