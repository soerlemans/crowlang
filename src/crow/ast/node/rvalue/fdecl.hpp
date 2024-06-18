#ifndef CROW_CROW_AST_NODE_RVALUE_FDECL_HPP
#define CROW_CROW_AST_NODE_RVALUE_FDECL_HPP

namespace ast::node::rvalue {
// Forward Declarations:
template<typename T>
class Literal;

// Aliases:
using Integer = Literal<int>;
using Float = Literal<double>;
using String = Literal<std::string>;
using Boolean = Literal<bool>;
} // namespace ast::node::rvalue

#endif // CROW_CROW_AST_NODE_RVALUE_FDECL_HPP
