module loop

func main() -> int {
   var sum = 10
   loop sum < 20; sum++ {
     println("Sum: {}", sum)
  }


   loop var index = 10; index < 20; index++ {
     println("Index: {}", index)
   }

   /*
    * loop {
    *   break
    *   continue
    * }
    */

   return sum
}
