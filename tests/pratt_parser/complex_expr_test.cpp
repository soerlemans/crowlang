// STL Includes:
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

// Library Includes:
#include <catch2/catch_test_macros.hpp>

// Crow Absolute Includes:
#include "crow/ast/node/include.hpp"
#include "crow/parser/pratt_parser/pratt_parser.hpp"
#include "crow/lexer/lexer.hpp"

/*!
 * @file
 *
 * The @ref PrattParser is actually pretty complex and we need to check for regressions.
 * For complex cases.
 */


// Using namespace Declarations:
using namespace std::literals::string_view_literals;

// Test Cases:
TEST_CASE("PrattParser", "[pratt_parser]")
{
}
