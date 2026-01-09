module pointer_module

func main() -> int {
  let target = 100
  // let pointer: *int = target

  var pointer: *int
  var pointer2: *int = &target

  return 0
}