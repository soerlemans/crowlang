#ifndef CROW_EXCEPTION_STACKTRACE_EXCEPTION_HPP
#define CROW_EXCEPTION_STACKTRACE_EXCEPTION_HPP

// STL Includes:
#include <stdexcept>
#include <string_view>

// Library Includes:
#include <cpptrace/cpptrace.hpp>

// Library Includes:
#include <cpptrace/cpptrace.hpp>


// Macros:
#ifdef DEBUG
#define STACKTRACE_EXCEPTION_PARENT cpptrace::exception
#else
#define STACKTRACE_EXCEPTION_PARENT std::exception
#endif

namespace exception {
//! Exception class that includes a stacktrace when compiling for a DEBUG build
class StacktraceException : public STACKTRACE_EXCEPTION_PARENT {
  private:
	//! format() constructs a std::stringstraam in order to append to the message
  virtual auto format(std::string_view t_msg) -> std::string = 0;

  protected:
  std::string m_error;

  public:
  StacktraceException(std::string t_msg);

  auto what() const noexcept -> const char* override;

  ~StacktraceException() override = default;
};
} // namespace exception

#endif // CROW_EXCEPTION_STACKTRACE_EXCEPTION_HPP
