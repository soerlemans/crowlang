#ifndef CROW_EXCEPTION_TYPE_ERROR_HPP
#define CROW_EXCEPTION_TYPE_ERROR_HPP

// Local Includes:
#include "error.hpp"


namespace exception {
// Classes:
class TypeError : public Error {
  private:
  auto format(std::string_view t_msg) -> std::string;

  public:
  TypeError(std::string_view t_msg);

  ~TypeError() override = default;
};

// Functions:
template<typename... Args>
auto type_error(Args&&... t_args) -> void
{
  using namespace exception;

  exception::error<TypeError>(std::forward<Args>(t_args)...);

  std::stringstream ss;

  // Fold expression
  (ss << ... << t_args);

  throw TypeError{ss.view()};
}
} // namespace exception

#endif // CROW_EXCEPTION_TYPE_ERROR_HPP
