module declare_module

declare func fwd_func() -> int

func fwd_func() -> int {
  return 0
}

func main() -> int {
  fwd_func()

  return 0
}
