module context_test

fn main() -> int {
    loop var index = 10; index > 0; index-- {
        if True {
	    break
	}
    }

    return 0
}