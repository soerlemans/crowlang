fn function1(param1: int) -> int {
    return param1
}

fn function2(param1: int, param2: int) -> int {
    if param2 > 10 {
        // return function1(param1)
        return function1(10)
    }

    return 0
}

fn function3(param1: int, param2: int, param3: bool) -> int {
    if param3 {
        return function2(param1, param2)
    }

    return 0
}

fn main() -> int {
    function3(10, 20, True)

    return 0
}
