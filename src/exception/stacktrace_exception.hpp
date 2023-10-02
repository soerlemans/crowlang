#ifndef STACKTRACE_EXCEPTION_HPP
#define STACKTRACE_EXCEPTION_HPP

// STL Includes:
#include <stdexcept>

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
  protected:
  std::string m_error;

  public:
  StacktraceException(std::string_view t_msg);

  auto what() const noexcept -> const char* override;

  ~StacktraceException() override = default;
};
} // namespace exception

#endif // STACKTRACE_EXCEPTION_HPP
