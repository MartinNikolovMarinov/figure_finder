#include <figure_finder.h>

using namespace coretypes;

#include <iostream>

using DataType = std::vector<bool>;

i32 main(i32 argc, char** argv) {
    if (!core::initCore(argc, argv)) {
        return -1;
    }
    defer { core::shutdownCore(); };

    // std::vector<bool> matrix = {
    //     1, 0, 1, 0, 0, 0, 1, 1, 0, 0,

    //     0, 1, 1, 0, 0, 1, 0, 0, 1, 1,

    //     1, 0, 0, 0, 0, 0, 1, 1, 1, 1,

    //     1, 1, 0, 1, 1, 1, 1, 1, 0, 1,

    //     0, 1, 0, 1, 1, 0, 1, 1, 0, 1,

    //     0, 1, 0, 1, 0, 1, 1, 0, 1, 0,

    //     0, 1, 1, 1, 0, 1, 1, 0, 1, 1,

    //     0, 1, 0, 1, 1, 1, 0, 1, 1, 1,

    //     1, 1, 1, 1, 0, 1, 0, 0, 1, 0,

    //     1, 0, 1, 1, 0, 1, 1, 0, 1, 1,

    //     0, 1, 1, 1, 1, 0, 1, 1, 1, 0,
    //     1, 1, 1, 0, 0, 0, 0, 0, 1, 0,
    //     0, 0, 1, 1, 0, 0, 0, 0, 1, 1,
    //     1, 1, 1, 1, 0, 1, 1, 1, 0, 0,
    //     1, 1, 1, 0, 0, 1, 0, 0, 1, 0,
    // };

    std::vector<bool> matrix = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };

    constexpr i32 width = 12;
    constexpr i32 height = 5;

    i32 expected = figfind::countFiguresDFS(matrix, width, height);
    i32 got = figfind::countFiguresParallel(matrix, width, height, 4);

    std::cout << "Expected: " << expected << std::endl;
    std::cout << "Got: " << got << std::endl;

    return 0;
}
