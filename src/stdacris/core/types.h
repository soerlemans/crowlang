#ifndef TYPES_H
#define TYPES_H


/*!
 * @file
 *
 * We define our own types for now so we dont have to depend on libc for later.
 * Then we can disable libc++ and similar
 */


#ifdef __cplusplus
extern "C" {
#endif

// On false condition will make a  will
#define core_assert(t_cond, t_msg) \
  typedef char assert_failed_##t_msg[(t_cond) ? 1 : -1]

// Fixed width Types:
typedef int int_t;          // 1 bytes.
typedef signed char i8_t;   // 4 bytes.
typedef signed short i16_t; // 2 bytes.
typedef signed int i32_t;   // 4 bytes.
typedef signed long i64_t;  // 8 bytes.

typedef unsigned int uint_t;  // 4 bytes.
typedef unsigned char u8_t;   // 1 bytes.
typedef unsigned short u16_t; // 2 bytes.
typedef unsigned int u32_t;   // 4 bytes.
typedef unsigned long u64_t;  // 8 bytes.

// Define helper types.
typedef long isize_t;          // 8 bytes.
typedef unsigned long usize_t; // 8 bytes.
typedef unsigned int umode_t;  // 4 bytes.

// TODO: Add ifdef which checks 32bit or 64 bit.
core_assert(sizeof(isize_t) == 8, isize_t_is_8_bytes);
core_assert(sizeof(usize_t) == 8, usize_t_is_8_bytes);
core_assert(sizeof(umode_t) == 4, umode_t_is_4_bytes);

core_assert(sizeof(i8_t) == 1, u8_t_is_1_bytes);
core_assert(sizeof(i16_t) == 2, i16_t_is_2_bytes);
core_assert(sizeof(i32_t) == 4, i32_t_is_4_bytes);
core_assert(sizeof(i64_t) == 8, i64_t_is_8_bytes);

core_assert(sizeof(u8_t) == 1, u8_t_is_1_bytes);
core_assert(sizeof(u16_t) == 2, i16_t_is_2_bytes);
core_assert(sizeof(u32_t) == 4, i32_t_is_4_bytes);
core_assert(sizeof(u64_t) == 8, i64_t_is_8_bytes);

// Undefine assert.
#undef core_assert

#ifdef __cplusplus
}
#endif

#endif // TYPES_H
