#ifndef CROW_AST_NODE_FUNCTION_PARAMETER_HPP
#define CROW_AST_NODE_FUNCTION_PARAMETER_HPP

// Includes:
#include "../node_traits/include.hpp"

// Local Includes:
#include "fdecl.hpp"


namespace ast::node::function {
// Aliases:
namespace nt = node_traits;
namespace ct = container;

// Classes:
class Parameter : public nt::NodePosition,
                  public nt::Identifier,
                  public nt::TypeAnnotation {
  public:
  Parameter(ct::TextPosition t_pos, std::string_view t_identifier,
            std::string_view t_type);

  MAKE_VISITABLE(visitor::NodeVisitor);

  virtual ~Parameter() = default;
};
} // namespace ast::node::lvalue

#endif // CROW_AST_NODE_FUNCTION_PARAMETER_HPP
