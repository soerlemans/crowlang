module and_

func and_op(t_left: bool, t_right: bool) -> bool {
  let result = t_left && t_right

  if result {
    println("True")
  } else {
    println("False")
  }

  return result
}