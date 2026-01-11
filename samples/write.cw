module write_sample

// Standard library include.
#include_once <core/core.cw>

func main() -> int {
  let path = "newfile.txt"

  // O_CREAT = 0x40
  let fd = open(path, 0x40, 0644)

  // TODO: Write().

  close(fd)

  return 0
}