#include "core.h"

long read(int t_fd, unsigned char* t_buf, long t_count)
{
  long err = 0;

  __asm__("mov $1, %%rax\n" // read syscall is 0.
          "mov %0, %%rdi\n"
          "mov %1, %%esi\n"
          "mov %2, %%rdx\n"
          "syscall\n"
          : "=r"(err)
          : "r"(t_fd), "r"(t_buf), "r"(t_count)
          : "%rax", "%rdi", "%rsi", "%rdx" // clobbered registers.
  );

  return err;
}

long write(int t_fd, const unsigned char* t_buf, long t_count)
{
  long err = 0;

  __asm__("mov $1, %%rax\n" // write syscall is 1.
          "mov %0, %%rdi\n"
          "mov %1, %%esi\n"
          "mov %2, %%rdx\n"
          "syscall\n"
          : "=r"(err)
          : "r"(t_fd), "r"(t_buf), "r"(t_count)
          : "%rax", "%rdi", "%rsi", "%rdx" // clobbered registers.
  );

  return err;
}

int open(const char* t_path, int t_flags, unsigned int t_mode)
{
  int err = 0;

  // clang-format off
  __asm__("mov $2, %%rax\n" // open syscall is 2.
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

int close(int t_fd)
{
  int err = 0;

  // clang-format off
  __asm__("mov $3, %%rax\n" // close syscall is 3.
          "mov %0, %%edi\n"
          "syscall\n"
          : "=r"(err)
          : "r"(t_fd)
          : "%rdi" // clobbered registers.
  );
  // clang-format on

  return err;
}

int getpid()
{
  int pid = 0;

  // clang-format off
  __asm__(
    "mov $39, %%rax\n" // getpid syscall is 39.
    "syscall\n"
    : "=r"(pid)
    :
    :
  );
  // clang-format on

  return pid;
}

int getppid()
{
  int pid = 0;

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
