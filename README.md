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
3. E.g. you may use 'libpthread.so' to refer to a library linked with -lpthread.

### ldk-depends-lib
```
Usage: ldk-depends-lib [-p] a.out
```
It lists all dynamic linked libraries ("soname") the executable needs.

You may use `-p` to get the full path. Standard error lists libraries which can not be found.

However, you must configure CMake correctly to get proper results. This is because some systems
also use other directories besides `/lib` and `/usr/lib`.

Debian, for example:
```
cmake -DSYSTEM_DIRS='"/lib/x86_64-linux-gnu:/usr/lib/x86_64-linux-gnu"' ..
```
