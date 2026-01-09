module methods_module

let magic_num = 100

struct ExampleStruct {
  m_num1: int
  m_num2: int
  m_num3: int
}

func (ExampleStruct) set() -> int {
  self.m_num1 = 20
  self.m_num2 = 40
  self.m_num3 = 60

  return -1
}

func init_example_struct() -> ExampleStruct {
  var example: ExampleStruct

  example.m_num1 = 10
  example.m_num2 = 10
  example.m_num3 = 10

  return example
}


func pass_example_struct(param: ExampleStruct) -> ExampleStruct{
  var example: ExampleStruct

  param.m_num1 = 200

  return param
}

func main() -> int {
  // var example: ExampleStruct = init_example_struct()
  var example: ExampleStruct
  example = init_example_struct()

  init_example_struct()

  let returned_example = pass_example_struct(example)

  let test = example.set()

  return test
}