#ifndef CROW_VISITOR_VISITABLE_HPP
#define CROW_VISITOR_VISITABLE_HPP


namespace visitor {
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
} // namespace visitor

#endif // CROW_VISITOR_VISITABLE_HPP
