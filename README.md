# Figure Finder

## Description

This project solves the problem described in this [pdf document](docs/C++%20Developer%20-%20Task%20(English).pdf)

## Dependencies

The only dependency for this project is CMake for building the project.

## Project Structure

The project is structured in the following way:
1. The `include/figure_finder.h` and `src/figure_finder.cpp` files contain the solution to the problem.
2. The `include/core` and `src/core` directories contain common utilities used in the project.
3. The `test` folder contains the tests for the project.
4. The `CMakeLists.txt` file is used to configure the project and build it. The `cmake` folder contains common cmake utilities. `CMakePresets.json` is used to configure the build presets.
5. The `.github` folder contains actions, which are used for the CI/CD pipeline, to build and test the project on
   multiple platforms (Windows, Intel MacOS, Ubuntu).

CMake is configured to build a library called `libfigure_finder` that can be used in other projects, and it also builds a test executable (unless a flag is set to disable it), which links to the library and runs multiple test suites to verify the correctness and performance of the solution.

## Build and Run instructions

To Build:
```bash
mkdir build
cd build
cmake .. --preset release
cd ..
cmake --build build --config Release --parallel
```

To Run the tests:
```bash
cd build
ctest --config Release --verbose
```

Windows might want:
```bash
cd build
ctest -C Release --verbose
```

## Cross-Platform support

There is an github actions based automation testing setup for Linux, MacOS and Windows. The project is tested on all three platforms. It was also tested for MacOS ARM device locally, since github actions do not support an easy way to test on ARM. The code is tested for the 3 main compilers - GCC, Clang and MSVC.

Here is the result of the last build and test runs -
https://github.com/MartinNikolovMarinov/figure_finder/actions/runs/8388583734
