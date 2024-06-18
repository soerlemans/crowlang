Architecture
============

 - `archive/` contains utilities for helping with the archiving of the AST.
 - `node/` contains the nodes which the AST consists of.
 - `visitor/` contains classes used for the visitor design pattern.


## Relative includes
It is important to know that the AST allows relative parent includes.
These are denoted as follows:

```cpp
// Relative AST Includes:
#include "../node/include_nodes.hpp"
```

The reason for this is that the nodes use a lot of relative includes that refer to the root classes of the AST.
There is little reason to make these paths absolute as the nodes generate a kind of natural include graph that propels up.
Using absolute includes for these would just complicate things.
