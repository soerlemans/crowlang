module countdown

fn main() -> int {
    println("Starting countdown...")

    loop var index = 10; index > 0; index-- {
        println("{}", index)
    }

    println("Blast off!")

    return 0
}
