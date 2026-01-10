// module core


[[extern("C")]] {
  decl func close(t_fd: int) -> int
  decl func getpid() -> int
  decl func getppid() -> int
}