module loop_module

func main() -> int {
  var someVar = 10

  loop var index = 10; index < 20; index++ {
    someVar += 10
  }

  return 0
}
