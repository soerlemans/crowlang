#ifndef CORE_H
#define CORE_H

// Core:
long read(int t_fd, unsigned char* t_buf, long t_count);
long write(int t_fd, const unsigned char* t_buf, long t_count);
int open(const char* t_path, const int t_flags, const unsigned int t_mode);
int close(int t_fd);
int getpid();
int getppid();

#endif // CORE_H
