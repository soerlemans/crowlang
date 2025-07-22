module logical_

func not_op(t_left: bool) -> bool {
  // let result = !t_left

  // if result {
  //   println("True")
  // } else {
  //   println("False")
  // }

  // return result
}

func and_op(t_left: bool, t_right: bool) -> bool {
  let result = t_left && t_right

  if result {
    println("True")
  } else {
    println("False")
  }

  return result
}

func or_op(t_left: bool, t_right: bool) -> bool {
  let result = t_left || t_right

  if result {
    println("True")
  } else {
    println("False")
  }

  return result
}