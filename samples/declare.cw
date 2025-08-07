module declare_module

declare let fwd_lvar: int
declare var fwd_vvar: int
declare func fwd_func() -> int

func main() -> int {
  fwd_func()

  return fwd_lvar
}

let fwd_lvar = 0

func fwd_func() -> int {
  return 0
}
