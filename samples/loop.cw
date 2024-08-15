fn main() -> int {
   #var empty: int

   var sum = 10
   loop sum < 20; sum++ {
   }

   loop var index = 10; index < 20; index++ {
   }

   #loop {
     #break
     #continue
   #}

   return sum
}
