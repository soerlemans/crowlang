#ifndef CROW_AST_NODE_RVALUE_RVALUE_HPP
#define CROW_AST_NODE_RVALUE_RVALUE_HPP


namespace ast::node::rvalue {
// Forward Declarations:
template<typename T>
class Literal;

// Aliases:
using Integer = Literal<int>;
using Float = Literal<double>;
using String = Literal<std::string>;
} // namespace ast::node::rvalue

#endif // CROW_AST_NODE_RVALUE_RVALUE_HPP
