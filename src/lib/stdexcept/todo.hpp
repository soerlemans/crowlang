#ifndef TODO_HPP
#define TODO_HPP

// Local Includes:
#include "exception.hpp"

#define TODO(t_msg)                    \
  do {                                 \
    lib::stdexcept::throw_todo(t_msg); \
  } while(false)

/*
 * #define TODO(t_msg)                              \
 *   do {                                           \
 *     lib::stdexcept::throw_todo(t_msg##__func__); \
 *   } while(false)
 */

namespace lib::stdexcept {
class Todo : public Exception {
  public:
  Todo(std::string_view t_msg);

  virtual ~Todo() = default;
};

// Functions:
template<typename... Args>
inline auto throw_todo(Args&&... t_args) -> void
{
  throw_exception<Todo>(std::forward<Args>(t_args)...);
}
} // namespace lib::stdexcept

#endif // TODO_HPP
