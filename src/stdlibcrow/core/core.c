#include "core.h"

long write(int t_fd, const void* t_buf, long t_count)
{
  long err = 0;

  /* __asm__("mov $1, %%rax;" // syscall number for write (1) */
  /*         "mov %0, %%rdi;" // move fd (first argument) into rdi */
  /*         "mov %1, %%rsi;" // move buf (second argument) into rsi */
  /*         "mov %2, %%rdx;" // move count (third argument) into rdx */
  /*         "syscall;"       // make the syscall */
  /*         "mov %%rax, %3;" // move the return value (result) from rax to result */
  /*         : "=r"(err)   // output: result will store the return value */
  /*         : "r"(t_fd), "r"(t_buf), "r"(t_count)  // inputs: fd, buf, count */
  /*         : "%rax", "%rdi", "%rsi", "%rdx" // clobbered registers */
  /* ); */

  return err;
}

int close(int t_fd)
{
  int err = 0;

  // clang-format off
  /* __asm__("mov $3, %%rax;" // close syscall is 3. */
  /*         "mov %0, %%rdi;" // move fd into rdi. */
  /*         "syscall;" */
  /*         "mov %%rax, %0;" */
  /*         : "=r"(err) */
  /*         : "r"(t_fd) */
  /*         : "%rdi" // clobbered registers */
  /* ); */
  // clang-format on

  return err;
}

int getpid()
{
  int pid = 0;

  // clang-format off
  __asm__(
    "mov $39, %%rax;" // getpid syscall is 39.
    "syscall;"
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
    "mov $110, %%rax;" // getppid syscall is 110.
    "syscall;"
    : "=r"(pid)
    :
    :
  );
  // clang-format on

  return pid;
}
