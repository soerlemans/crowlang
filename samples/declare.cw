module declare_module

decl let fwd_lvar: int
decl var fwd_vvar: int
decl func fwd_func() -> int

func main() -> int {
  fwd_func()

  return fwd_lvar
}

let fwd_lvar = 0
var fwd_vvar = 0

func fwd_func() -> int {
  return 0
}
