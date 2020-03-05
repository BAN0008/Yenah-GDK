# TODO
- **IMPORTANT: Test persistent buffer mapping**

# Building
## Linux
1. Install cmake, make, g++/clang and SDL2
2. Open terminal
3. Navigate to the directory containing the engine
4. Enter below commands
```
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cd build
make
```
5. Repeat steps for TestApp


## Windows
1. Install Visual Studio with the C++ Desktop Development Workload
2. Open a x64 native tools command prompt
3. Navigate to the directory containing the engine
4. Enter below commands
```
cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja -B build
cd build
ninja
```
5. Repeat steps for TestApp
6. Copy `Engine/vendor/SDL2/lib/x64/SDL2.dll` and `Engine/vendor/LuaJit/lib/x64/luajit.dll` and `Engine/build/debug/yeno.dll` to `TestApp/build/debug`

### Alternative
There is also a build script in TestApp that should automatically complete all the required steps of building.
