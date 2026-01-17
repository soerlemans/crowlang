// module core

// Define default file descriptors.
let STDIN = 0
let STDOUT = 1
let STDERR = 2

// Syscall wrapper API.
[[extern("C")]] {
  decl func read(t_fd: int, t_buf: *u8, t_count: usize) -> isize
  /// FIXME: These conflict as of writing with core.h, fix signature.
  // decl func write(t_fd: int, t_buf: *u8, t_count: usize) -> isize
  // decl func read_str(t_fd: int, t_buf: str, t_count: usize) -> isize
  decl func write_str(t_fd: int, t_buf: str, t_count: usize) -> isize
  decl func open(t_path: str, t_flags: i32, t_mode: u32) -> int
  decl func close(t_fd: int) -> int
  decl func getpid() -> int
  decl func getppid() -> int

  decl func strlen(t_str: str) -> usize
}

// func print(t_str: str) -> isize {
//   let len = strlen(t_str)
  
//   return write_str(STDOUT, t_str, len)
// }

// func println(t_str: str) -> usize {
//   let len = strlen(t_str)

//   return write_str(STDOUT, t_str, len)
// }