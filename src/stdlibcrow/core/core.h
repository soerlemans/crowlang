#ifndef CORE_H
#define CORE_H

/*!
 * @file
 *
 * Warning the C core is built without libc.
 */

// On false condition will make a  will
#define static_assert(t_cond, t_msg) \
  typedef char array_##t_msg[(t_cond) ? 1 : -1]

// Types:
// Define helper types.
typedef long ssize_t;         // 32 bit.
typedef unsigned long size_t; // 32 bit.
typedef unsigned int umode_t; // 32 bit.

static_assert(sizeof(ssize_t) == 8, ssize_t_is_8_bytes);
static_assert(sizeof(size_t) == 8, size_t_is_8_bytes);
static_assert(sizeof(umode_t) == 4, umode_t_is_4_bytes);


// Core:
ssize_t read(int t_fd, unsigned char* t_buf, size_t t_count);
ssize_t write(int t_fd, const unsigned char* t_buf, size_t t_count);
ssize_t read_str(int t_fd, char* t_buf, size_t t_count);
ssize_t write_str(int t_fd, const char* t_buf, size_t t_count);
int open(const char* t_path, const int t_flags, const umode_t t_mode);
int close(int t_fd);
int getpid();
int getppid();

size_t strlen(const char* t_str);

#endif // CORE_H
