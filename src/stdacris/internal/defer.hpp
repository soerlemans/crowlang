#ifndef ACRIS_STDACRIS_INTERNAL_DEFER_HPP
#define ACRIS_STDACRIS_INTERNAL_DEFER_HPP

// Include STL:
#include <functional>

namespace stdlibacris::internal {
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
} // namespace stdlibacris::internal

#endif // ACRIS_STDACRIS_INTERNAL_DEFER_HPP
