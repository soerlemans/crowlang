#ifndef CROW_STDLIB_IO_HPP
#define CROW_STDLIB_IO_HPP

namespace stdlib {
template<typename... Args>
inline auto println(std::format_string<Args...> t_fmt, Args&&... t_args) -> void
{
  std::println(fmt, std::forward<Args>(t_args)...);
}
} // namespace stdlib

#endif // CROW_STDLIB_IO_HPP
