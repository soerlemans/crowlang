// module core


[[extern("C")]] {
  decl func read(t_fd: int, t_buf: *u8, t_count: i32) -> i32
  decl func write(t_fd: int, t_buf: *u8, t_count: i32) -> i32
  decl func open(t_path: str) -> int
  decl func close(t_fd: int, t_flags: i32, t_mode: u32) -> int
  decl func getpid() -> int
  decl func getppid() -> int
}