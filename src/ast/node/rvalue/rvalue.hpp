#ifndef CROW_AST_NODE_RVALUE_RVALUE_HPP
#define CROW_AST_NODE_RVALUE_RVALUE_HPP

// Includes:
#include "../node.hpp"


namespace node::rvalue {
template<typename T>
class Literal;

class Regex;

// Aliases:
// TODO: Think about a way to convey Regex literals
using Integer = Literal<int>;
using Float = Literal<double>;
using String = Literal<std::string>;
} // namespace node::rvalue

#endif // CROW_AST_NODE_RVALUE_RVALUE_HPP
