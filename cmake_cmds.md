# CMake Workflow
## Configure (generate build files)
cmake -S . -B build

Only needs to be rerun after changing `CMakeLists.txt` or when creating a fresh build directory.

---

## Build

cmake --build build

Run this after changing source code.

---

## Test

ctest --test-dir build

---

## Run

./build/tty_invaders

---

## Clean everything

rm -rf build
cmake -S . -B build
cmake --build build
