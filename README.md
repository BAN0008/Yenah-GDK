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
