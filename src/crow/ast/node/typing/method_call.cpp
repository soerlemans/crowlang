#include "method_call.hpp"

namespace ast::node::typing {
MethodCall::MethodCall(const std::string_view t_identifier,
                       NodeListPtr&& t_args)
  : Identifier{std::move(t_identifier)}, Args{std::move(t_args)}
{}
} // namespace ast::node::typing
