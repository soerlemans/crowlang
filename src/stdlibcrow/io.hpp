#ifndef CROW_STDLIBCROW_IO_HPP
#define CROW_STDLIBCROW_IO_HPP

// STL Includes:
#include <format>
#include <print>

namespace stdlibcrow {
template<typename... Args>
inline auto print(std::format_string<Args...> t_fmt, Args&&... t_args) -> void
{
  std::print(t_fmt, std::forward<Args>(t_args)...);
}

template<typename... Args>
inline auto println(std::format_string<Args...> t_fmt, Args&&... t_args) -> void
{
  std::println(t_fmt, std::forward<Args>(t_args)...);
}
} // namespace stdlibcrow

#endif // CROW_STDLIBCROW_IO_HPP
