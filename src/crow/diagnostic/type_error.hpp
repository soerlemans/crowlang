#ifndef CROW_CROW_DIAGNOSTIC_TYPE_ERROR_HPP
#define CROW_CROW_DIAGNOSTIC_TYPE_ERROR_HPP

// Local Includes:
#include "diagnostic_error.hpp"

namespace diagnostic {
// Classes:
class TypeError : public DiagnosticError {
  private:
  auto format(std::string_view t_msg) -> std::string;

  public:
  TypeError(std::string_view t_msg);

  virtual ~TypeError() = default;
};

// Functions:
template<typename... Args>
auto type_error(Args&&... t_args) -> void
{
  using diagnostic::diagnostic_error;
  using diagnostic::TypeError;

  diagnostic_error<TypeError>(std::forward<Args>(t_args)...);

  std::stringstream ss;

  // Fold expression
  (ss << ... << t_args);

  throw TypeError{ss.view()};
}
} // namespace diagnostic

#endif // CROW_CROW_DIAGNOSTIC_TYPE_ERROR_HPP
