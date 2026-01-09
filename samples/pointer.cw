module pointer_module

func main() -> int {
  var target = 100
  var target2 = 100
  // let pointer: *int = target

  var pointer: *int = &target
  var pointer2: *int = &target

  return 0
}