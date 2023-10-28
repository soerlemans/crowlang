#ifndef ENV_STACK_HPP
#define ENV_STACK_HPP

// Local Includes:
#include "symbol_data.hpp"


namespace check {
// Aliases:
using Env = std::map<std::string, SymbolData>;

// Classes:
class EnvStack : public std::list<Env> {};
} // namespace check

#endif // ENV_STACK_HPP
