#ifndef CROW_EXCEPTION_TYPE_ERROR_HPP
#define CROW_EXCEPTION_TYPE_ERROR_HPP

// Local Includes:
#include "stacktrace_exception.hpp"


namespace exception {
class TypeError : public StacktraceException {
  private:
  auto format(std::string_view t_msg) -> std::string override;

  public:
  TypeError(std::string_view t_msg);

  ~TypeError() override = default;
};
} // namespace exception

#endif // CROW_EXCEPTION_TYPE_ERROR_HPP
