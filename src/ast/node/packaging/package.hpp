#ifndef CROW_AST_NODE_PACKAGING_PACKAGE_HPP
#define CROW_AST_NODE_PACKAGING_PACKAGE_HPP

// Includes:
#include "../node_interface.hpp"

// Local Includes:
#include "packaging.hpp"


namespace ast::node::packaging {
class Package : public NodeInterface {
  private:
  std::string m_identifier;

  public:
  Package(std::string t_identifier);

  auto identifier() const -> std::string_view;

  MAKE_VISITABLE(visitor::NodeVisitor);

  ~Package() override = default;
};
} // namespace ast::node::packaging

#endif // CROW_AST_NODE_PACKAGING_PACKAGE_HPP
