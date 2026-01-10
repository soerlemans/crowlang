#include "core.h"

int getpid()
{
  int pid = 0;

  // clang-format off
  __asm__(
    "mov $39, %%rax;" // getpid syscall is 39.
    "syscall;"
    : "=a"(pid)
    :
    :
  );
  // clang-format on

  return pid;
}
