#ifndef CROW_LIB_VISITABLE_VISITABLE_HPP
#define CROW_LIB_VISITABLE_VISITABLE_HPP

// STL Includes:
#include <any>


// Macros:
#define MAKE_VISITABLE(t_visitor_type)                            \
  auto accept(t_visitor_type* t_visitor)->visitable::Any override \
  {                                                               \
    return {t_visitor->visit(this)};                              \
  }

#define VISITABLE_PURE_ACCEPT(t_vis_type) \
  auto accept(t_vis_type*)->visitable::Any override = 0

namespace visitable {
// We use std::any to allow a visitor to return anything
using Any = std::any;

// Classes:
/*!
 * Inheriting from this forces children to be visitable.
 */
template<typename VisitorType, typename RetType = Any>
class Visitable {
  public:
  virtual auto accept(VisitorType* t_visitor) -> RetType = 0;
};
} // namespace visitable

#endif // CROW_LIB_VISITABLE_VISITABLE_HPP
