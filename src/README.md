Architecture
============

 - `crow` contains the actual compiler code.
 - `lib` contains useful utilities used project wide.
 - `lib` contains the standard library used by the generated C++ code.

## About includes
Here is an example of how includes should ordered for a file titled `header.cpp`.
Ignore the comments containing a `//~`, in the example below:

```cpp
//~ 1. Include header of the same name.
#include "header.hpp"

//~ 2. Include headers of the standard template library (must use angle brackets).
// STL Includes:
#include <filesystem>

//~ 3. Include headers for any third party libraries (must use angle brackets).
// Library Includes:
#include <rang>

//~ 4. Include headers in a parent directory.
// Absolute Includes:
#include "crow/container/text_position.hpp"

//~ 5. Include headers in a parent directory in the AST code.
// Relative AST Includes:
#include "../node/fdecl.hpp"

//~ 6. Include headers in the current or child directory.
// Local Includes:
#include "error.hpp"
```

It is important to adhere to this.
