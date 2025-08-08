module attribute_module

// Define a forward declaration for the libc abs function.
[[extern("C")]] {
  declare func abs(t_x: int) -> int
}

func main() -> int {
  let num = abs(-23)

  println("Absolute value of -23 => {}", num)

  return 0
}
