module attribute_module

[[extern("C")]] {
  declare func abs(t_x: int) -> int
}

func main() -> int {
  let num = abs(-23)

  io::println("Absolute value of -23 => {}", num)

  return 0
}
