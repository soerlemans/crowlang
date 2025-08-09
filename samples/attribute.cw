module attribute_module

// Define a forward declaration for the libc abs function.
[[extern("C")]] {
  declare func abs(t_x: int) -> int
}

// Inline attribute block.
[[inline]] {
  func test1(t_x: int) -> int {
    return 10
  }

  func test2(t_x: int) -> int {
    return 10
  }
}

[[inline]]
func test3(t_x: int) -> int {
  return 30
}

[[inline]]
[[constexpr]]
func test4(t_x: int) -> int {
  return 30
}

func main() -> int {
  let num = abs(-23)

  println("Absolute value of -23 => {}", num)

  return 0
}
