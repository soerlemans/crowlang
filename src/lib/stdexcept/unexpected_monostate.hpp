#ifndef ACRIS_LIB_STDEXCEPT_UNEXPECTED_MONOSTATE_HPP
#define ACRIS_LIB_STDEXCEPT_UNEXPECTED_MONOSTATE_HPP

// Local Includes:
#include "exception.hpp"

namespace lib::stdexcept {
// Classes:
class UnexpectedMonostate : public Exception {
  public:
  UnexpectedMonostate(std::string_view t_msg);

  virtual ~UnexpectedMonostate() = default;
};

// Functions:
template<typename... Args>
inline auto throw_unexpected_monostate(Args&&... t_args) -> void
{
  throw_exception<UnexpectedMonostate>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept

#endif // ACRIS_LIB_STDEXCEPT_UNEXPECTED_MONOSTATE_HPP
