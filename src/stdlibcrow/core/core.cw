// module core

// Define default file descriptors.
let STDIN = 0
let STDOUT = 1
let STDERR = 2

// Syscall wrapper API.
[[extern("C")]] {
  decl func read(t_fd: int, t_buf: *u8, t_count: u32) -> i32
  decl func write(t_fd: int, t_buf: *u8, t_count: u32) -> i32
  decl func read_str(t_fd: int, t_buf: str, t_count: u32) -> i32
  decl func write_str(t_fd: int, t_buf: str, t_count: u32) -> i32
  decl func open(t_path: str, t_flags: i32, t_mode: u32) -> int
  decl func close(t_fd: int) -> int
  decl func getpid() -> int
  decl func getppid() -> int

  decl func strlen(t_str: str) -> u32
}