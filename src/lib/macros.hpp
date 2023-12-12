#ifndef CROW_LIB_MACROS_HPP
#define CROW_LIB_MACROS_HPP

/*
 * Macros for common operations.
 */
#define STRINGIFY(expr)    #expr
#define CONCAT(a, b)       CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b

#endif // CROW_LIB_MACROS_HPP
