module if_module

func branch(t_cond: int) -> bool {
  var someVar: int = -1

  if t_cond > 10 {
    someVar = 1
  } else {
    someVar = 0
  }

  return someVar
}

func branch2(t_cond: int) -> bool {
  var someVar: int = -1

  if t_cond > 10 {
    someVar = 1
  }

  return someVar
}

func main() -> int {
  branch(0)

  return 0
}