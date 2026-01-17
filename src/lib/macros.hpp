#ifndef ACRIS_LIB_MACROS_HPP
#define ACRIS_LIB_MACROS_HPP

/*
 * Macros for common operations.
 */
#define STRINGIFY(expr)    #expr
#define CONCAT(a, b)       CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b

#endif // ACRIS_LIB_MACROS_HPP
