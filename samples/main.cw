module main

// Standard library include.
#include_once <core/core.cw>

func main() -> int {
  var msg = "Hello World!\n"
  let len = strlen(msg)

  return write_str(STDOUT, msg, len)
}
