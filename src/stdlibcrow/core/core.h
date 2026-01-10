#ifndef CORE_H
#define CORE_H

// Core:
long write(int t_fd, const void* t_buf, long t_count);
int close(int t_fd);
int getpid();
int getppid();

#endif // CORE_H
