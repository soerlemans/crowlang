module error_sample

// Standard library include.
#include_once <core/linux/core.cw>

func main() -> int {
  var msg = "Error: Hello World!\n"
  let len = strlen(msg)

  return write_str(STDERR, msg, len)
}
