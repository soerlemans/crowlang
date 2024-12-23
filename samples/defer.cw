/*
 * Sample meant to show of the defer keyword.
 * The defer keyword is used to delay the execution of a block.
 * To the end of a function's lifetime.
 */

fn main() -> int {
    defer println("Defer 1")
    defer {
        println("Defer 2")
    }

    defer {
        println("Defer 3: ", 10 + 10)
    }

    println("Regular print 1")

    // FIXME: Gives error, relating to TypeVariant.
    defer {
         let calc = 10 + 10
         println("Defer 4: ", calc)
    }

    println("Regular print 2")

    return 0
}
