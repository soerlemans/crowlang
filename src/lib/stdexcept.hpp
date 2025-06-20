#ifndef CROW_LIB_STDEXCEPT_HPP
#define CROW_LIB_STDEXCEPT_HPP

/*!
 * @file stdexcept.hpp
 *
 * Helper exceptions which conditionally have stacktrace support or not.
 */

namespace lib::stdexcept {
struct exception : public std::exception {};

} // namespace lib::stdexcept

#endif // CROW_LIB_STDEXCEPT_HPP
