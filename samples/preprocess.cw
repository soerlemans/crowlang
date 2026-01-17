module preprocessor_sample

#include "samples/preprocess.cw"

// Standard library include.
#include_once <core/linux/core.cw>


// Relative path include.
// #include_once "test"

func main() -> int {
  return getpid()
}