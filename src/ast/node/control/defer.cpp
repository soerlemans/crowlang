#include "defer.hpp"


using namespace ast::node::control;
using namespace ast::node::node_traits;

Defer::Defer(NodeListPtr&& t_body): Body{std::move(t_body)}
{}
