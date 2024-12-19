#ifndef DEFER_HPP
#define DEFER_HPP

// Include STL:
#include <functional>

namespace stdllibcrow::internal {
template<typename T>
class Defer {
  private:
  std::function<T> m_fn;

  public:
  Defer(std::function<T>&& t_fn): m_fn{t_fn}
  {}

  ~Defer()
  {
    m_fn();
  }
};
} // namespace stdllibcrow::internal

#endif // DEFER_HPP
