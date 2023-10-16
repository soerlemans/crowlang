let global = 10

fn test() -> int {
  return global
}

fn main() -> int {
  let var = 10
  let var2 = var

  let result = test() + var2

	return 0
}
