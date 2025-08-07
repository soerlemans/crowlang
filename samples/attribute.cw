module attribute_module

[[extern("C")]] {
  declare func abs(t_x: int) -> int
}

func main() -> int {
  abs(-23)

  return 0
}
