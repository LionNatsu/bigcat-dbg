# bigcat-dbg

My debugging tools. Everyone is welcome to add new stuff!

## Installation

First you should make a directory for building, say "build". Enter the directory.
```
mkdir build
cd build
```
Use "cmake" to configure the building environment.
```
cmake ..
```
Now CMake generated the "Makefile", so...
```
make
sudo make install
```
And everything is ready to go.

## Commands

### load-shlib
```
Usage:  load-shlib libfoo.so libbar.so...
```
Loads `.so` (aka. Shared Objects or Shared Libraries) by `dlopen()` and unloads them all.

Tips:
1. You may use full paths.
2. Try `LD_DEBUG=blah ...` to get more information.
