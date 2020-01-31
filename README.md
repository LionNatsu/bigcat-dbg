# bigcat-dbg

My debugging tools for Linux. Everyone is welcome to add new stuff!

Use CMake to build and install them. There is [installation guide](INSTALL.md) for your information.

For a better debugging experience, they are all compiled with `-g`.

Build dependencies: CMake(>= 3.2), GCC

## Commands

### ldk-load-lib
```
Usage:  ldk-load-lib libfoo.so libbar.so...
```
Loads `.so` (aka. Shared Objects or Shared Libraries) by `dlopen()` and unloads them all.

Tips:
1. You may use full paths.
2. Try `LD_DEBUG=blah ...` to get more information.
