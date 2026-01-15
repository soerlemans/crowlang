module write_sample

// Standard library include.
#include_once <core/core.cw>

func main() -> int {
  var path = "newfile.txt"
  let flags: i32 = 0x40
  let mode: u32 = 0x1A4 // 0644

  // O_CREAT = 0x40
  let fd = open(path, flags, mode)

  var msg = "Hello World!."
  let len = strlen(msg)

  // write_str(fd, msg, len)

  close(fd)

  return 0
}