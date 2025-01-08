#ifndef CROW_CROW_TOKEN_TOKEN_STREAM_HPP
#define CROW_CROW_TOKEN_TOKEN_STREAM_HPP

/*!
 * @file
 *
 * This file needs to exist because the operator<<() of @ref Stream<T>.
 * Is defined in the header as @ref Stream<T> is a templated class.
 * First we include @ref Token so that the operator<<() of @ref Stream<T>.
 * Sees the @ref Token operator<<().
 * Else it wont find the candidate for it.
 */

// STL Includes:
#include <vector>

// Absolute Includes:
#include "crow/container/stream.hpp"
#include "crow/token/token.hpp"

namespace token {
// Using Statements:
using container::Stream;

// Aliases:
using TokenVec = std::vector<Token>;
using TokenStream = Stream<TokenVec>;
} // namespace token

// Functions:
auto operator<<(std::ostream& t_os, const token::TokenStream& t_ts)
  -> std::ostream&;

#endif // CROW_CROW_TOKEN_TOKEN_STREAM_HPP
