#ifndef CROW_VISITABLE_VISITABLE_HPP
#define CROW_VISITABLE_VISITABLE_HPP


namespace visitable {
// Macros:
#define MAKE_VISITABLE(VisitorType)                  \
  auto accept(VisitorType* t_visitor)->void override \
  {                                                  \
    t_visitor->visit(this);                          \
  }

// Classes:
//! Interface that defines the method that must be implemented for a
template<typename T>
class Visitable {
  public:
  virtual auto accept(T* t_visitor) -> void = 0;
};
} // namespace visitable

#endif // CROW_VISITABLE_VISITABLE_HPP
