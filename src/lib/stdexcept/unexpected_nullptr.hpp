#ifndef CROW_LIB_STDEXCEPT_UNEXPECTED_NULLPTR_HPP
#define CROW_LIB_STDEXCEPT_UNEXPECTED_NULLPTR_HPP

// Local Includes:
#include "exception.hpp"

namespace lib::stdexcept {
// Classes:
class UnexpectedNullptr : public Exception {
  public:
  UnexpectedNullptr(std::string_view t_msg);

  virtual ~UnexpectedNullptr() = default;
};

// Functions:
template<typename... Args>
inline auto throw_unexpected_nullptr(Args&&... t_args) -> void
{
  throw_exception<UnexpectedNullptr>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept

#endif // CROW_LIB_STDEXCEPT_UNEXPECTED_NULLPTR_HPP
