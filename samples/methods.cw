module methods_module

/*
*/

#include ""
#include_once ""

let magic_num = 100
let some_str = "Some string"

interface ExampleInterface {
  hello() -> void
}

struct ExampleStruct {
}

func (ExampleStruct*) test() -> void {
  println("Test!")
}

[[implements(Exampleinterface)]]
func hello(self: Examplestruct*) -> void {
  println("Hello!")
}

func main() -> int {
  return 0
}