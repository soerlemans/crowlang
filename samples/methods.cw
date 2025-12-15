module methods_module

let magic_num = 100

struct ExampleStruct {
  m_num1: int
  m_num2: int
  m_num3: int
}

func (ExampleStruct) set() -> void {
  self.m_num1 = 20
  self.m_num2 = 40
  self.m_num3 = 60
}

func init_example_struct() -> ExampleStruct {
  var example: ExampleStruct

  example.m_num1 = 10
  example.m_num2 = 10
  example.m_num3 = 10

  return example
}

func main() -> int {
  // var example: ExampleStruct = init_example_struct()
  var example: ExampleStruct
  example = init_example_struct()

  init_example_struct()

  // Need to deal with this in grammar.
  example.set()

  let test = example.m_num1

  return test
}