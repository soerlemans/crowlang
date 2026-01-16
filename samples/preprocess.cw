module preprocessor_sample

// Standard library include.
#include_once <core/linux/core.cw>

// Relative path include.
// #include_once "test"

func main() -> int {
  return getpid()
}