#ifndef CROW_EXCEPTION_TYPE_ERROR_HPP
#define CROW_EXCEPTION_TYPE_ERROR_HPP

// STL Includes:
#include <stdexcept>


namespace exception {
class TypeError : public std::exception {
  protected:
  std::string m_error;

  public:
  TypeError(std::string_view t_msg);

  auto what() const noexcept -> const char* override;
};
} // namespace exception

#endif // CROW_EXCEPTION_TYPE_ERROR_HPP
