module declare_module

declare let fwd_var: int
declare func fwd_func() -> int

func main() -> int {
  fwd_func()

  return fwd_var
}

let fwd_var = 0

func fwd_func() -> int {
  return 0
}
