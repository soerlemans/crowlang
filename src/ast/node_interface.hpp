#ifndef NODE_INTERFACE_HPP
#define NODE_INTERFACE_HPP


namespace ast {
class NodeInterface {
  public:
  // virtual auto accept(visitor::NodeVisitor* t_visitor) -> void = 0;

  virtual ~NodeInterface() = default;
};
} // namespace ast

#endif // NODE_INTERFACE_HPP
