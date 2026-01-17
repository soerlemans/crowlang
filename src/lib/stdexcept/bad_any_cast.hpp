#ifndef ACRIS_LIB_STDEXCEPT_BAD_ANY_CAST_HPP
#define ACRIS_LIB_STDEXCEPT_BAD_ANY_CAST_HPP

// Local Includes:
#include "exception.hpp"

namespace lib::stdexcept {
class BadAnyCast : public Exception {
  public:
  BadAnyCast(std::string_view t_msg);

  virtual ~BadAnyCast() = default;
};

// Functions:
template<typename... Args>
auto throw_bad_any_cast(Args&&... t_args) -> void
{
  throw_exception<BadAnyCast>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept
#endif // ACRIS_LIB_STDEXCEPT_BAD_ANY_CAST_HPP
