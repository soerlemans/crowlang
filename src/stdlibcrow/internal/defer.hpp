#ifndef CROW_STDLIBCROW_INTERNAL_DEFER_HPP
#define CROW_STDLIBCROW_INTERNAL_DEFER_HPP

// Include STL:
#include <functional>

namespace stdlibcrow::internal {
// Aliases:
using DeferFn = std::function<void()>;

// Classes:
/*!
 * Construct used to ensure freeing of resources at the end of a blocks
 */
class Defer {
  private:
  DeferFn m_fn;

  public:
  Defer(DeferFn&& t_fn): m_fn{t_fn}
  {}

  ~Defer()
  {
    m_fn();
  }
};
} // namespace stdlibcrow::internal

#endif // CROW_STDLIBCROW_INTERNAL_DEFER_HPP
