/*
 * Sample meant to show order independent function calling.
 * Function calling and usage of return values.
 */

fn function1(param1: int) -> int {
    println("Function1.")
    return param1
}

fn function2(param1: int, param2: int) -> int {
    if param2 > 10 {
        println("Function2.")
        return function1(param1)
    }

    return 0
}

fn function3(param1: int, param2: int, param3: bool) -> int {
    if param3 {
        println("Function3.")
        return function2(param1, param2)
    }

    return 0
}

fn main() -> int {
    println("Function4.")
    println("Result: {}", function3(10, 20, True))

    return 0
}
