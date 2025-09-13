#include "self.hpp"

namespace ast::node::typing {
Self::Self(std::string_view t_identifier, std::string_view t_type)
  : Identifier{t_identifier}, TypeAnnotation{t_type}
{}
} // namespace ast::node::typing
