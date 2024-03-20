# Figure Finder

## Description

This project solves the problem described in this [pdf document](docs/C++%20Developer%20-%20Task%20(English).pdf)

## Dependencies

The only dependency for this project is CMake for building the project.

## Build and Run instructions

```bash
mkdir build
cd build
cmake .. --preset release
cd ..
cmake --build build --config Release --parallel
cd build
ctest --config Release --verbose
```
## Cross-Platform support

There is an github actions based automation testing setup for Linux, MacOS and Windows. The project is tested on all three platforms. It was also tested for MacOS ARM device locally, since github actions do not support an easy way to test on ARM. The code is tested for the 3 main compilers - GCC, Clang and MSVC.

Here is the result of the last build and test runs - https://github.com/MartinNikolovMarinov/figure_finder/actions/runs/8363167606
