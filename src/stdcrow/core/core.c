#include "core.h"

isize_t read(int_t t_fd, unsigned char* t_buf, usize_t t_count)
{
  isize_t err = 0;

  // clang-format off
  __asm__(
		"mov $1, %%rax\n" // read syscall is 0.
		"mov %0, %%rdi\n"
		"mov %1, %%esi\n"
		"mov %2, %%rdx\n"
		"syscall\n"
		: "=r"(err)
		: "r"(t_fd), "r"(t_buf), "r"(t_count)
		: "%rax", "%rdi", "%rsi", "%rdx" // clobbered registers.
  );
  // clang-format on

  return err;
}

isize_t write(int_t t_fd, const unsigned char* t_buf, usize_t t_count)
{
  isize_t err = 0;

  // clang-format off
  __asm__(
		"mov $1, %%rax\n" // write syscall is 1.
		"mov %0, %%rdi\n"
		"mov %1, %%esi\n"
		"mov %2, %%rdx\n"
		"syscall\n"
		: "=r"(err)
		: "r"(t_fd), "r"(t_buf), "r"(t_count)
		: "%rax", "%rdi", "%rsi", "%rdx" // clobbered registers.
  );
  // clang-format on

  return err;
}

isize_t read_str(int_t t_fd, char* t_buf, usize_t t_count)
{
  return read(t_fd, (unsigned char*)t_buf, t_count);
}

isize_t write_str(int_t t_fd, const char* t_buf, usize_t t_count)
{
  return write(t_fd, (const unsigned char*)t_buf, t_count);
}

int_t open(const char* t_path, int_t t_flags, umode_t t_mode)
{
  int_t err = 0;

  // clang-format off
  __asm__(
		"mov $2, %%rax\n" // open syscall is 2.
		"mov %0, %%edi\n"
		"mov %1, %%rsi\n"
		"mov %2, %%edx\n"
		"syscall\n"
		: "=r"(err)
		: "r"(t_path), "r"(t_flags), "r"(t_mode)
		: "%rdi", "%rsi", "%rdx" // clobbered registers.
  );
  // clang-format on

  return err;
}

int_t close(int_t t_fd)
{
  int_t err = 0;

  // clang-format off
  __asm__(
		"mov $3, %%rax\n" // close syscall is 3.
		"mov %0, %%edi\n"
		"syscall\n"
		: "=r"(err)
		: "r"(t_fd)
		: "%rdi" // clobbered registers.
  );
  // clang-format on

  return err;
}

int_t getpid()
{
  int_t pid = 0;

  // clang-format off
  __asm__(
    "mov $39, %%rax\n" // getpid syscall is 39.
    "syscall\n"
    : "=r"(pid)
    :
    : "rax"
  );
  // clang-format on

  return pid;
}

void __attribute__((noreturn)) exit(int_t t_errc)
{
  // clang-format off
  __asm__(
    "mov $60, %%rax\n" // exit syscall is 60.
		"mov %0, %%edi\n"
    "syscall\n"
    :
    : "r"(t_errc)
		: "rax", "rdi" // clobbered registers.
  );
  // clang-format on
}

int_t getppid()
{
  int_t pid = 0;

  // clang-format off
  __asm__(
    "mov $110, %%rax\n" // getppid syscall is 110.
    "syscall\n"
    : "=r"(pid)
    :
    :
  );
  // clang-format on

  return pid;
}

usize_t strlen(const char* t_str)
{
  const char* ptr = t_str;
  while(*ptr != '\0') {
    ptr++;
  }

  return (usize_t)(ptr - t_str);
}

void _start()
{
  // Perform pre main setup.

  const int_t errc = main();

  exit(errc);

  __builtin_unreachable();
}
