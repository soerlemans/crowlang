module pointer_module

func main() -> int {
  var target = 100
  var target2 = 200
  // let pointer: *int = target

  var pointer: *int = &target
  var pointer2: *int = &target
  var var3 = *pointer2

  return var3
}