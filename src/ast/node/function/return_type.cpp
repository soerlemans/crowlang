#include "return_type.hpp"


namespace ast::node::function {
ReturnType::ReturnType(const std::string_view t_type): TypeAnnotation{t_type}
{}
} // namespace ast::node::function
